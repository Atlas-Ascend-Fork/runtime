/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 * This program is free software, you can redistribute it and/or modify it under the terms and conditions of
 * CANN Open Software License Agreement Version 2.0 (the "License").
 * Please refer to the License for details. You may not use this file except in compliance with the License.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 * See LICENSE in the root of the software repository for the full text of the License.
 */

#ifndef AICPU_BUSY_STATE_H
#define AICPU_BUSY_STATE_H

#include "aicpu_context.h"

namespace aicpu {
/**
 * Update the busy state of an AICPU scheduler worker.
 * @param [in]coreIndex: Scheduler worker index, in the range [0, AicpuMaxCpuCnt()).
 *                      This index is not a physical CPU identifier and must be less than 64.
 * @param [in]busy: true to mark the worker busy; false to mark it idle.
 * @return AICPU_ERROR_NONE on success; AICPU_ERROR_FAILED if the index is invalid or accounting is uninitialized.
 * @note InitTaskMonitorContext must complete before workers start processing events.
 *       Each index must be owned by a single worker. Updates to different indices may run concurrently.
 *       Repeated updates to the same state are idempotent; nested busy scopes for one index are not supported.
 */
status_t SetCoreBusyState(uint32_t coreIndex, bool busy);
} // namespace aicpu

// Dynamic entry points exported by libaicpu_sharder.so.
extern "C" {
/**
 * Set the number of AICPU workers reserved by a component.
 * @param [in]type: Component identifier, in the range [0, 16). Each component must use a unique identifier.
 * @param [in]reservedCnt: Number of workers to reserve, in the range [0, AicpuMaxCpuCnt()].
 *                        A value of zero clears the reservation for this component.
 * @return None.
 * @note InitTaskMonitorContext must complete successfully before this interface is called.
 *       Calls made before initialization or with invalid parameters are ignored without changing reservations.
 *       Repeated calls with the same type replace the previous reservation. The effective reservation is the
 *       maximum across all components, with a minimum of one worker. Concurrent calls are supported.
 */
void __attribute__((visibility("default"))) AicpuSetReservedCpuCnt(uint8_t type, uint32_t reservedCnt);

/**
 * Get the effective number of reserved AICPU workers.
 * @return Maximum reservation across all components, with a minimum of one worker after initialization.
 *         Returns zero if InitTaskMonitorContext has not completed successfully.
 * @note Concurrent reservation updates are supported. The returned value is a snapshot and may change
 *       immediately after this call returns.
 */
uint32_t __attribute__((visibility("default"))) AicpuGetReservedCpuCnt();

/**
 * Get the total number of AICPU workers configured for task monitoring.
 * @return Worker count configured by InitTaskMonitorContext.
 *         Returns zero if InitTaskMonitorContext has not completed successfully.
 * @note The count represents scheduler workers, rather than the number of physical CPUs in the system.
 *       Successful initialization clears all component reservations and restores the default reservation of one.
 *       Initialization must complete before workers start processing events. Reinitialization must not run
 *       concurrently with event processing or calls to the CPU accounting interfaces.
 */
uint32_t __attribute__((visibility("default"))) AicpuMaxCpuCnt();

/**
 * Get the current number of idle AICPU workers.
 * @return Total worker count minus the number of workers marked busy, in the range [0, AicpuMaxCpuCnt()].
 *         Returns zero if InitTaskMonitorContext has not completed successfully.
 *         Returns zero if the configured worker count exceeds the 64-worker busy-state bitmap capacity.
 * @note A worker is marked busy after receiving an event and becomes idle when event handling exits.
 *       The returned count does not subtract the effective reservation. For work requiring one worker,
 *       callers may use AicpuGetIdleCpuCnt() > AicpuGetReservedCpuCnt() as a submission condition.
 *       This interface supports concurrent busy-state updates. It returns a snapshot and does not reserve
 *       workers or guarantee capacity for subsequent submissions. Separate getter calls are not an atomic
 *       snapshot of both idle and reserved counts.
 */
uint32_t __attribute__((visibility("default"))) AicpuGetIdleCpuCnt();

} // extern "C"

#endif // AICPU_BUSY_STATE_H
