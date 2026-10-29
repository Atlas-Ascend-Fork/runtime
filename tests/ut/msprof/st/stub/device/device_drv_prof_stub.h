/**
 * Copyright (c) 2025 Huawei Technologies Co., Ltd.
 * This program is free software, you can redistribute it and/or modify it under the terms and conditions of
 * CANN Open Software License Agreement Version 2.0 (the "License").
 * Please refer to the License for details. You may not use this file except in compliance with the License.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 * See LICENSE in the root of the software repository for the full text of the License.
 */

#ifndef DEVICE_DRV_PROF_STUB_H
#define DEVICE_DRV_PROF_STUB_H

#include <vector>
#include <map>

#include "ascend_hal.h"
#include "ascend_inpackage_hal.h"
extern "C" drvError_t halGetDeviceInfoByBuff(
    uint32_t devId, int32_t moduleType, int32_t infoType, void* value, int32_t* len);
extern "C" drvError_t drvGetDeviceSplitMode(unsigned int dev_id, unsigned int* mode);

namespace Cann {
namespace Dvvp {
namespace Test {
void ResetQosProfileQueryCountForTest();
uint32_t GetQosStreamListCountForTest();
const std::map<uint32_t, std::vector<uint8_t>>& GetQosQueriedMpamIdsByDeviceForTest();
int32_t GetLowPowerPeriodUsForTest();
bool GetLowPowerEnabledForTest();
void RecordStarsSocProfileConfigForTest(uint32_t channelId, const void* userData, uint32_t userDataSize);
} // namespace Test
} // namespace Dvvp
} // namespace Cann

extern "C" int halProfDataFlush(unsigned int deviceId, unsigned int channelId, unsigned int* bufSize);
#endif
