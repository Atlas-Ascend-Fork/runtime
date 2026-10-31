/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 * This program is free software, you can redistribute it and/or modify it under the terms and conditions of
 * CANN Open Software License Agreement Version 2.0 (the "License").
 * Please refer to the License for details. You may not use this file except in compliance with the License.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 * See LICENSE in the root of the software repository for the full text of the License.
 */
#ifndef RUNTIME_FEATURE_XPU_API_IMPL_XPU_COMMON_HPP_
#define RUNTIME_FEATURE_XPU_API_IMPL_XPU_COMMON_HPP_

#include "base.hpp"

namespace cce {
namespace runtime {

// SetXpuDevice公共参数校验，仅供Xpu实现内部使用
rtError_t CheckSetXpuDeviceParam(const rtXpuDevType devType, const uint32_t devId);

// ResetXpuDevice公共参数校验，仅供Xpu实现内部使用
rtError_t CheckResetXpuDeviceParam(const rtXpuDevType devType, const uint32_t devId);

} // namespace runtime
} // namespace cce

#endif // RUNTIME_FEATURE_XPU_API_IMPL_XPU_COMMON_HPP_
