/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 * This program is free software, you can redistribute it and/or modify it under the terms and conditions of
 * CANN Open Software License Agreement Version 2.0 (the "License").
 * Please refer to the License for details. You may not use this file except in compliance with the License.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 * See LICENSE in the root of the software repository for the full text of the License.
 */
#include "gtest/gtest.h"
#include "mockcpp/mockcpp.hpp"
#include "dev_info_manage.h"
#include "dev_simt_stack_checker.hpp"
#define private public
#include "raw_device.hpp"
#undef private
#include "npu_driver_dcache_lock.hpp"
#include "npu_driver.hpp"
#include "runtime.hpp"

using namespace cce::runtime;

namespace {
uint64_t g_dcacheAllocSize = 0ULL;
uint64_t g_simtStackAllocSize = 0ULL;

rtError_t StubAllocAddrForDcache(const uint32_t deviceId, void*& dcacheAddr, const uint64_t size, void*& drvHandle)
{
    UNUSED(deviceId);
    UNUSED(dcacheAddr);
    UNUSED(drvHandle);
    g_dcacheAllocSize = size;
    return RT_ERROR_NONE;
}

rtError_t StubSimtStackAlloc(
    Driver* driver, void** addr, uint64_t size, rtMemType_t memType, uint32_t deviceId, DevMemBackupType backupType,
    uint16_t moduleId, bool isLogError, DevMemAllocConfig config, bool isNewApi)
{
    UNUSED(driver);
    UNUSED(addr);
    UNUSED(moduleId);
    UNUSED(isLogError);
    UNUSED(config);
    UNUSED(isNewApi);
    EXPECT_EQ(memType, RT_MEMORY_DDR);
    EXPECT_EQ(deviceId, 0U);
    EXPECT_EQ(backupType, DevMemBackupType::SNAPSHOT_OPTIONAL_BACKUP);
    g_simtStackAllocSize = size;
    return RT_ERROR_DRV_ERR;
}
} // namespace

class DavidDieTest : public testing::Test {
protected:
    void SetUp() override
    {
        GlobalMockObject::reset();
        g_dcacheAllocSize = 0ULL;
        g_simtStackAllocSize = 0ULL;
    }

    void TearDown() override { GlobalMockObject::verify(); }

    void CheckStackAllocSize(const uint8_t dieNum, const uint64_t expectedSize)
    {
        DevProperties props = {};
        ASSERT_EQ(GET_DEV_PROPERTIES(CHIP_DAVID, props), RT_ERROR_NONE);

        RawDevice device(0U);
        device.RefreshDevProperties(props);
        device.davidDieNum_ = dieNum;
        MOCKER(AllocAddrForDcache).expects(once()).will(invoke(StubAllocAddrForDcache));

        ASSERT_EQ(device.AllocStackPhyBaseDavid(), RT_ERROR_NONE);
        EXPECT_EQ(g_dcacheAllocSize, expectedSize);
    }

    void CheckSimtStackAllocSize(const bool useMaxDieNum, const uint64_t expectedSize)
    {
        DevProperties props = {};
        ASSERT_EQ(GET_DEV_PROPERTIES(CHIP_DAVID, props), RT_ERROR_NONE);
        props.simtStackUseMaxDavidDieNum = useMaxDieNum;

        Runtime* const runtime = Runtime::Instance();
        const uint64_t oldWarpStackSize = runtime->GetSimtWarpStkSize();
        const uint32_t oldDvgWarpStackSize = runtime->GetSimtDvgWarpStkSize();
        runtime->SetSimtWarpStkSize(128U);
        runtime->SetSimtDvgWarpStkSize(32U);

        NpuDriver driver;
        RawDevice device(0U);
        device.RefreshDevProperties(props);
        device.davidDieNum_ = 1U;
        device.driver_ = &driver;
        MOCKER(IsNeedAllocSimtStack).expects(once()).will(returnValue(true));
        MOCKER_CPP_VIRTUAL(device.Driver_(), &Driver::DevMemAllocWithBackupFlag)
            .expects(once())
            .will(invoke(StubSimtStackAlloc));

        EXPECT_EQ(device.AllocSimtStackPhyBase(CHIP_DAVID), RT_ERROR_DRV_ERR);
        EXPECT_EQ(g_simtStackAllocSize, expectedSize);

        runtime->SetSimtWarpStkSize(oldWarpStackSize);
        runtime->SetSimtDvgWarpStkSize(oldDvgWarpStackSize);
    }
};

TEST_F(DavidDieTest, RegisteredCoreNumPerDie)
{
    DevProperties props = {};
    ASSERT_EQ(GET_DEV_PROPERTIES(CHIP_DAVID, props), RT_ERROR_NONE);
    EXPECT_EQ(props.aicNumPerDie, 18U); // 18 AICs per die
    EXPECT_EQ(props.aivNumPerDie, 36U); // 36 AIVs per die
    EXPECT_EQ(props.aicNum, 36U);       // 2 dies
    EXPECT_EQ(props.aivNum, 72U);       // 2 dies
}

TEST_F(DavidDieTest, AllocStackPhyBaseForSingleDie) { CheckStackAllocSize(1U, 32ULL * 1024ULL * (18ULL + 36ULL)); }

TEST_F(DavidDieTest, AllocStackPhyBaseForDualDie) { CheckStackAllocSize(2U, 32ULL * 1024ULL * 2ULL * (18ULL + 36ULL)); }

TEST_F(DavidDieTest, AllocSimtStackForActualDieNum)
{
    CheckSimtStackAllocSize(
        false, 36ULL * RT_MAX_WARP_NUM_PER_VECTOR_CORE * (128ULL + 32ULL) + STACK_PHY_BASE_ALIGN_LEN);
}

TEST_F(DavidDieTest, AllocSimtStackForMaxDieNum)
{
    CheckSimtStackAllocSize(
        true, 2ULL * 36ULL * RT_MAX_WARP_NUM_PER_VECTOR_CORE * (128ULL + 32ULL) + STACK_PHY_BASE_ALIGN_LEN);
}
