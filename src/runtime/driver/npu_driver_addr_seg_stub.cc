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

namespace cce {
namespace runtime {
rtError_t NpuDriver::MemGetAddrSegOfUB(
    uint32_t devId, uint64_t hostAddr, uint64_t cpySize, struct addr_range* outRange, uint32_t* outRangeCnt)
{
    UNUSED(devId);
    UNUSED(hostAddr);
    UNUSED(cpySize);
    UNUSED(outRange);
    UNUSED(outRangeCnt);
    return RT_ERROR_FEATURE_NOT_SUPPORT;
}

} // namespace runtime
} // namespace cce
