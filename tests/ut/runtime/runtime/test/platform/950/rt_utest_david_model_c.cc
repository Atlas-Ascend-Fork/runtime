/**
 * Copyright (c) 2025 Huawei Technologies Co., Ltd.
 * This program is free software, you can redistribute it and/or modify it under the terms and conditions of
 * CANN Open Software License Agreement Version 2.0 (the "License").
 * Please refer to the License for details. You may not use this file except in compliance with the License.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 * See LICENSE in the root of the software repository for the full text of the License.
 */
#include <iostream>
#include "driver/ascend_hal.h"
#include "runtime/rt.h"
#include "gtest/gtest.h"
#include "mockcpp/mockcpp.hpp"
#define private public
#define protected public
#include "api.hpp"
#include "api_impl_david.hpp"
#include "engine.hpp"
#include "stream.hpp"
#include "runtime.hpp"
#include "raw_device.hpp"
#include "task_info.hpp"
#include "context.hpp"
#include "stream_david.hpp"
#include "thread_local_container.hpp"
#undef private
#undef protected
#include "model_c.hpp"
#include "program.hpp"
#include "task.hpp"
#include "securec.h"
#include "npu_driver.hpp"
#include "../../rt_utest_config_define.hpp"
#include "stars_david.hpp"
#include "rt_unwrap.h"
#include "runtime_dump_task.h"
#include "model_maintaince_task.h"
#include "model_to_aicpu_task.h"
#include "stub/hal_stub.h"
#include "rt_utest_david_fixture_helper.h"

using namespace testing;
using namespace cce::runtime;
static rtChipType_t g_chipType;

static TaskInfo g_mockTaskInfo = {};
static rtError_t AllocTaskInfoSuccessMock(TaskInfo** tsk, Stream* stm, uint32_t& pos)
{
    *tsk = &g_mockTaskInfo;
    pos = 0U;
    return RT_ERROR_NONE;
}

class TaskTestDavidModelC : public testing::Test {
protected:
    static void SetUpTestCase()
    {
        MOCKER(halGetDeviceInfo).stubs().will(invoke(stubDavidGetDeviceInfo));
        char* socVer = "Ascend950PR_9599";
        MOCKER(halGetSocVersion)
            .stubs()
            .with(mockcpp::any(), outBoundP(socVer, strlen("Ascend950PR_9599")), mockcpp::any())
            .will(returnValue(DRV_ERROR_NONE));
        Runtime* rtInstance = (Runtime*)Runtime::Instance();
        rtInstance->SetDisableThread(true);
        g_chipType = rtInstance->GetChipType();
        rtInstance->SetChipType(CHIP_DAVID);
        GlobalContainer::SetRtChipType(CHIP_DAVID);
        rtInstance->SetConnectUbFlag(false);
    }

    static void TearDownTestCase()
    {
        Runtime* rtInstance = (Runtime*)Runtime::Instance();
        rtInstance->SetChipType(g_chipType);
        GlobalContainer::SetRtChipType(g_chipType);
        rtInstance->SetDisableThread(false);
        rtInstance->SetConnectUbFlag(false);
    }

    virtual void SetUp()
    {
        Driver* driver = MockDavidDriverSetup();

        bool enable = false;
        MOCKER_CPP_VIRTUAL(driver, &Driver::GetSqEnable)
            .stubs()
            .with(mockcpp::any(), mockcpp::any(), mockcpp::any(), outBound(enable))
            .will(returnValue(RT_ERROR_NONE));

        MOCKER_CPP_VIRTUAL(driver, &Driver::SetSqHead).stubs().will(returnValue(RT_ERROR_NONE));
        MOCKER_CPP_VIRTUAL(driver, &Driver::EnableSq).stubs().will(returnValue(RT_ERROR_NONE));
        SetupDavidDeviceAndEngine(device_, engine_);

        rtError_t res = rtStreamCreate(&streamHandle_, 0);
        EXPECT_EQ(res, RT_ERROR_NONE);
        stream_ = rt_ut::UnwrapOrNull<Stream>(streamHandle_);

        stream_->SetSqMemAttr(false);
        ((RawDevice*)(stream_->Device_()))->PrimaryStream_()->SetSqBaseAddr(0U);
    }

