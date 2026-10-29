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
#include <fstream>
#include <climits>
#include "gtest/gtest.h"
#include "mockcpp/mockcpp.hpp"
#include "device_simulator_manager.h"
#include "errno/error_code.h"
#include "msprof_start.h"
#include "../stub/cli_stub.h"
#include "data_manager.h"
#include "platform/platform.h"
#include "job_device_rpc.h"
#include "job_device_soc.h"
#include "utils.h"
#include "hdc_api.h"
#include "dev_mgr_api.h"
#include "devprof_drv_aicpu.h"
#include "data_check.h"

using namespace analysis::dvvp::common::error;
using namespace Analysis::Dvvp::Common::Platform;
using namespace Cann::Dvvp::Test;

static const char RC_LITE_V2_RM_RF[] = "rm -rf ./cliRcLiteV2stest_workspace";
static const char RC_LITE_V2_MKDIR[] = "mkdir ./cliRcLiteV2stest_workspace";
static const char RC_LITE_V2_OUTPUT_DIR[] = "--output=./cliRcLiteV2stest_workspace/output";

class CliRcLiteV2Stest : public testing::Test {
protected:
    virtual void SetUp()
    {
        DlStub();
        const ::testing::TestInfo* curTest = ::testing::UnitTest::GetInstance()->current_test_info();
        DataMgr().Init("david", curTest->name());
        optind = 1;
        system(RC_LITE_V2_MKDIR);
        system("touch ./cli");
        EXPECT_EQ(2, SimulatorMgr().CreateDeviceSimulator(2, StPlatformType::RC_LITE_V2_TYPE));
        SimulatorMgr().SetSocSide(SocType::HOST);
    }
    virtual void TearDown()
    {
        GlobalMockObject::verify();
        DevprofDrvAicpu::instance()->isRegister_ = false; // 重置aicpu注册状态，使单进程内能多次注册
        EXPECT_EQ(2, SimulatorMgr().DelDeviceSimulator(2, StPlatformType::RC_LITE_V2_TYPE));
        system(RC_LITE_V2_RM_RF);
        system("rm -rf ./cli");
        DataMgr().UnInit();
        MsprofMgr().UnInit();
    }
    void SetPerfEnv()
    {
        MOCKER(mmWaitPid).stubs().will(returnValue(1));
        std::string perfDataDirStub = "./perf";
        MockPerfDir(perfDataDirStub);
    }
    void DlStub()
    {
        MOCKER(dlopen).stubs().will(invoke(mmDlopen));
        MOCKER(dlsym).stubs().will(invoke(mmDlsym));
        MOCKER(OsalDlopen).stubs().will(invoke(mmDlopen));
        MOCKER(OsalDlsym).stubs().will(invoke(mmDlsym));
        MOCKER(dlclose).stubs().will(invoke(mmDlclose));
        MOCKER(dlerror).stubs().will(invoke(mmDlerror));
    }
};

TEST_F(CliRcLiteV2Stest, CliTaskTime)
{
    // TaskTime
    const char* argv[] = {RC_LITE_V2_OUTPUT_DIR, "--task-time=on"};
    std::vector<std::string> dataList = {
        "ffts_profile.data", "stars_soc.data", "ts_track.data", "stars_soc_profile.data"};
    std::vector<std::string> blackDataList = {};
    MsprofMgr().SetDeviceCheckList(dataList, blackDataList);
    EXPECT_EQ(PROFILING_SUCCESS, MsprofMgr().MsprofStartByAppMode(sizeof(argv) / sizeof(char*), argv));
}

TEST_F(CliRcLiteV2Stest, CliTaskBlockOn)
{
    const char* argv[] = {RC_LITE_V2_OUTPUT_DIR, "--task-block=on"};
    std::vector<std::string> dataList = {"ffts_profile.data"};
    MsprofMgr().SetDeviceCheckList(dataList);
    EXPECT_EQ(PROFILING_SUCCESS, MsprofMgr().MsprofStartByAppMode(sizeof(argv) / sizeof(char*), argv));
}

