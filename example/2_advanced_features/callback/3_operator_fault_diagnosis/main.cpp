/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 * This program is free software, you can redistribute it and/or modify it under the terms and conditions of
 * CANN Open Software License Agreement Version 2.0 (the "License").
 * Please refer to the License for details. You may not use this file except in compliance with the License.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 * See LICENSE in the root of the software repository for the full text of the License.
 */

#include <atomic>
#include <chrono>
#include <cstdint>
#include <thread>

#include "acl/acl.h"
#include "utils.h"

namespace {
constexpr int32_t kDeviceId = 0;
constexpr int32_t kSyncTimeoutMs = 30000;
constexpr uint32_t kInput = 41U;
constexpr char kBinaryPath[] = "./operator_fault_kernel.o";

struct Event {
    uint32_t device = 0U;
    uint32_t stream = 0U;
    uint32_t task = 0U;
    uint32_t error = 0U;
};

struct Snapshot {
    std::atomic<bool> claimed{false};
    std::atomic<bool> ready{false};
    Event event;
    aclrtFuncHandle function = nullptr;
    aclError queryResult = ACL_SUCCESS;
};

struct Diagnostics {
    Snapshot process;
    Snapshot binary;
    std::atomic<uint32_t> retiredCalls{0U};
    std::atomic<bool> invalidCallback{false};
};

// Static storage outlives notifications already in flight when callbacks are unregistered.
Diagnostics g_diagnostics;

struct Resources {
    aclrtStream stream = nullptr;
    aclrtBinHandle binary = nullptr;
    aclrtFuncHandle function = nullptr;
    void* output = nullptr;
    bool initialized = false;
    bool deviceSet = false;
    bool processRegistered = false;
    bool retiredRegistered = false;
    bool pending = false;
};

struct KernelArgs {
    void* output;
    uint32_t input;
    uint32_t injectFault;
};

void CaptureEvent(const aclrtExceptionInfo* info, Event& event)
{
    event.device = aclrtGetDeviceIdFromExceptionInfo(info);
    event.stream = aclrtGetStreamIdFromExceptionInfo(info);
    event.task = aclrtGetTaskIdFromExceptionInfo(info);
    event.error = aclrtGetErrorCodeFromExceptionInfo(info);
}

void ProcessException(aclrtExceptionInfo* info) noexcept
{
    if (info == nullptr) {
        g_diagnostics.invalidCallback.store(true);
        return;
    }
    Snapshot& snapshot = g_diagnostics.process;
    if (!snapshot.claimed.exchange(true)) {
        CaptureEvent(info, snapshot.event);
        snapshot.ready.store(true, std::memory_order_release);
    }
}

void RetiredException(aclrtExceptionInfo*) noexcept { g_diagnostics.retiredCalls.fetch_add(1U); }

void BinaryException(aclrtExceptionInfo* info, void* userData) noexcept
{
    if (info == nullptr || userData != &g_diagnostics) {
        g_diagnostics.invalidCallback.store(true);
        return;
    }
    Snapshot& snapshot = g_diagnostics.binary;
    if (!snapshot.claimed.exchange(true)) {
        CaptureEvent(info, snapshot.event);
        snapshot.queryResult = aclrtGetFuncHandleFromExceptionInfo(info, &snapshot.function);
        snapshot.ready.store(true, std::memory_order_release);
    }
}

int Initialize(Resources& resources)
{
    // Initialize one Device and stop the Stream when the injected task fails.
    CHECK_ERROR(aclInit(nullptr));
    resources.initialized = true;
    CHECK_ERROR(aclrtSetDevice(kDeviceId));
    resources.deviceSet = true;
    CHECK_ERROR(aclrtCreateStream(&resources.stream));
    CHECK_ERROR(aclrtSetStreamFailureMode(resources.stream, ACL_STOP_ON_FAILURE));
    CHECK_ERROR(aclrtMalloc(&resources.output, sizeof(uint32_t), ACL_MEM_MALLOC_HUGE_FIRST));
    CHECK_ERROR(aclrtBinaryLoadFromFile(kBinaryPath, nullptr, &resources.binary));
    CHECK_ERROR(aclrtBinaryGetFunction(resources.binary, "checked_increment", &resources.function));
    return 0;
}

int RegisterDiagnostics(Resources& resources)
{
    // Remove a temporary observer before submission; keep the service observer active.
    CHECK_ERROR(aclrtExceptionInfoCallbackRegister(ProcessException));
    resources.processRegistered = true;
    CHECK_ERROR(aclrtExceptionInfoCallbackRegister(RetiredException));
    resources.retiredRegistered = true;
    CHECK_ERROR(aclrtExceptionInfoCallbackUnregister(RetiredException));
    resources.retiredRegistered = false;
    CHECK_ERROR(aclrtBinarySetExceptionCallback(resources.binary, BinaryException, &g_diagnostics));
    return 0;
}

int Launch(Resources& resources, uint32_t injectFault)
{
    KernelArgs args{resources.output, kInput, injectFault};
    CHECK_ERROR(aclrtLaunchKernelWithHostArgs(
        resources.function, 1U, resources.stream, nullptr, &args, sizeof(KernelArgs), nullptr, 0U));
    resources.pending = true;
    return 0;
}

int VerifyHealthyTask(Resources& resources)
{
    // Verify useful work before exercising the fault path of the same operator.
    CHECK_ERROR(aclrtMemset(resources.output, sizeof(uint32_t), 0, sizeof(uint32_t)));
    if (Launch(resources, 0U) != 0) {
        return -1;
    }
    CHECK_ERROR(aclrtSynchronizeStreamWithTimeout(resources.stream, kSyncTimeoutMs));
    resources.pending = false;
    uint32_t actual = 0U;
    CHECK_ERROR(aclrtMemcpy(&actual, sizeof(uint32_t), resources.output, sizeof(uint32_t), ACL_MEMCPY_DEVICE_TO_HOST));
    if (actual != kInput + 1U || g_diagnostics.process.claimed.load() || g_diagnostics.binary.claimed.load() ||
        g_diagnostics.retiredCalls.load() != 0U || g_diagnostics.invalidCallback.load()) {
        ERROR_LOG("Healthy task failed validation: output=%u, expected=%u.", actual, kInput + 1U);
        return -1;
    }
    INFO_LOG("Healthy task verified: %u + 1 = %u; no exception notification.", kInput, actual);
    return 0;
}

bool WaitForDiagnostics()
{
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
    while (std::chrono::steady_clock::now() < deadline) {
        if (g_diagnostics.process.ready.load(std::memory_order_acquire) &&
            g_diagnostics.binary.ready.load(std::memory_order_acquire)) {
            return true;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    ERROR_LOG("Timed out waiting for process and binary exception notifications.");
    return false;
}

bool MatchesTask(const Event& event, uint32_t task, uint32_t stream)
{
    return event.device == static_cast<uint32_t>(kDeviceId) && event.stream == stream && event.task == task &&
           event.error != 0U;
}

int VerifyDiagnostics(const Resources& resources, uint32_t task, uint32_t stream)
{
    if (!WaitForDiagnostics()) {
        return -1;
    }
    const Snapshot& process = g_diagnostics.process;
    const Snapshot& binary = g_diagnostics.binary;
    INFO_LOG(
        "Process fault: device=%u, stream=%u, task=%u, error=%u.", process.event.device, process.event.stream,
        process.event.task, process.event.error);
    INFO_LOG(
        "Binary fault: device=%u, stream=%u, task=%u, error=%u.", binary.event.device, binary.event.stream,
        binary.event.task, binary.event.error);
    if (!MatchesTask(process.event, task, stream) || !MatchesTask(binary.event, task, stream) ||
        process.event.error != binary.event.error || binary.queryResult != ACL_SUCCESS ||
        binary.function != resources.function || g_diagnostics.invalidCallback.load() ||
        g_diagnostics.retiredCalls.load() != 0U) {
        ERROR_LOG(
            "Fault attribution failed: expected stream=%u, task=%u; function query=%d, retired calls=%u.", stream, task,
            static_cast<int32_t>(binary.queryResult), g_diagnostics.retiredCalls.load());
        return -1;
    }
    INFO_LOG("Fault attributed to checked_increment; retired observer calls=0.");
    return 0;
}

int DiagnoseFault(Resources& resources)
{
    // A controlled trap uses valid arguments and deliberately produces a Device task error.
    INFO_LOG("Injecting one operator fault; a Runtime task error is expected.");
    int32_t stream = 0;
    CHECK_ERROR(aclrtStreamGetId(resources.stream, &stream));
    if (Launch(resources, 1U) != 0) {
        return -1;
    }
    uint32_t task = 0U;
    CHECK_ERROR(aclrtGetThreadLastTaskId(&task));
    const aclError syncResult = aclrtSynchronizeStreamWithTimeout(resources.stream, kSyncTimeoutMs);
    if (syncResult == ACL_SUCCESS || syncResult == ACL_ERROR_RT_STREAM_SYNC_TIMEOUT) {
        ERROR_LOG("Expected an operator execution error, got %d.", static_cast<int32_t>(syncResult));
        return -1;
    }
    INFO_LOG("Fault synchronization returned %d (expected execution failure).", static_cast<int32_t>(syncResult));
    return VerifyDiagnostics(resources, task, static_cast<uint32_t>(stream));
}

void RecordCleanup(const char* operation, aclError error, int& result)
{
    if (error != ACL_SUCCESS) {
        ERROR_LOG("Cleanup failed: %s returned %d.", operation, static_cast<int32_t>(error));
        result = -1;
    }
}

void Release(Resources& resources, int& result)
{
    // Force-destroy the failed Stream before unloading code or releasing its arguments.
    if (resources.stream != nullptr) {
        if (resources.pending) {
            RecordCleanup("aclrtDestroyStreamForce", aclrtDestroyStreamForce(resources.stream), result);
        } else {
            RecordCleanup("aclrtDestroyStream", aclrtDestroyStream(resources.stream), result);
        }
        resources.stream = nullptr;
    }
    if (resources.binary != nullptr) {
        RecordCleanup("aclrtBinaryUnLoad", aclrtBinaryUnLoad(resources.binary), result);
        resources.binary = nullptr;
        resources.function = nullptr;
    }
    if (resources.output != nullptr) {
        RecordCleanup("aclrtFree", aclrtFree(resources.output), result);
        resources.output = nullptr;
    }
    if (resources.retiredRegistered) {
        RecordCleanup(
            "aclrtExceptionInfoCallbackUnregister(retired)", aclrtExceptionInfoCallbackUnregister(RetiredException),
            result);
    }
    if (resources.processRegistered) {
        RecordCleanup(
            "aclrtExceptionInfoCallbackUnregister(process)", aclrtExceptionInfoCallbackUnregister(ProcessException),
            result);
    }
    if (resources.deviceSet) {
        RecordCleanup("aclrtResetDeviceForce", aclrtResetDeviceForce(kDeviceId), result);
    }
    if (resources.initialized) {
        RecordCleanup("aclFinalize", aclFinalize(), result);
    }
}
} // namespace

int main()
{
    Resources resources;
    int result = Initialize(resources);
    if (result == 0) {
        result = RegisterDiagnostics(resources);
    }
    if (result == 0) {
        result = VerifyHealthyTask(resources);
    }
    if (result == 0) {
        result = DiagnoseFault(resources);
    }
    Release(resources, result);
    if (result != 0) {
        ERROR_LOG("Run the 3_operator_fault_diagnosis sample failed.");
        return 1;
    }
    INFO_LOG("Run the 3_operator_fault_diagnosis sample successfully.");
    return 0;
}
