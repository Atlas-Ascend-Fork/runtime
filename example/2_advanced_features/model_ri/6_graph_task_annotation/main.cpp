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
#include <cstdint>
#include <fstream>
#include <string>

#include "acl/acl.h"
#include "utils.h"

namespace {
constexpr int32_t DEVICE_ID = 0;
constexpr size_t BATCH_COUNT = 2;
constexpr size_t BATCH_BYTES = 4096;
constexpr size_t OUTPUT_BYTES = BATCH_COUNT * BATCH_BYTES;
constexpr size_t TASK_COUNT = BATCH_COUNT * 2;
constexpr const char* TRACE_PATH = "graph_task_annotations.json";

struct Annotation {
    std::string opInfo;
    std::string extendInfo;
};

struct Resources {
    bool initialized = false;
    bool deviceSet = false;
    bool capturing = false;
    bool cacheEnabled = false;
    void* scratch = nullptr;
    void* output = nullptr;
    aclrtStream stream = nullptr;
    aclmdlRI model = nullptr;
};

Annotation MakeAnnotation(size_t batch, bool archive)
{
    const std::string op = archive ? "ArchiveBatch" : "FillBatchMarker";
    const std::string phase = archive ? "archive" : "prepare";
    const std::string description = archive ? "Preserve the batch buffer" : "Initialize the batch buffer";
    Annotation annotation;
    annotation.opInfo =
        "{\"op_name\":\"" + op + "\",\"dtype\":\"uint8\",\"elements\":" + std::to_string(BATCH_BYTES) + "}";
    annotation.extendInfo = "{\"business_phase\":\"" + phase + "\",\"batch_id\":" + std::to_string(batch) +
                            ",\"op_name\":\"" + op + "\",\"description\":\"" + description +
                            "\",\"dtype\":\"uint8\",\"elements\":" + std::to_string(BATCH_BYTES) +
                            ",\"marker\":" + std::to_string((batch + 1) * 17) + "}";
    return annotation;
}

int32_t Initialize(Resources& resources)
{
    // Initialize one device and allocate graph-owned buffers before capture.
    CHECK_ERROR(aclInit(nullptr));
    resources.initialized = true;
    CHECK_ERROR(aclrtSetDevice(DEVICE_ID));
    resources.deviceSet = true;
    CHECK_ERROR(aclrtMalloc(&resources.scratch, BATCH_BYTES, ACL_MEM_MALLOC_HUGE_FIRST));
    CHECK_ERROR(aclrtMalloc(&resources.output, OUTPUT_BYTES, ACL_MEM_MALLOC_HUGE_FIRST));
    CHECK_ERROR(aclrtCreateStream(&resources.stream));
    CHECK_ERROR(aclrtMemset(resources.output, OUTPUT_BYTES, 0xCC, OUTPUT_BYTES));
    return 0;
}

int32_t SetCacheSwitch(Resources& resources, uint32_t enabled)
{
    aclrtStreamAttrValue value = {};
    value.cacheOpInfoSwitch = enabled;
    CHECK_ERROR(aclrtSetStreamAttribute(resources.stream, ACL_STREAM_ATTR_CACHE_OP_INFO, &value));
    resources.cacheEnabled = enabled != 0;
    CHECK_ERROR(aclrtGetStreamAttribute(resources.stream, ACL_STREAM_ATTR_CACHE_OP_INFO, &value));
    if (value.cacheOpInfoSwitch != enabled) {
        ERROR_LOG("Unexpected operator info cache switch: %u", value.cacheOpInfoSwitch);
        return -1;
    }
    return 0;
}

int32_t AnnotateLastTask(aclrtStream stream, const Annotation& annotation)
{
    aclrtStreamAttrValue value = {};
    CHECK_ERROR(aclrtGetStreamAttribute(stream, ACL_STREAM_ATTR_CACHE_OP_INFO, &value));
    if (value.cacheOpInfoSwitch != 1) {
        ERROR_LOG("Operator info caching must be enabled during capture");
        return -1;
    }
    if (annotation.opInfo.empty() || annotation.opInfo.size() > 65536 || annotation.extendInfo.empty() ||
        annotation.extendInfo.size() > 4096) {
        ERROR_LOG("Annotation exceeds the operator or extended info size limit");
        return -1;
    }
    // Both calls target the last submitted task in this host thread.
    CHECK_ERROR(aclrtCacheLastTaskOpInfo(annotation.opInfo.data(), annotation.opInfo.size()));
    CHECK_ERROR(aclrtCacheLastTaskExtendInfo(annotation.extendInfo.data(), annotation.extendInfo.size()));
    return 0;
}

int32_t RecordBatches(Resources& resources, const std::array<Annotation, TASK_COUNT>& annotations)
{
    // Keep submission and annotation together; no other task may intervene.
    auto* output = static_cast<uint8_t*>(resources.output);
    for (size_t batch = 0; batch < BATCH_COUNT; ++batch) {
        const int32_t marker = static_cast<int32_t>((batch + 1) * 17);
        CHECK_ERROR(aclrtMemsetAsync(resources.scratch, BATCH_BYTES, marker, BATCH_BYTES, resources.stream));
        if (AnnotateLastTask(resources.stream, annotations[batch * 2]) != 0) {
            return -1;
        }
        CHECK_ERROR(aclrtMemcpyAsync(
            output + batch * BATCH_BYTES, BATCH_BYTES, resources.scratch, BATCH_BYTES, ACL_MEMCPY_DEVICE_TO_DEVICE,
            resources.stream));
        if (AnnotateLastTask(resources.stream, annotations[batch * 2 + 1]) != 0) {
            return -1;
        }
    }
    return 0;
}

int32_t CaptureGraph(Resources& resources, const std::array<Annotation, TASK_COUNT>& annotations)
{
    // Begin capture, enable annotations, record tasks, then close the switch.
    CHECK_ERROR(aclmdlRICaptureBegin(resources.stream, ACL_MODEL_RI_CAPTURE_MODE_THREAD_LOCAL));
    resources.capturing = true;
    if (SetCacheSwitch(resources, 1) != 0 || RecordBatches(resources, annotations) != 0 ||
        SetCacheSwitch(resources, 0) != 0) {
        return -1;
    }
    const aclError result = aclmdlRICaptureEnd(resources.stream, &resources.model);
    resources.capturing = false;
    CHECK_ERROR(result);
    if (resources.model == nullptr) {
        ERROR_LOG("Capture returned an empty model");
        return -1;
    }
    return 0;
}

int32_t ExportGraph(aclmdlRI model)
{
    // Create a fresh writable file so an earlier export cannot pass validation.
    std::ofstream trace(TRACE_PATH, std::ios::trunc);
    if (!trace.is_open()) {
        ERROR_LOG("Cannot create %s", TRACE_PATH);
        return -1;
    }
    trace.close();
    if (trace.fail()) {
        ERROR_LOG("Cannot close %s", TRACE_PATH);
        return -1;
    }
    CHECK_ERROR(aclmdlRIDebugJsonPrint(model, TRACE_PATH, ACL_MDLRI_DEBUG_JSON_PRINT_SUMMARY));
    INFO_LOG("Exported annotated graph: %s", TRACE_PATH);
    return 0;
}

int32_t ExecuteAndVerify(const Resources& resources)
{
    // Execute only after capture and export; verify both archived batches.
    CHECK_ERROR(aclmdlRIExecuteAsync(resources.model, resources.stream));
    CHECK_ERROR(aclrtSynchronizeStream(resources.stream));
    std::array<uint8_t, OUTPUT_BYTES> output = {};
    CHECK_ERROR(aclrtMemcpy(output.data(), output.size(), resources.output, OUTPUT_BYTES, ACL_MEMCPY_DEVICE_TO_HOST));
    for (size_t batch = 0; batch < BATCH_COUNT; ++batch) {
        const uint8_t expected = static_cast<uint8_t>((batch + 1) * 17);
        for (size_t offset = 0; offset < BATCH_BYTES; ++offset) {
            const uint8_t actual = output[batch * BATCH_BYTES + offset];
            if (actual != expected) {
                ERROR_LOG(
                    "Batch %zu, byte %zu: expected %u, got %u", batch, offset, static_cast<unsigned int>(expected),
                    static_cast<unsigned int>(actual));
                return -1;
            }
        }
        INFO_LOG("Batch %zu verified: %zu bytes, marker=%u", batch, BATCH_BYTES, static_cast<unsigned int>(expected));
    }
    return 0;
}

void RecordCleanup(const char* operation, aclError error, int32_t& result)
{
    if (error != ACL_SUCCESS) {
        ERROR_LOG("Cleanup failed: %s returned error code %d", operation, static_cast<int32_t>(error));
        result = -1;
    }
}

void FinishCapture(Resources& resources, int32_t& result)
{
    if (resources.cacheEnabled) {
        aclrtStreamAttrValue value = {};
        value.cacheOpInfoSwitch = 0;
        RecordCleanup(
            "aclrtSetStreamAttribute", aclrtSetStreamAttribute(resources.stream, ACL_STREAM_ATTR_CACHE_OP_INFO, &value),
            result);
        resources.cacheEnabled = false;
    }
    if (resources.capturing) {
        RecordCleanup("aclmdlRICaptureEnd", aclmdlRICaptureEnd(resources.stream, &resources.model), result);
        resources.capturing = false;
    }
}

void Cleanup(Resources& resources, int32_t& result)
{
    // End unfinished capture, synchronize, and release the model before its buffers.
    FinishCapture(resources, result);
    if (resources.stream != nullptr) {
        RecordCleanup("aclrtSynchronizeStream", aclrtSynchronizeStream(resources.stream), result);
    }
    if (resources.model != nullptr) {
        RecordCleanup("aclmdlRIDestroy", aclmdlRIDestroy(resources.model), result);
    }
    if (resources.stream != nullptr) {
        RecordCleanup("aclrtDestroyStream", aclrtDestroyStream(resources.stream), result);
    }
    if (resources.output != nullptr) {
        RecordCleanup("aclrtFree(output)", aclrtFree(resources.output), result);
    }
    if (resources.scratch != nullptr) {
        RecordCleanup("aclrtFree(scratch)", aclrtFree(resources.scratch), result);
    }
    if (resources.deviceSet) {
        RecordCleanup("aclrtResetDeviceForce", aclrtResetDeviceForce(DEVICE_ID), result);
    }
    if (resources.initialized) {
        RecordCleanup("aclFinalize", aclFinalize(), result);
    }
}
} // namespace

int32_t main()
{
    Resources resources;
    std::array<Annotation, TASK_COUNT> annotations;
    for (size_t batch = 0; batch < BATCH_COUNT; ++batch) {
        annotations[batch * 2] = MakeAnnotation(batch, false);
        annotations[batch * 2 + 1] = MakeAnnotation(batch, true);
    }
    int32_t result = Initialize(resources);
    if (result == 0) {
        result = CaptureGraph(resources, annotations);
    }
    if (result == 0) {
        result = ExportGraph(resources.model);
    }
    if (result == 0) {
        result = ExecuteAndVerify(resources);
    }
    Cleanup(resources, result);
    if (result != 0) {
        ERROR_LOG("Graph task annotation sample failed");
        return 1;
    }
    INFO_LOG("Graph execution and data verification passed");
    return 0;
}