    virtual void TearDown()
    {
        while (stream_->GetPendingNum() > 0) {
            stream_->pendingNum_.Sub(1U);
        }
        while (engine_->GetPendingNum() > 0) {
            engine_->pendingNum_.Set(0U);
        }
        rtStreamDestroy(streamHandle_);
        stream_ = nullptr;
        engine_ = nullptr;
        ((Runtime*)Runtime::Instance())->DeviceRelease(device_);
        ((Runtime*)Runtime::Instance())->SetIsUserSetSocVersion(false);
        rtDeviceReset(0);
        GlobalMockObject::reset();
    }

    rtModel_t CreateModel()
    {
        rtModel_t model = nullptr;
        EXPECT_EQ(rtModelCreate(&model, 0), RT_ERROR_NONE);
        return model;
    }

    void DestroyModel(rtModel_t model) { EXPECT_EQ(rtModelDestroy(model), RT_ERROR_NONE); }

    rtStream_t CreateExtraStream()
    {
        rtStream_t stream;
        EXPECT_EQ(rtStreamCreate(&stream, 0), RT_ERROR_NONE);
        return stream;
    }

    void DestroyExtraStream(rtStream_t stream) { EXPECT_EQ(rtStreamDestroy(stream), RT_ERROR_NONE); }

    void MockIsSupportFeatureFalse()
    {
        MOCKER_CPP_VIRTUAL(device_, &Device::IsSupportFeature).stubs().will(returnValue(false));
    }

public:
    Device* device_ = nullptr;
    Stream* stream_ = nullptr;
    Engine* engine_ = nullptr;
    rtStream_t streamHandle_ = 0;
};

TEST_F(TaskTestDavidModelC, TestModelDebugRegister_CheckTaskCanSendFail)
{
    rtModel_t model = CreateModel();
    Model* mdl = rt_ut::UnwrapOrNull<Model>(model);
    ASSERT_NE(mdl, nullptr);

    MockIsSupportFeatureFalse();
    MOCKER(CheckTaskCanSend).stubs().will(returnValue(RT_ERROR_INVALID_VALUE));

    uint32_t streamId = 0U;
    uint32_t taskId = 0U;
    rtError_t ret = ModelDebugRegister(mdl, 0, nullptr, &streamId, &taskId, stream_);
    EXPECT_NE(ret, RT_ERROR_NONE);

    DestroyModel(model);
}

TEST_F(TaskTestDavidModelC, TestModelDebugRegister_AllocTaskInfoFail)
{
    rtModel_t model = CreateModel();
    Model* mdl = rt_ut::UnwrapOrNull<Model>(model);
    ASSERT_NE(mdl, nullptr);

    MockIsSupportFeatureFalse();
    MOCKER(CheckTaskCanSend).stubs().will(returnValue(RT_ERROR_NONE));
    MOCKER_CPP(static_cast<TaskInfo* (Stream::*)(TaskInfo*, tsTaskType_t, rtError_t&, uint32_t, UpdateTaskFlag)>(
                   &Stream::AllocTask))
        .stubs()
        .with(mockcpp::any(), mockcpp::any(), outBound(RT_ERROR_INVALID_VALUE), mockcpp::any(), mockcpp::any())
        .will(returnValue(static_cast<TaskInfo*>(nullptr)));

    uint32_t streamId = 0U;
    uint32_t taskId = 0U;
    rtError_t ret = ModelDebugRegister(mdl, 0, nullptr, &streamId, &taskId, stream_);
    EXPECT_NE(ret, RT_ERROR_NONE);

    DestroyModel(model);
}

