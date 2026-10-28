/**
 * Copyright (c) 2025 Huawei Technologies Co., Ltd.
 * This program is free software, you can redistribute it and/or modify it under the terms and conditions of
 * CANN Open Software License Agreement Version 2.0 (the "License").
 * Please refer to the License for details. You may not use this file except in compliance with the License.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 * See LICENSE in the root of the software repository for the full text of the License.
 */
#include "mockcpp/mockcpp.hpp"
#include "gtest/gtest.h"
#include <iostream>
#include <thread>
#include "errno/error_code.h"
#include "data_handle.h"
#include "message/codec.h"
#include "msprof_task.h"

using namespace analysis::dvvp::common::error;
using namespace analysis::dvvp::common::config;

class DATA_HANDLE_UTEST : public testing::Test {
protected:
    virtual void SetUp() { Analysis::Dvvp::Msprof::HdcTransportDataHandle::UnregisterAllTask(); }
    virtual void TearDown() {}
};

TEST_F(DATA_HANDLE_UTEST, ReceiveStreamData)
{
    GlobalMockObject::verify();

    std::shared_ptr<analysis::dvvp::message::JobContext> jobCtx(new analysis::dvvp::message::JobContext);
    jobCtx->dev_id = "0";
    jobCtx->job_id = "0x123456789";

    std::shared_ptr<analysis::dvvp::proto::DataChannelFinish> message(new analysis::dvvp::proto::DataChannelFinish());
    std::string encoded = analysis::dvvp::message::EncodeMessage(message);
    EXPECT_EQ(
        PROFILING_FAILED,
        Analysis::Dvvp::Msprof::HdcTransportDataHandle::ReceiveStreamData((void*)NULL, encoded.size()));

    message->mutable_hdr()->set_job_ctx(jobCtx->ToString());
    encoded = analysis::dvvp::message::EncodeMessage(message);
    // null
    EXPECT_EQ(
        PROFILING_FAILED,
        Analysis::Dvvp::Msprof::HdcTransportDataHandle::ReceiveStreamData((void*)encoded.c_str(), encoded.size()));

    // message error
    std::shared_ptr<analysis::dvvp::proto::Response> fake_message(new analysis::dvvp::proto::Response());
    std::string fake_encoded = analysis::dvvp::message::EncodeMessage(fake_message);
    EXPECT_EQ(
        PROFILING_FAILED, Analysis::Dvvp::Msprof::HdcTransportDataHandle::ReceiveStreamData(
                              (void*)fake_encoded.c_str(), fake_encoded.size()));
    // success
    EXPECT_EQ(
        PROFILING_FAILED,
        Analysis::Dvvp::Msprof::HdcTransportDataHandle::ReceiveStreamData((void*)encoded.c_str(), encoded.size()));

    // filechunk meessage
    std::shared_ptr<analysis::dvvp::proto::FileChunkReq> fileChunkMessage(new analysis::dvvp::proto::FileChunkReq());
    std::string fileChunkEncoded = analysis::dvvp::message::EncodeMessage(fileChunkMessage);

    EXPECT_EQ(
        PROFILING_FAILED, Analysis::Dvvp::Msprof::HdcTransportDataHandle::ReceiveStreamData(
                              (void*)fileChunkEncoded.c_str(), fileChunkEncoded.size()));

    fileChunkMessage->mutable_hdr()->set_job_ctx(jobCtx->ToString());
    fileChunkMessage->set_datamodule(FileChunkDataModule::PROFILING_IS_FROM_MSPROF);
    fileChunkEncoded = analysis::dvvp::message::EncodeMessage(fileChunkMessage);
    EXPECT_EQ(
        PROFILING_FAILED, Analysis::Dvvp::Msprof::HdcTransportDataHandle::ReceiveStreamData(
                              (void*)fileChunkEncoded.c_str(), fileChunkEncoded.size()));

    // FinishJobRsp messsage
    std::shared_ptr<analysis::dvvp::proto::FinishJobRsp> finishJobRsp(new analysis::dvvp::proto::FinishJobRsp());
    std::string finishJob = analysis::dvvp::message::EncodeMessage(finishJobRsp);
    EXPECT_EQ(
        PROFILING_FAILED,
        Analysis::Dvvp::Msprof::HdcTransportDataHandle::ReceiveStreamData((void*)finishJob.c_str(), finishJob.size()));
}

