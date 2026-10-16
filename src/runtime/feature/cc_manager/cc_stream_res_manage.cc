/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 * This program is free software, you can redistribute it and/or modify it under the terms and conditions of
 * CANN Open Software License Agreement Version 2.0 (the "License").
 * Please refer to the License for details. You may not use this file except in compliance with the License.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 * See LICENSE in the root of the software repository for the full text of the License.
 */
#include "cc_stream_res_manage.h"

#include <cstring>

#include "device.hpp"
#include "driver.hpp"
#include "type_def.h"

namespace cce {
namespace runtime {
namespace {
constexpr uint64_t CC_BAR_RESOURCE_SIZE = sizeof(CCSliceQueue) + sizeof(CCSliceDesc) * CC_SLICE_DESC_SLOT_NUM;
}

CCStreamResManage::~CCStreamResManage() { Destroy(); }

rtError_t CCStreamResManage::Init(Device* device)
{
    COND_RETURN_ERROR(device == nullptr, RT_ERROR_DEVICE_NULL, "CC stream resource device is null.");
    COND_RETURN_ERROR(device->Driver_() == nullptr, RT_ERROR_DRV_NULL, "CC stream resource driver is null.");
    device_ = device;

    rtError_t ret = device_->Driver_()->DevMemAlloc(
        &barDeviceAddr_, CC_BAR_RESOURCE_SIZE, RT_MEMORY_P2P_HBM, device_->Id_(), MODULEID_RUNTIME);
    if (ret != RT_ERROR_NONE) {
        Destroy();
        return ret;
    }

    void* mappedAddr = nullptr;
    ret = device_->Driver_()->PcieHostRegister(barDeviceAddr_, CC_BAR_RESOURCE_SIZE, device_->Id_(), mappedAddr);
    if (ret != RT_ERROR_NONE) {
        Destroy();
        return ret;
    }
    barRegistered_ = true;
    barHostAddr_ = (mappedAddr == nullptr) ? barDeviceAddr_ : mappedAddr;

    (void)std::memset(barHostAddr_, 0, CC_BAR_RESOURCE_SIZE);
    CCSliceQueue* const queue = Queue();
    queue->depth = static_cast<uint8_t>(CC_SLICE_DESC_SLOT_NUM);
    return RT_ERROR_NONE;
}

void CCStreamResManage::Destroy()
{
    if (device_ == nullptr) {
        return;
    }
    Driver* const driver = device_->Driver_();
    if (driver != nullptr) {
        if (barRegistered_ && (barDeviceAddr_ != nullptr)) {
            rtError_t ret = driver->PcieHostUnRegister(barDeviceAddr_, device_->Id_());
            if (ret != RT_ERROR_NONE) {
                RT_LOG(RT_LOG_ERROR, "CC stream resource: PcieHostUnRegister failed, ret=%#x", ret);
            }
        }
        if (barDeviceAddr_ != nullptr) {
            (void)driver->DevMemFree(barDeviceAddr_, device_->Id_());
        }
    }
    barRegistered_ = false;
    barDeviceAddr_ = nullptr;
    barHostAddr_ = nullptr;
    device_ = nullptr;
}

void CCStreamResManage::Reset()
{
    CCSliceQueue* const queue = Queue();
    CCSliceDesc* const sliceDesc = SliceDesc();
    if ((queue == nullptr) || (sliceDesc == nullptr)) {
        return;
    }
    queue->totalSlices = 0U;
    queue->head = 0U;
    queue->tail = 0U;
    queue->depth = static_cast<uint8_t>(CC_SLICE_DESC_SLOT_NUM);
}

CCSliceQueue* CCStreamResManage::Queue() const { return PtrToPtr<void, CCSliceQueue>(barHostAddr_); }

CCSliceDesc* CCStreamResManage::SliceDesc() const
{
    CCSliceQueue* const queue = Queue();
    if (queue == nullptr) {
        return nullptr;
    }
    return queue->sliceDesc;
}

uint64_t CCStreamResManage::DeviceQueueAddr() const { return PtrToValue(barDeviceAddr_); }

std::mutex& CCStreamResManage::MemSubmitMutex() { return memSubmitMutex_; }

} // namespace runtime
} // namespace cce