TEST_F(TaskTestDavidModelC, TestModelDebugRegister_SyncTimeout)
{
    rtModel_t model = CreateModel();
    Model* mdl = rt_ut::UnwrapOrNull<Model>(model);
    ASSERT_NE(mdl, nullptr);

    MockIsSupportFeatureFalse();
    MOCKER(CheckTaskCanSend).stubs().will(returnValue(RT_ERROR_NONE));
    MOCKER_CPP(static_cast<TaskInfo* (Stream::*)(TaskInfo*, tsTaskType_t, rtError_t&, uint32_t, UpdateTaskFlag)>(
                   &Stream::AllocTask))
        .stubs()
        .will(returnValue(&g_mockTaskInfo));
    MOCKER(DebugRegisterTaskInit).stubs().will(returnValue(RT_ERROR_NONE));
    MOCKER(DavidSendTask).stubs().will(returnValue(RT_ERROR_NONE));
    MOCKER_CPP_VIRTUAL(stream_, &Stream::Synchronize).stubs().will(returnValue(RT_ERROR_STREAM_SYNC_TIMEOUT));

    uint32_t streamId = 0U;
    uint32_t taskId = 0U;
    rtError_t ret = ModelDebugRegister(mdl, 0, nullptr, &streamId, &taskId, stream_);
    EXPECT_EQ(ret, RT_ERROR_STREAM_SYNC_TIMEOUT);

    DestroyModel(model);
}

TEST_F(TaskTestDavidModelC, TestModelDebugUnRegister_CheckTaskCanSendFail)
{
    rtModel_t model = CreateModel();
    Model* mdl = rt_ut::UnwrapOrNull<Model>(model);
    ASSERT_NE(mdl, nullptr);
    mdl->SetDebugRegister(true);

    MockIsSupportFeatureFalse();
    MOCKER(CheckTaskCanSend).stubs().will(returnValue(RT_ERROR_INVALID_VALUE));

    rtError_t ret = ModelDebugUnRegister(mdl, stream_);
    EXPECT_NE(ret, RT_ERROR_NONE);

    DestroyModel(model);
}

TEST_F(TaskTestDavidModelC, TestModelDebugUnRegister_AllocTaskInfoFail)
{
    rtModel_t model = CreateModel();
    Model* mdl = rt_ut::UnwrapOrNull<Model>(model);
    ASSERT_NE(mdl, nullptr);
    mdl->SetDebugRegister(true);

    MockIsSupportFeatureFalse();
    MOCKER(CheckTaskCanSend).stubs().will(returnValue(RT_ERROR_NONE));
    MOCKER_CPP(static_cast<TaskInfo* (Stream::*)(TaskInfo*, tsTaskType_t, rtError_t&, uint32_t, UpdateTaskFlag)>(
                   &Stream::AllocTask))
        .stubs()
        .with(mockcpp::any(), mockcpp::any(), outBound(RT_ERROR_INVALID_VALUE), mockcpp::any(), mockcpp::any())
        .will(returnValue(static_cast<TaskInfo*>(nullptr)));

    rtError_t ret = ModelDebugUnRegister(mdl, stream_);
    EXPECT_NE(ret, RT_ERROR_NONE);

    DestroyModel(model);
}

TEST_F(TaskTestDavidModelC, TestModelDebugUnRegister_SyncTimeout)
{
    rtModel_t model = CreateModel();
    Model* mdl = rt_ut::UnwrapOrNull<Model>(model);
    ASSERT_NE(mdl, nullptr);
    mdl->SetDebugRegister(true);

    MockIsSupportFeatureFalse();
    MOCKER(CheckTaskCanSend).stubs().will(returnValue(RT_ERROR_NONE));
    MOCKER_CPP(static_cast<TaskInfo* (Stream::*)(TaskInfo*, tsTaskType_t, rtError_t&, uint32_t, UpdateTaskFlag)>(
                   &Stream::AllocTask))
        .stubs()
        .will(returnValue(&g_mockTaskInfo));
    MOCKER(DebugUnRegisterTaskInit).stubs().will(returnValue(RT_ERROR_NONE));
    MOCKER(DavidSendTask).stubs().will(returnValue(RT_ERROR_NONE));
    MOCKER_CPP_VIRTUAL(stream_, &Stream::Synchronize).stubs().will(returnValue(RT_ERROR_STREAM_SYNC_TIMEOUT));

    rtError_t ret = ModelDebugUnRegister(mdl, stream_);
    EXPECT_EQ(ret, RT_ERROR_STREAM_SYNC_TIMEOUT);

    DestroyModel(model);
}

