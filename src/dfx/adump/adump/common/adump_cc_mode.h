/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 * This program is free software, you can redistribute it and/or modify it under the terms and conditions of
 * CANN Open Software License Agreement Version 2.0 (the "License").
 * Please refer to the License for details. You may not use this file except in compliance with the License.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 * See LICENSE in the root of the software repository for the full text of the License.
 */
#ifndef ADUMP_COMMON_ADUMP_CC_MODE_H
#define ADUMP_COMMON_ADUMP_CC_MODE_H

// CC means confidential computing. This file caches rtDeviceGetCcMode results and provides the mode checks
// used by Adump data-output entry points.

#include <cstdint>
#include <atomic>
#include <map>
#include <mutex>
#include <utility>

#include "ascend_hal_base.h"
#include "error_codes/rt_error_codes.h"
#include "rt_inner_device.h"
#include "runtime/dev.h"
#include "log/adx_log.h"

namespace Adx {
constexpr int32_t CC_MODE_UNCACHED = -1;
constexpr int32_t CC_MODE_QUERY_FAILED = -2;

struct CcModeCacheEntry {
    int32_t mode{CC_MODE_UNCACHED}; // Cached CC mode. CC_MODE_UNCACHED means no successful query result is cached.
    bool ccLogReported{false};      // Indicates whether the CC-enabled INFO log has been reported for this device.
    bool failureLogReported{false}; // Indicates whether the query-failure or unknown-mode WARN log has been reported.
};

struct CcModeCache {
    std::mutex mutex;
    std::map<int32_t, CcModeCacheEntry> entries;

    bool TryGetCachedMode(const int32_t deviceId, int32_t& mode)
    {
        std::lock_guard<std::mutex> lock(mutex);
        const auto iter = entries.find(deviceId);
        if (iter == entries.end()) {
            return false;
        }
        mode = iter->second.mode;
        return mode != CC_MODE_UNCACHED;
    }

    void SetCachedMode(const int32_t deviceId, const int32_t mode)
    {
        std::lock_guard<std::mutex> lock(mutex);
        entries[deviceId].mode = mode;
    }

    bool MarkCcLogReported(const int32_t deviceId)
    {
        std::lock_guard<std::mutex> lock(mutex);
        return std::exchange(entries[deviceId].ccLogReported, true) == false;
    }

    bool MarkFailureLogReported(const int32_t deviceId)
    {
        std::lock_guard<std::mutex> lock(mutex);
        return std::exchange(entries[deviceId].failureLogReported, true) == false;
    }

    void Reset()
    {
        std::lock_guard<std::mutex> lock(mutex);
        entries.clear();
    }
};

inline CcModeCache& GetCcModeCache()
{
    static CcModeCache ccModeCache;
    return ccModeCache;
}

inline bool GetCurrentDeviceId(int32_t& deviceId) { return rtGetDevice(&deviceId) == 0; }

inline void LogCcQueryFailureOnce(const int32_t deviceId, const bool queryFailed, const int32_t mode = 0)
{
    CcModeCache& cache = GetCcModeCache();
    if (!cache.MarkFailureLogReported(deviceId)) {
        return;
    }
    if (queryFailed) {
        IDE_LOGW(
            "[Adump][CC] Query confidential computing mode failed on device %d, fail-open and keep dump enabled.",
            deviceId);
    } else {
        IDE_LOGW(
            "[Adump][CC] Query confidential computing mode returned an unknown value on device %d, mode=%d, "
            "fail-open and keep dump enabled.",
            deviceId, mode);
    }
}

inline bool IsDeterministicCcQueryFailure(const rtError_t error)
{
    return (error == ACL_ERROR_RT_FEATURE_NOT_SUPPORT) || (error == ACL_ERROR_RT_PARAM_INVALID) ||
           (error == ACL_ERROR_RT_INVALID_DEVICEID);
}

inline bool IsCcMode(const int32_t deviceId)
{
    if (deviceId < 0) {
        return false;
    }
#if !defined(_WIN32) && !defined(_WIN64) && !defined(_MSC_VER)
    CcModeCache& cache = GetCcModeCache();
    int32_t cachedMode = CC_MODE_UNCACHED;
    if (cache.TryGetCachedMode(deviceId, cachedMode)) {
        return (cachedMode == static_cast<int32_t>(HAL_CC_MODE_NORMAL)) ||
               (cachedMode == static_cast<int32_t>(HAL_CC_MODE_ADDITIONAL));
    }

    int32_t mode = 0;
    const rtError_t queryRet = rtDeviceGetCcMode(deviceId, &mode);
    if (queryRet != RT_ERROR_NONE) {
        LogCcQueryFailureOnce(deviceId, true);
        if (IsDeterministicCcQueryFailure(queryRet)) {
            cache.SetCachedMode(deviceId, CC_MODE_QUERY_FAILED);
        }
        return false;
    }

    const bool isCcMode =
        (mode == static_cast<int32_t>(HAL_CC_MODE_NORMAL)) || (mode == static_cast<int32_t>(HAL_CC_MODE_ADDITIONAL));
    if (!isCcMode && (mode != static_cast<int32_t>(HAL_CC_MODE_OFF))) {
        LogCcQueryFailureOnce(deviceId, false, mode);
    }

    // Cache all successful query results. Modes outside OFF/NORMAL/ADDITIONAL are treated as non-CC.
    // Deterministic query failures are also cached as non-CC; transient failures are retried later.
    cache.SetCachedMode(deviceId, mode);
    if (isCcMode) {
        if (cache.MarkCcLogReported(deviceId)) {
            IDE_RUN_LOGI(
                "[Adump][CC] Confidential computing mode is enabled on device %d (mode=%d). Adump data output is "
                "disabled.",
                deviceId, mode);
        }
    }
    return isCcMode;
#else
    (void)deviceId;
    return false;
#endif
}

inline bool IsCurrentDeviceCcMode()
{
    int32_t deviceId = -1;
    if (!GetCurrentDeviceId(deviceId)) {
        static std::atomic<bool> noDeviceLogReported{false};
        const bool needLog = !noDeviceLogReported.exchange(true, std::memory_order_relaxed);
        if (needLog) {
            IDE_LOGW("[Adump][CC] Current logical device is unavailable, fail-open and keep dump enabled.");
        }
        return false;
    }
    return IsCcMode(deviceId);
}

#if defined(__ADUMP_LLT) || defined(__IDE_UT)
inline void ResetCcModeCacheForUt() { GetCcModeCache().Reset(); }
#endif
} // namespace Adx
#endif // ADUMP_COMMON_ADUMP_CC_MODE_H
