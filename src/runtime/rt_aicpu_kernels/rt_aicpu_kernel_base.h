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
#ifndef RT_AICPU_KERNEL_BASE_H
#define RT_AICPU_KERNEL_BASE_H

#include <cstdio>
#include <cstdint>
#include <vector>
#include <sys/types.h>
#include "aicpu_kernel_log.h"

namespace RT_AICPU_KERNEL {
enum ErrorCode : uint32_t {
    RT_AICPU_KERNEL_SUCCESS = 0U,
    RT_AICPU_KERNEL_E_PARA,
    RT_AICPU_KERNEL_E_TIMEOUT,
    RT_AICPU_KERNEL_E_NOT_SUPPORT,
    RT_AICPU_KERNEL_E_AGAIN,
    RT_AICPU_KERNEL_E_INTERNAL,
    RT_AICPU_KERNEL_E_MEMORY,
    RT_AICPU_KERNEL_E_DRIVE
};

enum RtAicpuKernelType : uint32_t { RT_AICPU_KERNEL_DSA_UPDATE = 0U };

struct RtAicpuKernelArgs {
    uint32_t kernel_type;
    uint32_t param_length;
};

#define COND_RETURN_ERROR_MSG(COND, ERRCODE, format, ...) \
    if (COND) {                                           \
        KERNEL_LOG_ERROR(format, ##__VA_ARGS__);          \
        return ERRCODE;                                   \
    }

} // namespace RT_AICPU_KERNEL
#endif // RT_AICPU_KERNEL_BASE_H