TEST_F(TaskTestDavidModelC, TestAicpuMdlDestroy_CheckTaskCanSendFail)
{
    rtModel_t model = CreateModel();
    Model* mdl = rt_ut::UnwrapOrNull<Model>(model);
    ASSERT_NE(mdl, nullptr);

    MOCKER(CheckTaskCanSend).stubs().will(returnValue(RT_ERROR_INVALID_VALUE));

    rtError_t ret = AicpuMdlDestroy(mdl);
    EXPECT_NE(ret, RT_ERROR_NONE);

    DestroyModel(model);
}

TEST_F(TaskTestDavidModelC, TestAicpuMdlDestroy_AllocTaskInfoFail)
{
    rtModel_t model = CreateModel();
    Model* mdl = rt_ut::UnwrapOrNull<Model>(model);
    ASSERT_NE(mdl, nullptr);

    MOCKER(CheckTaskCanSend).stubs().will(returnValue(RT_ERROR_NONE));
    MOCKER_CPP(static_cast<TaskInfo* (Stream::*)(TaskInfo*, tsTaskType_t, rtError_t&, uint32_t, UpdateTaskFlag)>(
                   &Stream::AllocTask))
        .stubs()
        .with(mockcpp::any(), mockcpp::any(), outBound(RT_ERROR_INVALID_VALUE), mockcpp::any(), mockcpp::any())
        .will(returnValue(static_cast<TaskInfo*>(nullptr)));

    rtError_t ret = AicpuMdlDestroy(mdl);
    EXPECT_NE(ret, RT_ERROR_NONE);

    DestroyModel(model);
}

TEST_F(TaskTestDavidModelC, TestAicpuMdlDestroy_SyncTimeout)
{
    rtModel_t model = CreateModel();
    Model* mdl = rt_ut::UnwrapOrNull<Model>(model);
    ASSERT_NE(mdl, nullptr);

    MOCKER(CheckTaskCanSend).stubs().will(returnValue(RT_ERROR_NONE));
    MOCKER_CPP(static_cast<TaskInfo* (Stream::*)(TaskInfo*, tsTaskType_t, rtError_t&, uint32_t, UpdateTaskFlag)>(
                   &Stream::AllocTask))
        .stubs()
        .will(returnValue(&g_mockTaskInfo));
    MOCKER(ModelToAicpuTaskInit).stubs().will(returnValue(RT_ERROR_NONE));
    MOCKER(DavidSendTask).stubs().will(returnValue(RT_ERROR_NONE));
    MOCKER_CPP_VIRTUAL(stream_, &Stream::Synchronize).stubs().will(returnValue(RT_ERROR_STREAM_SYNC_TIMEOUT));

    rtError_t ret = AicpuMdlDestroy(mdl);
    EXPECT_EQ(ret, RT_ERROR_STREAM_SYNC_TIMEOUT);

    DestroyModel(model);
}

