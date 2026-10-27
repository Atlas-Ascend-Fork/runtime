/**
 * Copyright (c) 2025 Huawei Technologies Co., Ltd.
 * This program is free software, you can redistribute it and/or modify it under the terms and conditions of
 * CANN Open Software License Agreement Version 2.0 (the "License").
 * Please refer to the License for details. You may not use this file except in compliance with the License.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 * See LICENSE in the root of the software repository for the full text of the License.
 */
#include <gtest/gtest.h>
#include "mockcpp/mockcpp.hpp"
#define protected public
#define private public

#include "log_hdc.h"
#include "log_session_manage.h"
#include "log_common.h"
#include "hdc_api.h"
#undef private
#undef protected

using namespace Adx;
static const std::string INSERT_MSG = "###[HDC_MSG]_DEVICE_FRAMEWORK_START_###";
static const std::string DELETE_MSG = "###[HDC_MSG]_DEVICE_FRAMEWORK_END_###";
static SessionNode* g_node = NULL;

class ADX_LOG_HDC_TEST : public testing::Test {
protected:
    virtual void SetUp() {}
    virtual void TearDown()
    {
        free(g_node);
        g_node = NULL;
        GlobalMockObject::verify();
    }
};

TEST_F(ADX_LOG_HDC_TEST, Init)
{
    Adx::LogHdc LogHdc;
    EXPECT_EQ(IDE_DAEMON_OK, LogHdc.Init());
}

TEST_F(ADX_LOG_HDC_TEST, UnInit)
{
    Adx::LogHdc LogHdc;
    EXPECT_EQ(IDE_DAEMON_OK, LogHdc.UnInit());
}

// the notify payload carries a distinctive timeout, so the timeout assertions below discriminate
// a call site that forwards msg->timeout from one that hardcodes it or reads the wrong field;
// the pid/devId assertions only pin the values produced by the returnValue session-info mocks
// (they never write out-params, so a pid/devId swap stays indistinguishable until mockcpp
// governance restores reliable out-param stubs). mockcpp drops invoke-stub return values on
// some toolchains (aarch64 gcc13 returns 0 for the first chained response, x86 gcc15 dropped
// the online-UT run), so the stubs return values that stay inert when dropped: SUCCESS equals
// the dropped default 0, and ARGV_NULL only routes into the warn branch whose flag outcome is
// identical. returnValue chains are used where the return value itself is load-bearing.
static constexpr int32_t STUB_NOTIFY_TIMEOUT = 0x7B;

static LogRt DeleteSessionNodeByPidDevIdStub(uint32_t pid, uint32_t devId, int32_t timeout)
{
    EXPECT_EQ(0U, pid);
    EXPECT_EQ(0U, devId);
    EXPECT_EQ(STUB_NOTIFY_TIMEOUT, timeout);
    return (LogRt)SUCCESS;
}

static LogRt DeleteSessionNodeByPidDevIdNullStub(uint32_t pid, uint32_t devId, int32_t timeout)
{
    EXPECT_EQ(0U, pid);
    EXPECT_EQ(0U, devId);
    EXPECT_EQ(STUB_NOTIFY_TIMEOUT, timeout);
    return (LogRt)ARGV_NULL;
}

TEST_F(ADX_LOG_HDC_TEST, Process)
{
    LogHdc LogHdc;
    CommHandle handle = ADX_COMMOPT_INVALID_HANDLE(OptType::COMM_HDC);
    handle.type = OptType::COMM_HDC;
    handle.session = 0x123456789;

    MsgProto* proto = (MsgProto*)calloc(1, sizeof(MsgProto) + 100);
    proto->msgType = MsgType::MSG_DATA;
    proto->status = MsgStatus::MSG_STATUS_HAND_SHAKE;
    proto->sliceLen = 100;
    LogNotifyMsg* msg = (LogNotifyMsg*)proto->data;
    strcpy(msg->data, INSERT_MSG.c_str());
    SharedPtr<MsgProto> protoPtrs(proto, free);

    MOCKER(IdeGetDevIdBySession).stubs().will(returnValue(IDE_DAEMON_ERROR)).then(returnValue(IDE_DAEMON_OK));

    MOCKER(IdeGetPidBySession).stubs().will(returnValue(IDE_DAEMON_ERROR)).then(returnValue(IDE_DAEMON_OK));

    MOCKER(InsertSessionNode).stubs().will(returnValue(IDE_DAEMON_OK));

    MOCKER(DeleteSessionNodeByPidDevId)
        .stubs()
        .will(invoke(DeleteSessionNodeByPidDevIdStub))
        .then(invoke(DeleteSessionNodeByPidDevIdNullStub));

    MOCKER(IsSessionNodeListNull).stubs().will(returnValue(true));

    EXPECT_EQ(IDE_DAEMON_OK, LogHdc.Init());
    EXPECT_EQ(IDE_DAEMON_ERROR, LogHdc.Process(handle, protoPtrs));
    EXPECT_EQ(IDE_DAEMON_ERROR, LogHdc.Process(handle, protoPtrs));
    EXPECT_EQ(IDE_DAEMON_OK, LogHdc.Process(handle, protoPtrs));
    strcpy(msg->data, DELETE_MSG.c_str());
    msg->timeout = STUB_NOTIFY_TIMEOUT;
    EXPECT_EQ(IDE_DAEMON_OK, LogHdc.Process(handle, protoPtrs));
    EXPECT_EQ(IDE_DAEMON_OK, LogHdc.Process(handle, protoPtrs));
    strcpy(msg->data, "TEST FAILED");
    EXPECT_EQ(IDE_DAEMON_ERROR, LogHdc.Process(handle, protoPtrs));

    EXPECT_EQ(IDE_DAEMON_OK, LogHdc.UnInit());
}
