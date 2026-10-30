/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 * This program is free software, you can redistribute it and/or modify it under the terms and conditions of
 * CANN Open Software License Agreement Version 2.0 (the "License").
 * Please refer to the License for details. You may not use this file except in compliance with the License.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 * See LICENSE in the root of the software repository for the full text of the License.
 */
#include "rt_utest_api.hpp"

namespace {
class ApiErrmsgBoundaryTest : public Test {
protected:
    void SetUp() override { MOCKER(Api::Instance).stubs().will(returnValue(static_cast<Api*>(&api_))); }

    void TearDown() override { GlobalMockObject::verify(); }

    ApiDecorator api_{nullptr};
};
} // namespace

TEST_F(ApiErrmsgBoundaryTest, PhysicalDeviceInfoUnsupportedDoesNotInvokeFallback)
{
    MOCKER(ErrorMessageUtils::FuncErrorReason).expects(never());
    MOCKER(GetRtExtErrCodeAndSetGlobalErr).expects(never());
    int64_t value = -1;
    MOCKER_CPP_VIRTUAL(static_cast<Api*>(&api_), &Api::GetPhyDeviceInfo)
        .expects(once())
        .with(eq(0U), eq(RT_MODULE_TYPE_SYSTEM), eq(RT_PHY_INFO_TYPE_MASTER_ID), eq(&value))
        .will(returnValue(RT_ERROR_DRV_NOT_SUPPORT));

    EXPECT_EQ(
        rtGetPhyDeviceInfo(0U, RT_MODULE_TYPE_SYSTEM, RT_PHY_INFO_TYPE_MASTER_ID, &value),
        ACL_ERROR_RT_FEATURE_NOT_SUPPORT);
    EXPECT_EQ(value, -1);
}

TEST_F(ApiErrmsgBoundaryTest, PhysicalDeviceInfoOtherErrorStillInvokesFallback)
{
    MOCKER(ErrorMessageUtils::FuncErrorReason).expects(once()).with(eq(RT_ERROR_DRV_ERR), mockcpp::any());
    MOCKER(GetRtExtErrCodeAndSetGlobalErr)
        .expects(once())
        .with(eq(RT_ERROR_DRV_ERR))
        .will(returnValue(ACL_ERROR_RT_DRV_INTERNAL_ERROR));
    int64_t value = -1;
    MOCKER_CPP_VIRTUAL(static_cast<Api*>(&api_), &Api::GetPhyDeviceInfo)
        .expects(once())
        .with(eq(0U), eq(RT_MODULE_TYPE_SYSTEM), eq(RT_PHY_INFO_TYPE_MASTER_ID), eq(&value))
        .will(returnValue(RT_ERROR_DRV_ERR));

    EXPECT_EQ(
        rtGetPhyDeviceInfo(0U, RT_MODULE_TYPE_SYSTEM, RT_PHY_INFO_TYPE_MASTER_ID, &value),
        ACL_ERROR_RT_DRV_INTERNAL_ERROR);
    EXPECT_EQ(value, -1);
}

TEST_F(ApiErrmsgBoundaryTest, DeviceStatusUnsupportedDoesNotInvokeFallback)
{
    MOCKER(ErrorMessageUtils::FuncErrorReason).expects(never());
    MOCKER(GetRtExtErrCodeAndSetGlobalErr).expects(never());
    rtDevStatus_t status = {};
    const rtDevStatus_t originalStatus = status;
    MOCKER_CPP_VIRTUAL(static_cast<Api*>(&api_), &Api::GetDeviceStatus)
        .expects(once())
        .with(eq(0), eq(&status))
        .will(returnValue(RT_ERROR_DRV_NOT_SUPPORT));

    EXPECT_EQ(rtGetDeviceStatus(0, &status), ACL_ERROR_RT_FEATURE_NOT_SUPPORT);
    EXPECT_EQ(status, originalStatus);
}

TEST_F(ApiErrmsgBoundaryTest, DeviceStatusOtherErrorStillInvokesFallback)
{
    MOCKER(ErrorMessageUtils::FuncErrorReason).expects(once()).with(eq(RT_ERROR_DRV_ERR), mockcpp::any());
    MOCKER(GetRtExtErrCodeAndSetGlobalErr)
        .expects(once())
        .with(eq(RT_ERROR_DRV_ERR))
        .will(returnValue(ACL_ERROR_RT_DRV_INTERNAL_ERROR));
    rtDevStatus_t status = {};
    const rtDevStatus_t originalStatus = status;
    MOCKER_CPP_VIRTUAL(static_cast<Api*>(&api_), &Api::GetDeviceStatus)
        .expects(once())
        .with(eq(0), eq(&status))
        .will(returnValue(RT_ERROR_DRV_ERR));

    EXPECT_EQ(rtGetDeviceStatus(0, &status), ACL_ERROR_RT_DRV_INTERNAL_ERROR);
    EXPECT_EQ(status, originalStatus);
}

TEST_F(ApiErrmsgBoundaryTest, HdcServerUnsupportedDoesNotInvokeFallback)
{
    MOCKER(ErrorMessageUtils::FuncErrorReason).expects(never());
    MOCKER(GetRtExtErrCodeAndSetGlobalErr).expects(never());
    rtHdcServer_t server = nullptr;
    MOCKER_CPP_VIRTUAL(static_cast<Api*>(&api_), &Api::HdcServerCreate)
        .expects(once())
        .with(eq(0), eq(RT_HDC_SERVICE_TYPE_DMP), eq(&server))
        .will(returnValue(RT_ERROR_DRV_NOT_SUPPORT));

    EXPECT_EQ(rtHdcServerCreate(0, RT_HDC_SERVICE_TYPE_DMP, &server), ACL_ERROR_RT_FEATURE_NOT_SUPPORT);
    EXPECT_EQ(server, nullptr);
}