TEST_F(CliRcLiteV2Stest, CliL2CacheTask)
{
    const char* argv[] = {RC_LITE_V2_OUTPUT_DIR, "--aic-metrics=L2Cache"};
    std::vector<std::string> dataList = {"ffts_profile.data"};
    MsprofMgr().SetDeviceCheckList(dataList);
    EXPECT_EQ(PROFILING_SUCCESS, MsprofMgr().MsprofStartByAppMode(sizeof(argv) / sizeof(char*), argv));
}

// RC Lite V2 inherits the LLC collection flow: --sys-hardware-mem opens
// ProfLlcJob on channel 8 and writes data/llc.data.
TEST_F(CliRcLiteV2Stest, CliSysHardwareMemLlcBandwidth)
{
    std::cout << "[RCLLC] Start --sys-hardware-mem flow: CLI -> ProfLlcJob -> channel 8 -> llc.data" << std::endl;
    std::vector<const char*> argv = {RC_LITE_V2_OUTPUT_DIR, "--sys-hardware-mem=on"};
    const std::vector<std::string> dataList = {"llc.data"};
    MsprofMgr().SetDeviceCheckList(dataList);
    EXPECT_EQ(PROFILING_SUCCESS, MsprofMgr().MsprofStartBySysMode(static_cast<int32_t>(argv.size()), argv.data()));
    EXPECT_TRUE(Platform::instance()->CheckIfSupport(PLATFORM_SYS_DEVICE_LLC));
    EXPECT_TRUE(Platform::instance()->CheckIfSupport(PLATFORM_SYS_DEVICE_QOS));
    EXPECT_TRUE(Platform::instance()->CheckIfSupport(PLATFORM_SYS_DEVICE_LOW_POWER));
    std::cout << "[RCLLC] Finish: DataCheck passed and platform supports LLC/QoS/low-power" << std::endl;
}

// --sys-hardware-mem also opens accelerator bandwidth collection. Runtime asks
// HAL for the driver stream list, keeps the first eight streams limited by the
// RC Lite V2 monitor number, then sends them through StarsSocQosProfileConfigT.
TEST_F(CliRcLiteV2Stest, CliAcceleratorBandwidthFirstEightStreams)
{
    std::cout << "[RCQoS] Start --sys-hardware-mem flow: HAL stream query -> min(8, 10) -> channel 52 -> "
              << "stars_soc_profile.data" << std::endl;
    std::vector<const char*> argv = {RC_LITE_V2_OUTPUT_DIR, "--sys-hardware-mem=on"};
    const std::vector<std::string> dataList = {"stars_soc_profile.data"};
    MsprofMgr().SetDeviceCheckList(dataList);
    EXPECT_EQ(PROFILING_SUCCESS, MsprofMgr().MsprofStartBySysMode(static_cast<int32_t>(argv.size()), argv.data()));
    EXPECT_EQ(10U, MsprofMgr().GetQosStreamCountForTest());
    const std::map<uint32_t, std::vector<uint8_t>>& queriedMpamIdsByDevice =
        MsprofMgr().GetQosQueriedMpamIdsByDeviceForTest();
    ASSERT_EQ(1U, queriedMpamIdsByDevice.size());
    for (const auto& iter : queriedMpamIdsByDevice) {
        const std::vector<uint8_t> expectedMpamIds = {1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U};
        EXPECT_EQ(expectedMpamIds, iter.second) << "device " << iter.first;
    }
    std::cout << "[RCQoS] Finish: DataCheck passed, HAL returns 10 streams and Runtime keeps first 8" << std::endl;
}

