/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 * This program is free software, you can redistribute it and/or modify it under the terms and conditions of
 * CANN Open Software License Agreement Version 2.0 (the "License").
 * Please refer to the License for details. You may not use this file except in compliance with the License.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 * See LICENSE in the root of the software repository for the full text of the License.
 */

#include "cc_res_manage.h"
#include "cc_stream_res_manage.h"
#include "cc_worker.h"

#include "aicpu_c.hpp"
#include "base.hpp"
#include "device.hpp"
#include "runtime.hpp"
#include "stream.hpp"
#include "stream_sqcq_manage.hpp"
#include "logger.hpp"

namespace cce {
namespace runtime {

namespace {
constexpr const char_t* AICC_LOAD_KEY_KERNEL_NAME = "AiccLoadKey";

rtError_t LaunchAiccLoadKeyKernel(Stream* const stm, CCLoadKeyKernelParam& param)
{
    COND_RETURN_ERROR(stm == nullptr, RT_ERROR_STREAM_NULL, "CC load key stream is null.");

    rtKernelLaunchNames_t launchNames{};
    launchNames.soName = nullptr;
    launchNames.kernelName = AICC_LOAD_KEY_KERNEL_NAME;
    launchNames.opName = AICC_LOAD_KEY_KERNEL_NAME;

    rtArgsEx_t argsInfo{};
    argsInfo.args = &param;
    argsInfo.argsSize = static_cast<uint32_t>(sizeof(param));
    argsInfo.isNoNeedH2DCopy = 0U;

    return StreamLaunchCpuKernel(&launchNames, 1U, &argsInfo, stm, RT_KERNEL_DEFAULT);
}
} // namespace

static constexpr uint32_t CC_WORKER_COUNT = 6;
CCResManage::CCResManage(Device* device) : deviceId_((device == nullptr) ? 0U : device->Id_()), device_(device) {}

CCResManage::~CCResManage() { DestroyCcResource(); }

rtError_t CCResManage::InitCcResource()
{
    COND_RETURN_ERROR(device_ == nullptr, RT_ERROR_DEVICE_NULL, "CCResManage device is null.");
    rtError_t ret = crypto_.InitKey(deviceId_);
    if (ret != RT_ERROR_NONE) {
        RT_LOG(RT_LOG_ERROR, "CC init key failed, device_id=%u, ret=%#x", deviceId_, ret);
        return RT_ERROR_CC_INIT_FAILED;
    }

    ret = LoadKeyToAicpu();
    if (ret != RT_ERROR_NONE) {
        crypto_.ReleaseKey(deviceId_);
        RT_LOG(RT_LOG_ERROR, "CC load key initialization failed, device_id=%u, ret=%#x", deviceId_, ret);
        return RT_ERROR_CC_INIT_FAILED;
    }

    ret = InitWorkerPool(CC_WORKER_COUNT, CC_SLICE_SIZE);
    if (ret != RT_ERROR_NONE) {
        crypto_.ReleaseKey(deviceId_);
        RT_LOG(RT_LOG_ERROR, "CC worker pool init failed, device_id=%u, ret=%#x", deviceId_, ret);
        return RT_ERROR_CC_INIT_FAILED;
    }

    RT_LOG(RT_LOG_INFO, "CCResManage initialized for device %u", deviceId_);
    return RT_ERROR_NONE;
}

rtError_t CCResManage::LoadKeyToAicpu()
{
    Stream* const curStm = device_->GetCtrlSQStream(nullptr);
    COND_RETURN_ERROR(
        curStm == nullptr, RT_ERROR_STREAM_NULL, "CC load key CtrlSQ stream is null, device_id=%u.", deviceId_);

    CCLoadKeyKernelParam param{};
    rtError_t ret = crypto_.BuildLoadKeyParam(&param);
    COND_RETURN_ERROR(
        ret != RT_ERROR_NONE, ret, "Failed to build CC load-key kernel parameters, device_id=%u, retCode=%#x.",
        deviceId_, static_cast<uint32_t>(ret));

    ret = Runtime::Instance()->StartAicpuSd(device_);
    COND_RETURN_ERROR(
        ret != RT_ERROR_NONE, ret,
        "Failed to start AICPU SD before launching the CC load-key kernel, device_id=%u, retCode=%#x.", deviceId_,
        static_cast<uint32_t>(ret));

    ret = LaunchAiccLoadKeyKernel(curStm, param);
    COND_RETURN_ERROR(
        ret != RT_ERROR_NONE, ret, "Failed to launch the CC load-key kernel, device_id=%u, retCode=%#x.", deviceId_,
        static_cast<uint32_t>(ret));

    ret = curStm->Synchronize();
    COND_RETURN_ERROR(
        ret != RT_ERROR_NONE, ret,
        "Failed to synchronize the CC load-key stream, device_id=%u, stream_id=%d, retCode=%#x.", deviceId_,
        curStm->Id_(), static_cast<uint32_t>(ret));

    return RT_ERROR_NONE;
}

void CCResManage::DestroyCcResource()
{
    DestroyWorkerPool();
    crypto_.ReleaseKey(deviceId_);
}

rtError_t CCResManage::GetOrCreateStreamResource(Stream* stm, CCStreamResManage*& resource)
{
    COND_RETURN_ERROR(stm == nullptr, RT_ERROR_STREAM_NULL, "CC stream is null.");
    std::lock_guard<std::mutex> lock(streamResourceMutex_);
    resource = stm->GetCCStreamResource();
    if (resource != nullptr) {
        return RT_ERROR_NONE;
    }

    std::unique_ptr<CCStreamResManage> newResource = std::make_unique<CCStreamResManage>();
    rtError_t ret = newResource->Init(stm->Device_());
    if (ret != RT_ERROR_NONE) {
        return ret;
    }
    resource = newResource.release();
    stm->SetCCStreamResource(resource);
    return RT_ERROR_NONE;
}

void CCResManage::DestroyStreamResource(Stream* stm)
{
    if (stm == nullptr) {
        return;
    }

    if (taskQueue_ != nullptr) {
        taskQueue_->CancelTasksByStream(static_cast<uint32_t>(stm->Id_()));
    }

    CCStreamResManage* resource = nullptr;
    {
        std::lock_guard<std::mutex> lock(streamResourceMutex_);
        resource = stm->TakeCCStreamResource();
    }
    delete resource;
}

rtError_t CCResManage::InitWorkerPool(uint32_t workerCount, uint32_t sliceSize)
{
    std::lock_guard<std::mutex> lock(workerPoolMutex_);
    taskQueue_ = std::make_unique<CCMemcpyTaskQueue>();
    maxWorkerCount_ = workerCount;
    workerSliceSize_ = sliceSize;
    workers_.reserve(workerCount);
    const rtError_t ret = CreateWorker();
    if (ret != RT_ERROR_NONE) {
        RT_LOG(RT_LOG_ERROR, "CC initial worker init failed, devId=%u", device_->Id_());
        DestroyWorkerPoolLocked();
        return ret;
    }

    RT_LOG(
        RT_LOG_INFO, "CC worker pool initialized, devId=%u, workers=%zu, maxWorkers=%u, sliceSize=%u", device_->Id_(),
        workers_.size(), maxWorkerCount_, workerSliceSize_);
    return RT_ERROR_NONE;
}

rtError_t CCResManage::CreateWorker()
{
    if (workers_.size() >= maxWorkerCount_) {
        return RT_ERROR_NONE;
    }

    const uint32_t workerIndex = static_cast<uint32_t>(workers_.size());
    auto worker = std::make_unique<CCWorker>();
    const rtError_t ret = worker->Init(
        device_->Id_() * maxWorkerCount_ + workerIndex, workerSliceSize_, taskQueue_.get(), device_, &crypto_);
    if (ret != RT_ERROR_NONE) {
        return ret;
    }
    workers_.push_back(std::move(worker));
    return RT_ERROR_NONE;
}

void CCResManage::DestroyWorkerPoolLocked()
{
    if (taskQueue_ != nullptr) {
        taskQueue_->Shutdown();
    }

    for (auto& worker : workers_) {
        worker->Destroy();
    }
    workers_.clear();
    taskQueue_.reset();
    maxWorkerCount_ = 0U;
    workerSliceSize_ = 0U;
}

void CCResManage::DestroyWorkerPool()
{
    std::lock_guard<std::mutex> lock(workerPoolMutex_);
    DestroyWorkerPoolLocked();
}

rtError_t CCResManage::SubmitTask(const CCMemcpyTask& task)
{
    std::lock_guard<std::mutex> lock(workerPoolMutex_);
    if (taskQueue_ == nullptr) {
        return RT_ERROR_CC_WORKER_FAILED;
    }

    if (!taskQueue_->Push(task)) {
        return RT_ERROR_CC_WORKER_FAILED;
    }

    const rtError_t ret = CreateWorker();
    if (ret != RT_ERROR_NONE) {
        RT_LOG(
            RT_LOG_WARNING, "CC worker pool expansion failed, devId=%u, workers=%zu, maxWorkers=%u, ret=%#x", deviceId_,
            workers_.size(), maxWorkerCount_, static_cast<uint32_t>(ret));
    }
    return RT_ERROR_NONE;
}

uint32_t CCResManage::BuildDeviceCryptoParam(CC_CRYPTO_MODE mode, CCCryptoKernelParam* param)
{
    return crypto_.BuildDeviceCryptoParam(deviceId_, mode, param);
}

} // namespace runtime
} // namespace cce
