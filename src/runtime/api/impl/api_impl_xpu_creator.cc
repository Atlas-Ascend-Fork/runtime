/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 * This program is free software, you can redistribute it and/or modify it under the terms and conditions of
 * CANN Open Software License Agreement Version 2.0 (the "License").
 * Please refer to the License for details. You may not use this file except in compliance with the License.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 * See LICENSE in the root of the software repository for the full text of the License.
 */
#include "api_impl_xpu.hpp"
#include <new>
#include "api_impl_creator.hpp"

namespace cce {
namespace runtime {

bool IsImplXpuSupported() { return true; }

ApiXpu* CreateImplXpuAndGet()
{
    ApiXpu* const apiImplXpu = new (std::nothrow) ApiImplXpu();
    if (apiImplXpu == nullptr) {
        RT_LOG_OUTER_MSG_IMPL(ErrorCode::EE1013, sizeof(ApiImplXpu), "new");
        RT_LOG(RT_LOG_ERROR, "Create ApiImplXpu failed.");
        return nullptr;
    }

    RT_LOG(RT_LOG_INFO, "ApiImplXpu:Runtime_alloc_size %zu", sizeof(ApiImplXpu));
    return apiImplXpu;
}

void DestroyImplXpu(ApiXpu*& apiImplXpu)
{
    delete apiImplXpu;
    apiImplXpu = nullptr;
}
} // namespace runtime
} // namespace cce