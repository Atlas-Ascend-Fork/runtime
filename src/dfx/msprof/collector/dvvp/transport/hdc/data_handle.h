/**
 * Copyright (c) 2025 Huawei Technologies Co., Ltd.
 * This program is free software, you can redistribute it and/or modify it under the terms and conditions of
 * CANN Open Software License Agreement Version 2.0 (the "License").
 * Please refer to the License for details. You may not use this file except in compliance with the License.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 * See LICENSE in the root of the software repository for the full text of the License.
 */
#ifndef ANALYSIS_DVVP_TRANSPORT_DATA_HANDLE_H
#define ANALYSIS_DVVP_TRANSPORT_DATA_HANDLE_H

#include <map>
#include "config/config.h"
#include <mutex>
#include "message/prof_params.h"
#include "singleton/singleton.h"
#include "proto/profiler.pb.h"
#include "utils/utils.h"

namespace Analysis {
namespace Dvvp {
namespace Msprof {
using namespace analysis::dvvp::common::utils;
using PFMessagehandler = int32_t (*)(SHARED_PTR_ALIA<google::protobuf::Message> message);
class MsprofTask;
class IDataHandleCB {
public:
    virtual ~IDataHandleCB();
};

class HdcTransportDataHandle : public IDataHandleCB,
                               public analysis::dvvp::common::singleton::Singleton<HdcTransportDataHandle> {
public:
    HdcTransportDataHandle();
    ~HdcTransportDataHandle() override;
    static std::map<const google::protobuf::Descriptor*, PFMessagehandler> CreateHandlerMap();
    static int32_t ReceiveStreamData(CONST_VOID_PTR data, uint32_t dataLen);
    static void RegisterTask(const std::string& jobId, const SHARED_PTR_ALIA<MsprofTask>& task);
    static void UnregisterAllTask();

private:
    static int32_t ProcessStreamFileChunk(SHARED_PTR_ALIA<google::protobuf::Message> message);
    static int32_t ProcessDataChannelFinish(SHARED_PTR_ALIA<google::protobuf::Message> message);
    static int32_t ProcessFinishJobRspMsg(SHARED_PTR_ALIA<google::protobuf::Message> message);
    static int32_t ProcessResponseMsg(SHARED_PTR_ALIA<google::protobuf::Message> message);
    static int32_t ProcessRspCommon(const std::string& jobId, const std::string& encoded);
    static SHARED_PTR_ALIA<MsprofTask> GetTask(const std::string& jobId);

private:
    static std::map<const google::protobuf::Descriptor*, PFMessagehandler> handlerMap_;
    static std::map<std::string, SHARED_PTR_ALIA<MsprofTask>> taskMap_;
    static std::mutex taskMapMutex_;
};
} // namespace Msprof
} // namespace Dvvp
} // namespace Analysis
#endif
