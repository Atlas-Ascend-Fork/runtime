/**
 * Copyright (c) Huawei Technologies Co., Ltd. 2025. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "rt_aicpu_kernel.h"
#include "rt_aicpu_kernel_base.h"
#include "rt_kernel_dsa_update.h"

using namespace RT_AICPU_KERNEL;

extern "C" {
__attribute__((visibility(("default")))) uint32_t RuntimeAicpuKernel(void* args)
{
    if (args == nullptr) {
        KERNEL_LOG_ERROR("Runtime aicpu kernel args is null");
        return static_cast<uint32_t>(RT_AICPU_KERNEL_E_PARA);
    }
    RtAicpuKernelArgs* tl = RtPtrToPtr<RtAicpuKernelArgs*>(args);
    COND_RETURN_ERROR_MSG(tl == nullptr, RT_AICPU_KERNEL_E_PARA, "RtAicpuKernelArgs reinterpret failed.");
    uint32_t ret = RT_AICPU_KERNEL_SUCCESS;
    switch (tl->kernel_type) {
        case RT_AICPU_KERNEL_DSA_UPDATE:
            ret = DsaUpdate(args);
            break;
        default:
            ret = RT_AICPU_KERNEL_E_NOT_SUPPORT;
            KERNEL_LOG_ERROR("kernelType [%d] is not supported.", tl->kernel_type);
            break;
    }
    return ret;
}
}
