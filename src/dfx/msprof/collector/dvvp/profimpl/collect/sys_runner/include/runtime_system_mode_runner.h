/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef PROFILING_RUNTIME_SYSTEM_MODE_RUNNER_H
#define PROFILING_RUNTIME_SYSTEM_MODE_RUNNER_H

#include <string>
#include <vector>
#include "msprof_task.h"
#include "message/prof_params.h"

namespace analysis {
namespace dvvp {
namespace runner {
class RuntimeSystemModeRunner {
public:
    static int32_t Run(const SHARED_PTR_ALIA<message::ProfileParams>& params, const std::string& baseDir);

private:
    RuntimeSystemModeRunner(const SHARED_PTR_ALIA<message::ProfileParams>& params, const std::string& baseDir);

    int32_t Start();
    int32_t StartSysTask();
    int32_t StartHostJobs();
    int32_t StartDeviceJobs(const std::string& device);
    int32_t StartHostTask(const std::string& resultDir, uint32_t deviceId);
    int32_t StartDeviceTask(const std::string& resultDir, const std::string& device);
    int32_t WaitSysTask() const;
    void StopTask();
    bool IsDeviceJob() const;
    int32_t CreateJobDir(const std::string& device, std::string& resultDir) const;
    int32_t RecordOutPut() const;
    int32_t CreateUploader(const std::string& jobId, const std::string& resultDir) const;
    bool CreateSampleJsonFile(
        const SHARED_PTR_ALIA<message::ProfileParams>& params, const std::string& resultDir) const;
    bool CreateDoneFile(const std::string& absolutePath, const std::string& fileSize) const;
    int32_t WriteCtrlDataToFile(const std::string& absolutePath, const std::string& data, int32_t dataLen) const;
    SHARED_PTR_ALIA<message::ProfileParams> GenerateHostParam(
        const SHARED_PTR_ALIA<message::ProfileParams>& params) const;
    SHARED_PTR_ALIA<message::ProfileParams> GenerateDeviceParam(
        const SHARED_PTR_ALIA<message::ProfileParams>& params) const;

    SHARED_PTR_ALIA<message::ProfileParams> params_;
    std::string baseDir_;
    std::vector<SHARED_PTR_ALIA<Analysis::Dvvp::Msprof::MsprofTask>> taskList_;
};
} // namespace runner
} // namespace dvvp
} // namespace analysis

#endif