TEST_F(DATA_HANDLE_UTEST, TaskRegistryLifecycle)
{
    GlobalMockObject::verify();

    std::shared_ptr<analysis::dvvp::message::JobContext> jobCtx(new analysis::dvvp::message::JobContext);
    jobCtx->job_id = "task_registry_ut";

    std::shared_ptr<analysis::dvvp::message::ProfileParams> params(new analysis::dvvp::message::ProfileParams);
    SHARED_PTR_ALIA<Analysis::Dvvp::Msprof::ProfSocTask> task(new Analysis::Dvvp::Msprof::ProfSocTask(0, params));

    std::shared_ptr<analysis::dvvp::proto::DataChannelFinish> message(new analysis::dvvp::proto::DataChannelFinish);
    message->mutable_hdr()->set_job_ctx(jobCtx->ToString());
    std::string encoded = analysis::dvvp::message::EncodeMessage(message);

    Analysis::Dvvp::Msprof::HdcTransportDataHandle::RegisterTask("", task);
    Analysis::Dvvp::Msprof::HdcTransportDataHandle::RegisterTask(jobCtx->job_id, nullptr);
    EXPECT_EQ(
        PROFILING_FAILED,
        Analysis::Dvvp::Msprof::HdcTransportDataHandle::ReceiveStreamData((void*)encoded.c_str(), encoded.size()));

    Analysis::Dvvp::Msprof::HdcTransportDataHandle::RegisterTask(jobCtx->job_id, task);
    EXPECT_EQ(
        PROFILING_SUCCESS,
        Analysis::Dvvp::Msprof::HdcTransportDataHandle::ReceiveStreamData((void*)encoded.c_str(), encoded.size()));

    Analysis::Dvvp::Msprof::HdcTransportDataHandle::UnregisterAllTask();
    EXPECT_EQ(
        PROFILING_FAILED,
        Analysis::Dvvp::Msprof::HdcTransportDataHandle::ReceiveStreamData((void*)encoded.c_str(), encoded.size()));
}

TEST_F(DATA_HANDLE_UTEST, TaskRegistryConcurrentAccess)
{
    GlobalMockObject::verify();

    std::shared_ptr<analysis::dvvp::message::JobContext> jobCtx(new analysis::dvvp::message::JobContext);
    jobCtx->job_id = "task_registry_concurrent_ut";

    std::shared_ptr<analysis::dvvp::message::ProfileParams> params(new analysis::dvvp::message::ProfileParams);
    SHARED_PTR_ALIA<Analysis::Dvvp::Msprof::ProfSocTask> task(new Analysis::Dvvp::Msprof::ProfSocTask(0, params));

    std::shared_ptr<analysis::dvvp::proto::DataChannelFinish> message(new analysis::dvvp::proto::DataChannelFinish);
    message->mutable_hdr()->set_job_ctx(jobCtx->ToString());
    std::string encoded = analysis::dvvp::message::EncodeMessage(message);

    std::thread registerThread([&task, &jobCtx]() {
        for (int32_t i = 0; i < 100; ++i) {
            Analysis::Dvvp::Msprof::HdcTransportDataHandle::RegisterTask(jobCtx->job_id, task);
        }
    });

    std::thread callbackThread([&encoded]() {
        for (int32_t i = 0; i < 100; ++i) {
            (void)Analysis::Dvvp::Msprof::HdcTransportDataHandle::ReceiveStreamData(
                (void*)encoded.c_str(), encoded.size());
        }
    });

    std::thread unregisterThread([]() {
        for (int32_t i = 0; i < 100; ++i) {
            Analysis::Dvvp::Msprof::HdcTransportDataHandle::UnregisterAllTask();
        }
    });

    registerThread.join();
    callbackThread.join();
    unregisterThread.join();

    Analysis::Dvvp::Msprof::HdcTransportDataHandle::UnregisterAllTask();
}