TEST_F(ApiErrmsgBoundaryTest, HdcServerOtherErrorStillInvokesFallback)
{
    MOCKER(ErrorMessageUtils::FuncErrorReason).expects(once()).with(eq(RT_ERROR_DRV_ERR), mockcpp::any());
    MOCKER(GetRtExtErrCodeAndSetGlobalErr)
        .expects(once())
        .with(eq(RT_ERROR_DRV_ERR))
        .will(returnValue(ACL_ERROR_RT_DRV_INTERNAL_ERROR));
    rtHdcServer_t server = nullptr;
    MOCKER_CPP_VIRTUAL(static_cast<Api*>(&api_), &Api::HdcServerCreate)
        .expects(once())
        .with(eq(0), eq(RT_HDC_SERVICE_TYPE_DMP), eq(&server))
        .will(returnValue(RT_ERROR_DRV_ERR));

    EXPECT_EQ(rtHdcServerCreate(0, RT_HDC_SERVICE_TYPE_DMP, &server), ACL_ERROR_RT_DRV_INTERNAL_ERROR);
    EXPECT_EQ(server, nullptr);
}

TEST_F(ApiErrmsgBoundaryTest, UtilizationUnsupportedDoesNotInvokeFallback)
{
    MOCKER(ErrorMessageUtils::FuncErrorReason).expects(never());
    MOCKER(GetRtExtErrCodeAndSetGlobalErr).expects(never());
    uint8_t utilization = 0xFFU;
    MOCKER_CPP_VIRTUAL(static_cast<Api*>(&api_), &Api::GetAllUtilizations)
        .expects(once())
        .with(eq(0), eq(RT_UTIL_TYPE_AICORE), eq(&utilization))
        .will(returnValue(RT_ERROR_DRV_NOT_SUPPORT));

    EXPECT_EQ(rtGetAllUtilizations(0, RT_UTIL_TYPE_AICORE, &utilization), ACL_ERROR_RT_FEATURE_NOT_SUPPORT);
    EXPECT_EQ(utilization, 0xFFU);
}

TEST_F(ApiErrmsgBoundaryTest, UtilizationOtherErrorStillInvokesFallback)
{
    MOCKER(ErrorMessageUtils::FuncErrorReason).expects(once()).with(eq(RT_ERROR_DRV_ERR), mockcpp::any());
    MOCKER(GetRtExtErrCodeAndSetGlobalErr)
        .expects(once())
        .with(eq(RT_ERROR_DRV_ERR))
        .will(returnValue(ACL_ERROR_RT_DRV_INTERNAL_ERROR));
    uint8_t utilization = 0xFFU;
    MOCKER_CPP_VIRTUAL(static_cast<Api*>(&api_), &Api::GetAllUtilizations)
        .expects(once())
        .with(eq(0), eq(RT_UTIL_TYPE_AICORE), eq(&utilization))
        .will(returnValue(RT_ERROR_DRV_ERR));

    EXPECT_EQ(rtGetAllUtilizations(0, RT_UTIL_TYPE_AICORE, &utilization), ACL_ERROR_RT_DRV_INTERNAL_ERROR);
    EXPECT_EQ(utilization, 0xFFU);
}

TEST_F(ApiErrmsgBoundaryTest, ServerIdUnsupportedDoesNotInvokeFallback)
{
    MOCKER(ErrorMessageUtils::FuncErrorReason).expects(never());
    MOCKER(GetRtExtErrCodeAndSetGlobalErr).expects(never());
    uint32_t serverId = UINT32_MAX;
    MOCKER_CPP_VIRTUAL(static_cast<Api*>(&api_), &Api::GetServerIDBySDID)
        .expects(once())
        .with(eq(0U), eq(&serverId))
        .will(returnValue(RT_ERROR_FEATURE_NOT_SUPPORT));

    EXPECT_EQ(rtGetServerIDBySDID(0U, &serverId), ACL_ERROR_RT_FEATURE_NOT_SUPPORT);
    EXPECT_EQ(serverId, UINT32_MAX);
}

TEST_F(ApiErrmsgBoundaryTest, ServerIdOtherErrorStillInvokesFallback)
{
    MOCKER(ErrorMessageUtils::FuncErrorReason).expects(once()).with(eq(RT_ERROR_DRV_ERR), mockcpp::any());
    MOCKER(GetRtExtErrCodeAndSetGlobalErr)
        .expects(once())
        .with(eq(RT_ERROR_DRV_ERR))
        .will(returnValue(ACL_ERROR_RT_DRV_INTERNAL_ERROR));
    uint32_t serverId = UINT32_MAX;
    MOCKER_CPP_VIRTUAL(static_cast<Api*>(&api_), &Api::GetServerIDBySDID)
        .expects(once())
        .with(eq(0U), eq(&serverId))
        .will(returnValue(RT_ERROR_DRV_ERR));

    EXPECT_EQ(rtGetServerIDBySDID(0U, &serverId), ACL_ERROR_RT_DRV_INTERNAL_ERROR);
    EXPECT_EQ(serverId, UINT32_MAX);
}
