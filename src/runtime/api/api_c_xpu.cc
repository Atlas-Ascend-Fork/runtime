/**
 * Copyright (c) 2025 Huawei Technologies Co., Ltd.
 * This program is free software, you can redistribute it and/or modify it under the terms and conditions of
 * CANN Open Software License Agreement Version 2.0 (the "License").
 * Please refer to the License for details. You may not use this file except in compliance with the License.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 * See LICENSE in the root of the software repository for the full text of the License.
 */
#include "api_xpu.hpp"
#include "api_c.h"
#include "rt_external_device.h"
using namespace cce::runtime;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
VISIBILITY_DEFAULT
rtError_t rtGetXpuDevCount(const rtXpuDevType devType, uint32_t* devCount)
{
    ApiXpu* const apiInstance = ApiXpu::Instance();
    NULL_RETURN_ERROR_WITH_EXT_ERRCODE(apiInstance);

    const rtError_t error = apiInstance->GetXpuDevCount(devType, devCount);
    COND_RETURN_WITH_NOLOG(error == RT_ERROR_FEATURE_NOT_SUPPORT, ACL_ERROR_RT_FEATURE_NOT_SUPPORT);
    ERROR_RETURN_WITH_EXT_ERRCODE(error);
    return ACL_RT_SUCCESS;
}

VISIBILITY_DEFAULT
rtError_t rtSetXpuDevice(rtXpuDevType devType, const uint32_t devId)
{
    ApiXpu* const apiInstance = ApiXpu::Instance();
    NULL_RETURN_ERROR_WITH_EXT_ERRCODE(apiInstance);
    const rtError_t error = apiInstance->SetXpuDevice(devType, devId);
    COND_RETURN_WITH_NOLOG(error == RT_ERROR_FEATURE_NOT_SUPPORT, ACL_ERROR_RT_FEATURE_NOT_SUPPORT);
    ERROR_RETURN_WITH_EXT_ERRCODE(error);
    return ACL_RT_SUCCESS;
}

VISIBILITY_DEFAULT
rtError_t rtResetXpuDevice(rtXpuDevType devType, const uint32_t devId)
{
    ApiXpu* const apiInstance = ApiXpu::Instance();
    NULL_RETURN_ERROR_WITH_EXT_ERRCODE(apiInstance);
    const rtError_t error = apiInstance->ResetXpuDevice(devType, devId);
    COND_RETURN_WITH_NOLOG(error == RT_ERROR_FEATURE_NOT_SUPPORT, ACL_ERROR_RT_FEATURE_NOT_SUPPORT);
    ERROR_RETURN_WITH_EXT_ERRCODE(error);
    return ACL_RT_SUCCESS;
}

VISIBILITY_DEFAULT
rtError_t rtXpuSetTaskFailCallback(rtXpuDevType devType, const char_t* moduleName, rtTaskFailCallback callback)
{
    ApiXpu* const apiInstance = ApiXpu::Instance();
    NULL_RETURN_ERROR_WITH_EXT_ERRCODE(apiInstance);
    const rtError_t error = apiInstance->XpuSetTaskFailCallback(devType, moduleName, RtPtrToPtr<void*>(callback));
    COND_RETURN_WITH_NOLOG(error == RT_ERROR_FEATURE_NOT_SUPPORT, ACL_ERROR_RT_FEATURE_NOT_SUPPORT);
    ERROR_RETURN_WITH_EXT_ERRCODE(error);
    return ACL_RT_SUCCESS;
}
#ifdef __cplusplus
}
#endif // __cplusplus