TEST_F(TaskTestDavidModelC, TestAicpuMdlDestroy_SyncError)
{
    rtModel_t model = CreateModel();
    Model* mdl = rt_ut::UnwrapOrNull<Model>(model);
    ASSERT_NE(mdl, nullptr);

    MOCKER(CheckTaskCanSend).stubs().will(returnValue(RT_ERROR_NONE));
    MOCKER_CPP(static_cast<TaskInfo* (Stream::*)(TaskInfo*, tsTaskType_t, rtError_t&, uint32_t, UpdateTaskFlag)>(
                   &Stream::AllocTask))
        .stubs()
        .will(returnValue(&g_mockTaskInfo));
    MOCKER(ModelToAicpuTaskInit).stubs().will(returnValue(RT_ERROR_NONE));
    MOCKER(DavidSendTask).stubs().will(returnValue(RT_ERROR_NONE));
    MOCKER_CPP_VIRTUAL(stream_, &Stream::Synchronize).stubs().will(returnValue(RT_ERROR_INVALID_VALUE));

    rtError_t ret = AicpuMdlDestroy(mdl);
    EXPECT_NE(ret, RT_ERROR_NONE);

    DestroyModel(model);
}

TEST_F(TaskTestDavidModelC, TestMdlBindTaskSubmit_CheckTaskCanSendFail)
{
    rtModel_t model = CreateModel();
    Model* mdl = rt_ut::UnwrapOrNull<Model>(model);
    ASSERT_NE(mdl, nullptr);

    rtStream_t stream = CreateExtraStream();
    Stream* stm = rt_ut::UnwrapOrNull<Stream>(stream);

    MOCKER(CheckTaskCanSend).stubs().will(returnValue(RT_ERROR_INVALID_VALUE));

    rtError_t ret = MdlBindTaskSubmit(mdl, stm, 0U);
    EXPECT_NE(ret, RT_ERROR_NONE);

    DestroyExtraStream(stream);
    DestroyModel(model);
}

TEST_F(TaskTestDavidModelC, TestMdlBindTaskSubmit_MaintainceTaskInitFail)
{
    rtModel_t model = CreateModel();
    Model* mdl = rt_ut::UnwrapOrNull<Model>(model);
    ASSERT_NE(mdl, nullptr);

    rtStream_t stream = CreateExtraStream();
    Stream* stm = rt_ut::UnwrapOrNull<Stream>(stream);

    MOCKER(CheckTaskCanSend).stubs().will(returnValue(RT_ERROR_NONE));
    MOCKER_CPP(static_cast<TaskInfo* (Stream::*)(TaskInfo*, tsTaskType_t, rtError_t&, uint32_t, UpdateTaskFlag)>(
                   &Stream::AllocTask))
        .stubs()
        .will(returnValue(&g_mockTaskInfo));
    MOCKER(DavidModelMaintainceTaskInit).stubs().will(returnValue(RT_ERROR_INVALID_VALUE));
    MOCKER(TaskUnInitProc).stubs();
    MOCKER(TaskRollBack).stubs();

    rtError_t ret = MdlBindTaskSubmit(mdl, stm, 0U);
    EXPECT_NE(ret, RT_ERROR_NONE);

    DestroyExtraStream(stream);
    DestroyModel(model);
}

TEST_F(TaskTestDavidModelC, TestMdlBindTaskSubmit_SendTaskFail)
{
    rtModel_t model = CreateModel();
    Model* mdl = rt_ut::UnwrapOrNull<Model>(model);
    ASSERT_NE(mdl, nullptr);

    rtStream_t stream = CreateExtraStream();
    Stream* stm = rt_ut::UnwrapOrNull<Stream>(stream);

    MOCKER(CheckTaskCanSend).stubs().will(returnValue(RT_ERROR_NONE));
    MOCKER_CPP(static_cast<TaskInfo* (Stream::*)(TaskInfo*, tsTaskType_t, rtError_t&, uint32_t, UpdateTaskFlag)>(
                   &Stream::AllocTask))
        .stubs()
        .will(returnValue(&g_mockTaskInfo));
    MOCKER(DavidModelMaintainceTaskInit).stubs().will(returnValue(RT_ERROR_NONE));
    MOCKER(DavidSendTask).stubs().will(returnValue(RT_ERROR_INVALID_VALUE));
    MOCKER(TaskUnInitProc).stubs();
    MOCKER(TaskRollBack).stubs();

    rtError_t ret = MdlBindTaskSubmit(mdl, stm, 0U);
    EXPECT_NE(ret, RT_ERROR_NONE);

    DestroyExtraStream(stream);
    DestroyModel(model);
}

