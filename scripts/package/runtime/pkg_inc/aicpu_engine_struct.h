/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 * This program is free software, you can redistribute it and/or modify it under the terms and conditions of
 * CANN Open Software License Agreement Version 2.0 (the "License").
 * Please refer to the License for details. You may not use this file except in compliance with the License.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 * See LICENSE in the root of the software repository for the full text of the License.
 */

#ifndef AICPU_ENGINE_STRUCT_COMPAT_H
#define AICPU_ENGINE_STRUCT_COMPAT_H

#ifndef AICPU_ENGINE_STRUCT_COMPAT_WARN_SHOWN
#define AICPU_ENGINE_STRUCT_COMPAT_WARN_SHOWN
#pragma message( \
        "aicpu_engine_struct.h is scheduled to be removed on 2027-07-25 (one-year compatibility period since 2026-07-25), \
and will be replaced by aicpu/aicpu_engine_struct.h. Please migrate to the new include path in time.")
#endif // AICPU_ENGINE_STRUCT_COMPAT_WARN_SHOWN

/*
 * Compatibility header for legacy include path.
 * Deprecated since 2026-07-25, use "aicpu/aicpu_engine_struct.h" instead.
 * This header will be removed on 2027-07-25 (one-year compatibility period), and cannot be used anymore after that
 * date.
 */
#include "aicpu/aicpu_engine_struct.h"

#endif // AICPU_ENGINE_STRUCT_COMPAT_H
