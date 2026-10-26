/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 * This program is free software, you can redistribute it and/or modify it under the terms and conditions of
 * CANN Open Software License Agreement Version 2.0 (the "License").
 * Please refer to the License for details. You may not use this file except in compliance with the License.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 * See LICENSE in the root of the software repository for the full text of the License.
 */

#include <array>
#include <charconv>
#include <cinttypes>
#include <cstdint>
#include <cstring>
#include <limits>

#include "acl/acl.h"
#include "utils.h"

namespace {
constexpr int32_t DEVICE_ID = 0;
constexpr size_t INITIAL_CAPACITY = 8U;
constexpr size_t MAX_COMPONENTS = 256U;
constexpr uint32_t MIB_SHIFT = 20U;

struct Limits {
    uint64_t currentBytes = 64ULL << MIB_SHIFT;
    uint64_t peakBytes = 128ULL << MIB_SHIFT;
};

struct Snapshot {
    std::array<aclrtMemUsageInfo, MAX_COMPONENTS> entries{};
    size_t count = 0U;
};

struct RuntimeResources {
    bool initialized = false;
    bool deviceSet = false;
};

int32_t ParseLimit(const char* text, uint64_t& bytes)
{
    uint64_t mib = 0U;
    const char* end = text + std::strlen(text);
    const auto parsed = std::from_chars(text, end, mib);
    if (parsed.ec != std::errc{} || parsed.ptr != end || mib == 0U ||
        mib > (std::numeric_limits<uint64_t>::max() >> MIB_SHIFT)) {
        ERROR_LOG("Limits must be positive decimal MiB values without byte overflow");
        return -1;
    }
    bytes = mib << MIB_SHIFT;
    return 0;
}

int32_t ParseArguments(int32_t argc, char** argv, Limits& limits)
{
    if (argc > 3) {
        ERROR_LOG("Usage: %s [current_limit_mib [peak_limit_mib]]", argv[0]);
        return -1;
    }
    if (argc >= 2 && ParseLimit(argv[1], limits.currentBytes) != 0) {
        return -1;
    }
    if (argc == 3 && ParseLimit(argv[2], limits.peakBytes) != 0) {
        return -1;
    }
    return 0;
}

int32_t InitializeRuntime(RuntimeResources& resources)
{
    // Bind one visible device for the diagnostic snapshot.
    CHECK_ERROR(aclInit(nullptr));
    resources.initialized = true;
    CHECK_ERROR(aclrtSetDevice(DEVICE_ID));
    resources.deviceSet = true;
    return 0;
}

int32_t QuerySnapshot(Snapshot& snapshot)
{
    // Retry full arrays so a truncated ranking cannot become a complete report.
    size_t capacity = INITIAL_CAPACITY;
    while (capacity <= MAX_COMPONENTS) {
        size_t outputNum = 0U;
        CHECK_ERROR(aclrtGetMemUsageInfo(DEVICE_ID, snapshot.entries.data(), capacity, &outputNum));
        if (outputNum == 0U || outputNum > capacity) {
            ERROR_LOG("Invalid component count: %zu for capacity %zu", outputNum, capacity);
            return -1;
        }
        if (outputNum < capacity) {
            snapshot.count = outputNum;
            INFO_LOG(
                "Complete component snapshot: device=%d components=%zu capacity=%zu", DEVICE_ID, outputNum, capacity);
            return 0;
        }
        capacity *= 2U;
    }
    ERROR_LOG("Snapshot may be truncated at %zu entries; increase the sample capacity guard", MAX_COMPONENTS);
    return -1;
}

int32_t ValidateSnapshot(const Snapshot& snapshot)
{
    // Validate names, byte counters, and the documented current-usage ordering.
    if (snapshot.count == 0U || snapshot.count > snapshot.entries.size()) {
        ERROR_LOG("Snapshot has no valid component range");
        return -1;
    }
    for (size_t index = 0U; index < snapshot.count; ++index) {
        const auto& entry = snapshot.entries[index];
        if (entry.name[0] == '\0' || std::memchr(entry.name, '\0', sizeof(entry.name)) == nullptr ||
            entry.curMemSize > entry.memPeakSize) {
            ERROR_LOG("Invalid component name or current/peak counters at index %zu", index);
            return -1;
        }
        if (index > 0U && snapshot.entries[index - 1U].curMemSize < entry.curMemSize) {
            ERROR_LOG("Current memory usage is not sorted at index %zu", index);
            return -1;
        }
    }
    INFO_LOG("Verified component names, current <= peak, and descending current usage");
    return 0;
}

void PrintTriage(const Snapshot& snapshot, const Limits& limits)
{
    // Prioritize current pressure; otherwise review the largest historical peak.
    size_t peakIndex = 0U;
    INFO_LOG(
        "Per-component limits: current=%" PRIu64 " bytes peak=%" PRIu64 " bytes", limits.currentBytes,
        limits.peakBytes);
    for (size_t index = 0U; index < snapshot.count; ++index) {
        const auto& entry = snapshot.entries[index];
        INFO_LOG(
            "Component[%zu] %s current=%" PRIu64 " bytes peak=%" PRIu64 " bytes", index, entry.name, entry.curMemSize,
            entry.memPeakSize);
        if (entry.memPeakSize > snapshot.entries[peakIndex].memPeakSize) {
            peakIndex = index;
        }
    }
    const auto& largestCurrent = snapshot.entries[0];
    const auto& largestPeak = snapshot.entries[peakIndex];
    if (largestCurrent.curMemSize >= limits.currentBytes) {
        INFO_LOG("Triage: CURRENT_PRESSURE component=%s; inspect current component usage", largestCurrent.name);
    } else if (largestPeak.memPeakSize >= limits.peakBytes) {
        INFO_LOG("Triage: HISTORICAL_PEAK component=%s; review peak history", largestPeak.name);
    } else {
        INFO_LOG("Triage: WITHIN_BUDGET; all reported components are below both limits");
    }
}

void RecordCleanupError(const char* apiName, aclError error, int32_t& result)
{
    if (error != ACL_SUCCESS) {
        ERROR_LOG("Cleanup failed: %s returned error code %d", apiName, static_cast<int32_t>(error));
        result = -1;
    }
}

void Cleanup(RuntimeResources& resources, int32_t& result)
{
    // Preserve a prior failure and attempt every acquired runtime cleanup.
    if (resources.deviceSet) {
        RecordCleanupError("aclrtResetDevice", aclrtResetDevice(DEVICE_ID), result);
        resources.deviceSet = false;
    }
    if (resources.initialized) {
        RecordCleanupError("aclFinalize", aclFinalize(), result);
        resources.initialized = false;
    }
}
} // namespace

int32_t main(int32_t argc, char** argv)
{
    Limits limits;
    if (ParseArguments(argc, argv, limits) != 0) {
        return 1;
    }
    RuntimeResources resources;
    Snapshot snapshot;
    int32_t result = InitializeRuntime(resources);
    if (result == 0) {
        result = QuerySnapshot(snapshot);
    }
    if (result == 0) {
        result = ValidateSnapshot(snapshot);
    }
    if (result == 0) {
        PrintTriage(snapshot, limits);
    }
    Cleanup(resources, result);
    if (result != 0) {
        ERROR_LOG("Component memory triage failed");
        return 1;
    }
    INFO_LOG("Component memory triage succeeded");
    return 0;
}