// Low-power profiling is enabled by default and reuses channel 52. The explicit
// 100Hz setting is converted by Runtime to a 10000us period before delivery.
TEST_F(CliRcLiteV2Stest, CliLowPowerProfiling)
{
    std::cout << "[RCLowPower] Start --sys-lp flow: 100Hz -> 10000us -> channel 52 -> "
              << "stars_soc_profile.data" << std::endl;
    std::vector<const char*> argv = {RC_LITE_V2_OUTPUT_DIR, "--sys-lp=on", "--sys-lp-freq=100"};
    const std::vector<std::string> dataList = {"stars_soc_profile.data"};
    MsprofMgr().SetDeviceCheckList(dataList);
    EXPECT_EQ(PROFILING_SUCCESS, MsprofMgr().MsprofStartBySysMode(static_cast<int32_t>(argv.size()), argv.data()));
    EXPECT_TRUE(Platform::instance()->CheckIfSupport(PLATFORM_SYS_DEVICE_LOW_POWER));
    EXPECT_TRUE(MsprofMgr().GetLowPowerEnabledForTest());
    EXPECT_EQ(10000, MsprofMgr().GetLowPowerPeriodUsForTest());
    std::cout << "[RCLowPower] Finish: DataCheck passed and period is 10000us" << std::endl;
}

TEST_F(CliRcLiteV2Stest, CliLowPowerFreqOverFlow)
{
    std::cout << "[RCLowPowerOverflow] Start validation flow: 101Hz is rejected by current range [1,100]" << std::endl;
    std::vector<const char*> argv = {RC_LITE_V2_OUTPUT_DIR, "--sys-lp=on", "--sys-lp-freq=101"};
    EXPECT_EQ(PROFILING_FAILED, MsprofMgr().MsprofStartBySysMode(static_cast<int32_t>(argv.size()), argv.data()));
    std::cout << "[RCLowPowerOverflow] Finish: validation failed as expected" << std::endl;
}

// F Die task data reuses channel 45, but is registered by ProfHwtsLogFDieJob
// and written to stars_f_soc.data instead of the normal HWTS file.
TEST_F(CliRcLiteV2Stest, CliFDieTaskTime)
{
    std::cout << "[RCFDieTaskTime] Start --task-time flow: ProfHwtsLogFDieJob -> channel 45 -> "
              << "stars_f_soc.data" << std::endl;
    std::vector<const char*> argv = {RC_LITE_V2_OUTPUT_DIR, "--task-time=on"};
    const std::vector<std::string> dataList = {"stars_f_soc.data"};
    MsprofMgr().SetDeviceCheckList(dataList);
    EXPECT_EQ(PROFILING_SUCCESS, MsprofMgr().MsprofStartByAppMode(static_cast<int32_t>(argv.size()), argv.data()));
    EXPECT_TRUE(Platform::instance()->CheckIfSupport(PLATFORM_STARS_F_DIE));
    std::cout << "[RCFDieTaskTime] Finish: DataCheck passed and F-Die feature is enabled" << std::endl;
}

// task-block maps to dvpp_vpc_block in DrvStarsSocLogStart for channel 45 and
// must collect the first/last block data of IO-STARS scheduled DVPP tasks.
TEST_F(CliRcLiteV2Stest, CliFDieTaskBlock)
{
    std::cout << "[RCFDieTaskBlock] Start --task-block flow: ProfHwtsLogFDieJob -> channel 45 -> "
              << "stars_f_soc.data" << std::endl;
    std::vector<const char*> argv = {RC_LITE_V2_OUTPUT_DIR, "--task-block=on"};
    const std::vector<std::string> dataList = {"stars_f_soc.data"};
    MsprofMgr().SetDeviceCheckList(dataList);
    EXPECT_EQ(PROFILING_SUCCESS, MsprofMgr().MsprofStartByAppMode(static_cast<int32_t>(argv.size()), argv.data()));
    EXPECT_TRUE(Platform::instance()->CheckIfSupport(PLATFORM_STARS_F_DIE));
    std::cout << "[RCFDieTaskBlock] Finish: DataCheck passed and F-Die feature is enabled" << std::endl;
}

TEST_F(CliRcLiteV2Stest, CliAivNotSupport)
{
    const char* argv[] = {RC_LITE_V2_OUTPUT_DIR, "--aiv=on"};
    EXPECT_EQ(PROFILING_FAILED, MsprofMgr().MsprofStartByAppMode(sizeof(argv) / sizeof(char*), argv));
}