TEST_F(TaskTestDavidModelC, TestModelAddEndGraph_EndGraphNumExceed)
{
    rtModel_t model = CreateModel();
    Model* mdl = rt_ut::UnwrapOrNull<Model>(model);
    ASSERT_NE(mdl, nullptr);

    mdl->IncEndGraphNum();

    rtError_t ret = ModelAddEndGraph(mdl, stream_, 0U);
    EXPECT_EQ(ret, RT_ERROR_MODEL_ENDGRAPH);

    DestroyModel(model);
}

TEST_F(TaskTestDavidModelC, TestModelAddEndGraph_StreamNotBoundToModel)
{
    rtModel_t model = CreateModel();
    Model* mdl = rt_ut::UnwrapOrNull<Model>(model);
    ASSERT_NE(mdl, nullptr);

    rtError_t ret = ModelAddEndGraph(mdl, stream_, 0U);
    EXPECT_EQ(ret, RT_ERROR_STREAM_INVALID);

    DestroyModel(model);
}

TEST_F(TaskTestDavidModelC, TestModelLoadCompleteByStream_SubmitLoadCompleteDirectly)
{
    rtModel_t model = CreateModel();
    Model* mdl = rt_ut::UnwrapOrNull<Model>(model);
    ASSERT_NE(mdl, nullptr);

    mdl->streams_.push_front(stream_);
    stream_->SetModel(mdl);

    mdl->isModelComplete_ = true;
    mdl->SetModelExecutorType(EXECUTOR_AICPU);

    MockIsSupportFeatureFalse();
    MOCKER_CPP_VIRTUAL(stream_, &Stream::Synchronize).stubs().will(returnValue(RT_ERROR_NONE));

    MOCKER(CheckTaskCanSend).stubs().will(returnValue(RT_ERROR_NONE));
    MOCKER_CPP(static_cast<TaskInfo* (Stream::*)(TaskInfo*, tsTaskType_t, rtError_t&, uint32_t, UpdateTaskFlag)>(
                   &Stream::AllocTask))
        .stubs()
        .will(returnValue(&g_mockTaskInfo));
    MOCKER(DavidModelMaintainceTaskInit).stubs().will(returnValue(RT_ERROR_NONE));
    MOCKER(DavidSendTask).stubs().will(returnValue(RT_ERROR_NONE));

    rtError_t ret = ModelLoadCompleteByStream(mdl);
    EXPECT_EQ(ret, RT_ERROR_NONE);

    mdl->streams_.remove(stream_);
    stream_->SetModel(nullptr);
    DestroyModel(model);
}

class ModelTaskUpdateMissingTaskTest : public TaskTestDavidModelC, public testing::WithParamInterface<bool> {
protected:
    void SetUp() override
    {
        TaskTestDavidModelC::SetUp();
        oldSplitCtx_ = stream_->GetAutoSplitCtx();
        oldAutoSplit_ = stream_->IsAutoSplitSq();
        oldIsSlave_ = stream_->IsSlaveStream();
        slaveHandle_ = CreateExtraStream();
        slave_ = rt_ut::UnwrapOrNull<Stream>(slaveHandle_);
        ASSERT_NE(slave_, nullptr);
        // Normal David streams do not allocate the map used by model-update task recording.
        ASSERT_GT(slave_->GetSqDepth(), 2U);
        ASSERT_EQ(slave_->AllocPosToTaskIdMap(), RT_ERROR_NONE);
    }

    void TearDown() override
    {
        stream_->SetAutoSplitCtx(oldSplitCtx_);
        stream_->SetAutoSplitSq(oldAutoSplit_);
        stream_->SetIsSlaveStream(oldIsSlave_);
        // Restore real task allocation and lookup before destroying either stream.
        GlobalMockObject::verify();
        if (slave_ != nullptr) {
            // The recorded IDs belong to injected lookup results, not allocated tasks.
            slave_->ResetHostResourceForPersistentStream();
            DestroyExtraStream(slaveHandle_);
        }
        TaskTestDavidModelC::TearDown();
    }

