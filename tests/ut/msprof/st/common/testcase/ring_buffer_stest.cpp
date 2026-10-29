/**
 * Copyright (c) 2025 Huawei Technologies Co., Ltd.
 * This program is free software, you can redistribute it and/or modify it under the terms and conditions of
 * CANN Open Software License Agreement Version 2.0 (the "License").
 * Please refer to the License for details. You may not use this file except in compliance with the License.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 * See LICENSE in the root of the software repository for the full text of the License.
 */
#include <string>
#include <memory>
#include "gtest/gtest.h"
#include "mockcpp/mockcpp.hpp"
#include "queue/ring_buffer.h"
#include "queue/report_buffer.h"

using namespace analysis::dvvp::common::queue;

class COMMON_QUEUE_RING_BUFFER_STEST : public testing::Test {
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
};

TEST_F(COMMON_QUEUE_RING_BUFFER_STEST, ReportBuffer_GetUsedSize)
{
    std::shared_ptr<ReportBuffer<int> > bq(new ReportBuffer<int>(-1));
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    int data4 = 4;
    int data5 = 5;

    std::string name = "test";
    bq->Init(4, name);
    EXPECT_EQ(4, bq->capacity_);

    bq->BatchPush(1, &data1, sizeof(data1));
    EXPECT_EQ(1, bq->GetUsedSize());
    bq->BatchPush(1, &data2, sizeof(data2));
    EXPECT_EQ(2, bq->GetUsedSize());
    bq->BatchPush(1, &data3, sizeof(data3));
    EXPECT_EQ(3, bq->GetUsedSize());
    bq->BatchPush(1, &data4, sizeof(data4));
    EXPECT_EQ(4, bq->GetUsedSize());

    EXPECT_EQ(0, bq->readIndex_.load());
    EXPECT_EQ(4, bq->writeIndex_.load());

    bq->BatchPush(1, &data5, sizeof(data5));
    EXPECT_EQ(1, bq->GetUsedSize());

    size_t popSize = sizeof(int);
    void* popPtr = bq->BatchPop(1, popSize, true);
    EXPECT_NE(nullptr, popPtr);
    EXPECT_EQ(5, *static_cast<int*>(popPtr));
    EXPECT_EQ(0, bq->GetUsedSize());

    popSize = sizeof(int);
    EXPECT_EQ(nullptr, bq->BatchPop(1, popSize, true));
    bq->UnInit();
}
