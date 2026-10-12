/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 * This program is free software, you can redistribute it and/or modify it under the terms and conditions of
 * CANN Open Software License Agreement Version 2.0 (the "License").
 * Please refer to the License for details. You may not use this file except in compliance with the License.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 * See LICENSE in the root of the software repository for the full text of the License.
 */

#include "npu_driver.hpp"
#include "driver/ascend_hal.h"
#include "errcode_manage.hpp"

namespace cce {
namespace runtime {
rtError_t NpuDriver::MemGetAddrSegOfUB(
    uint32_t devId, uint64_t hostAddr, uint64_t cpySize, struct addr_range* outRange, uint32_t* outRangeCnt)
{
    NULL_PTR_RETURN(outRange, RT_ERROR_INVALID_VALUE);
    NULL_PTR_RETURN(outRangeCnt, RT_ERROR_INVALID_VALUE);
    const uint32_t rangeCapacity = *outRangeCnt;
    COND_RETURN_ERROR(rangeCapacity == 0U, RT_ERROR_INVALID_VALUE, "The host address segment capacity is zero.");
    COND_RETURN_WARN(
        &halMemGetAddrSeg == nullptr, RT_ERROR_FEATURE_NOT_SUPPORT, "[drv api] halMemGetAddrSeg does not exist.");

    struct addr_range rangeIn = {};
    rangeIn.addr = hostAddr;
    rangeIn.size = cpySize;
    uint32_t drvRangeCnt = rangeCapacity;
    const drvError_t drvRet = halMemGetAddrSeg(devId, rangeIn, outRange, &drvRangeCnt, 0ULL);
    if (drvRet != DRV_ERROR_NONE) {
        DRV_ERROR_PROCESS(
            drvRet, "Call driver api halMemGetAddrSeg failed, drvRetCode=%d, drvDevId=%u.",
            static_cast<int32_t>(drvRet), devId);
        return RT_GET_DRV_ERRCODE(drvRet);
    }
    if ((drvRangeCnt == 0U) || (drvRangeCnt > rangeCapacity)) {
        RT_LOG(
            RT_LOG_ERROR,
            "Invalid output of halMemGetAddrSeg, drvDevId=%u, segmentCapacity=%u, segmentCnt=%u, ranges=%p.", devId,
            rangeCapacity, drvRangeCnt, static_cast<void*>(outRange));
        return RT_ERROR_DRV_ERR;
    }
    *outRangeCnt = drvRangeCnt;
    RT_LOG(
        RT_LOG_DEBUG, "halMemGetAddrSeg success, drvDevId=%u, segmentCapacity=%u, segmentCnt=%u.", devId, rangeCapacity,
        drvRangeCnt);
    return RT_ERROR_NONE;
}

} // namespace runtime
} // namespace cce