    rtStream_t slaveHandle_ = nullptr;
    Stream* slave_ = nullptr;
    AutoSplitSqContext* oldSplitCtx_ = nullptr;
    bool oldAutoSplit_ = false;
    bool oldIsSlave_ = false;
    AutoSplitSqContext splitCtx_ = {};
    TaskInfo updateTask_ = {};
    TaskInfo missingTask_ = {};
    TaskInfo matchingTask_ = {};
};

TEST_P(ModelTaskUpdateMissingTaskTest, SkipsMissingTasksAndSelectsDestinationStream)
{
    constexpr uint32_t targetTaskSn = 123U;
    InitByStream(&missingTask_, slave_);
    missingTask_.id = 10U;
    InitByStream(&matchingTask_, slave_);
    matchingTask_.id = 11U;
    matchingTask_.taskSn = targetTaskSn;
    ASSERT_EQ(slave_->StarsAddTaskToStreamForModelUpdate(&missingTask_, 1U), RT_ERROR_NONE);
    ASSERT_EQ(slave_->StarsAddTaskToStreamForModelUpdate(&matchingTask_, 1U), RT_ERROR_NONE);
    ASSERT_NE(stream_->Id_(), slave_->Id_());

    splitCtx_.slaveStreams.push_back(slave_);
    stream_->SetAutoSplitCtx(&splitCtx_);
    stream_->SetAutoSplitSq(true);
    stream_->SetIsSlaveStream(false);
    MOCKER_CPP(&TaskFactory::GetTask)
        .expects(once())
        .with(eq(slave_->Id_()), eq(missingTask_.id))
        .will(returnValue(static_cast<TaskInfo*>(nullptr)));
    TaskInfo* followingTask = GetParam() ? &matchingTask_ : nullptr;
    MOCKER_CPP(&TaskFactory::GetTask)
        .expects(once())
        .with(eq(slave_->Id_()), eq(matchingTask_.id))
        .will(returnValue(followingTask));

    PlainProgram program;
    Program* programBase = &program;
    rtMdlTaskUpdateInfo_t para = {};
    para.hdl = rt_ut::InitAndExportHandle<rtBinHandle>(programBase);
    MOCKER_CPP(&Program::CopyTilingTabToDev).stubs().will(returnValue(RT_ERROR_NONE));
    MOCKER(CheckTaskCanSend).stubs().will(returnValue(RT_ERROR_NONE));
    InitByStream(&updateTask_, stream_);
    MOCKER_CPP(static_cast<TaskInfo* (Stream::*)(TaskInfo*, tsTaskType_t, rtError_t&, uint32_t, UpdateTaskFlag)>(
                   &Stream::AllocTask))
        .stubs()
        .will(returnValue(&updateTask_));
    MOCKER(DavidSendTask).expects(once()).with(eq(&updateTask_), eq(stream_)).will(returnValue(RT_ERROR_NONE));

    EXPECT_EQ(MdlTaskUpdate(stream_, targetTaskSn, stream_, &para), RT_ERROR_NONE);
    EXPECT_EQ(updateTask_.type, TS_TASK_TYPE_MODEL_TASK_UPDATE);
    const uint16_t expectedStreamId = static_cast<uint16_t>(GetParam() ? slave_->Id_() : stream_->Id_());
    EXPECT_EQ(updateTask_.u.mdlUpdateTask.desStreamId, expectedStreamId);
    EXPECT_EQ(updateTask_.u.mdlUpdateTask.destaskId, targetTaskSn);
    EXPECT_EQ(updateTask_.u.mdlUpdateTask.exeStreamId, static_cast<uint16_t>(stream_->Id_()));
}

INSTANTIATE_TEST_SUITE_P(NullTaskLookup, ModelTaskUpdateMissingTaskTest, testing::Values(true, false));