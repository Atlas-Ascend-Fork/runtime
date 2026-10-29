# -----------------------------------------------------------------------------------------------------------
# Copyright (c) 2026 Huawei Technologies Co., Ltd.
# This program is free software, you can redistribute it and/or modify it under the terms and conditions of
# CANN Open Software License Agreement Version 2.0 (the "License").
# Please refer to the License for details. You may not use this file except in compliance with the License.
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
# INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
# See LICENSE in the root of the software repository for the full text of the License.
# -----------------------------------------------------------------------------------------------------------

add_library(rt_aicpu_kernels SHARED
    rt_kernel_dsa_update.cpp
    rt_aicpu_kernel.cpp
)

target_include_directories(rt_aicpu_kernels PRIVATE
    ${RUNTIME_DIR}/src/aicpu_sched/aicpu_kernel/utils
)

target_link_libraries(rt_aicpu_kernels PRIVATE
    $<BUILD_INTERFACE:intf_pub>
    $<BUILD_INTERFACE:slog_headers>
    c_sec
)

target_compile_options(rt_aicpu_kernels PRIVATE
    -fvisibility=hidden
    -fvisibility-inlines-hidden
)
