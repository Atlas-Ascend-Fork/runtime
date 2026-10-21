/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 * This program is free software, you can redistribute it and/or modify it under the terms and conditions of
 * CANN Open Software License Agreement Version 2.0 (the "License").
 * Please refer to the License for details. You may not use this file except in compliance with the License.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 * See LICENSE in the root of the software repository for the full text of the License.
 */
#ifndef CCE_RUNTIME_CC_TASK_QUEUE_H
#define CCE_RUNTIME_CC_TASK_QUEUE_H

#include <cstdint>
#include <cstddef>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "base.hpp"
#include "rt_external_mem.h"
#include "crypto/cc_crypto.h"

namespace cce {
namespace runtime {

// 本头文件定义两类协作对象：
// 1. 设备侧分片队列（PCIe BAR 空间，Host 与 AICPU 经 ld/st 共享）：CCSliceQueue + CCSliceDesc，
//    Host 分配、AICPU 读写，布局与 AICPU 实现保持一致，成员类型与顺序不可变更。
// 2. Host 侧内存拷贝任务队列（仅 CCManager/CCWorker 内部使用）：CCMemcpyTask + CCMemcpyTaskQueue。

// Device Buffer A/B 双缓冲物理槽位数
constexpr uint32_t CC_BUFFER_SLOT_NUM = 2U;
// 分片队列环形描述槽深度（= 3，牺牲 1 个槽位区分满/空，有效槽位 = 2）
constexpr uint32_t CC_SLICE_DESC_SLOT_NUM = 3U;
// 密文 buffer 大小（header + plaintext）
constexpr uint32_t CC_SLICE_SIZE = 2U * 1024U * 1024U;
// 单分片密文头大小
constexpr uint32_t CC_CIPHER_HEADER_SIZE = static_cast<uint32_t>(sizeof(CCCipherTxtHeader));
// 单分片最大明文字节数
constexpr uint32_t CC_PLAINTEXT_SLICE_SIZE = CC_SLICE_SIZE - CC_CIPHER_HEADER_SIZE;

// 单个分片的任务描述（PCIe BAR 空间，depth = CC_SLICE_DESC_SLOT_NUM，由 AICPU 按序消费）。
struct CCSliceDesc {
    volatile uint64_t ciphertextAddr; // Device Buffer A/B 地址（密文所在物理槽）
    volatile uint64_t plaintextAddr;  // 明文地址
    volatile uint32_t ciphertextLen;  // 密文长度（CC_CIPHER_HEADER_SIZE + plaintextLen）
    volatile uint32_t plaintextLen;   // 明文长度
    volatile uint32_t sliceIdx;       // 分片序号，sliceIdx == totalSlices - 1 时为最后一块
};

// 设备侧分片队列控制头（位于 PCIe BAR 空间，Host 和 AICPU 均可直接 ld/st 访问）。
// Stream 级管理：首次 CC memcpy 时惰性分配，绑定到 Stream；Stream 销毁时释放。
// 环形缓冲区协议（depth = CC_SLICE_DESC_SLOT_NUM，牺牲 1 个槽位区分满/空）：
//   空：head == tail；满：(head + 1) % depth == tail；可写：(head + 1) % depth != tail
struct CCSliceQueue {
    volatile uint32_t totalSlices; // 本次 memcpy 的总分片数，由 worker 写入
    volatile uint8_t head;         // 环形缓冲区发布位置（0→1→2→0）
    volatile uint8_t tail;         // 环形缓冲区消费位置（0→1→2→0）
    volatile uint8_t memWaitVal;   // worker 完成 totalSlices 发布后写 1, 任务执行结束后写0
    volatile uint8_t depth;        // sliceDesc 数组长度，固定为 CC_SLICE_DESC_SLOT_NUM
    uint8_t rsv[4];
    CCSliceDesc sliceDesc[];       // 柔性数组，紧跟在结构体后面

    bool IsEmpty() const { return head == tail; }
    bool IsFull() const { return static_cast<uint8_t>((head + 1U) % depth) == tail; }
    // sliceIdx 连续递增，交替映射到 Device Buffer A/B，保证双缓冲不冲突
    static uint32_t PhysicalBufferIndex(const uint32_t sliceIdx) { return sliceIdx % CC_BUFFER_SLOT_NUM; }
};

// Host 侧内存拷贝任务（CCMemcpyTaskQueue 的节点，由 CCWorker 消费）。
struct CCMemcpyTask {
    const void* src;                // 源地址
    void* dst;                      // 目标地址
    size_t totalSize;               // 总拷贝大小
    rtMemcpyKind_t kind;            // H2D 或 D2H
    uint32_t streamId;              // Worker 通过 StreamSqCqManage 获取 Stream shared_ptr
    std::shared_ptr<void> guardMem; // Memset场景下保活Host侧的临时Buffer
};

// Host 侧任务队列（per-device，1 个共享队列，结构为纯数据 + 内联方法）。
struct CCMemcpyTaskQueue {
    bool Push(const CCMemcpyTask& task)
    {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (closed_) {
                return false;
            }
            queue_.push(task);
        }
        cv_.notify_one();
        return true;
    }

    bool Pop(CCMemcpyTask& task)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [&]() { return !queue_.empty() || closed_; });
        if (queue_.empty()) {
            return false;
        }
        task = queue_.front();
        queue_.pop();
        return true;
    }

    // 关闭队列 + 清空未领取任务 + 唤醒所有 worker 立即退出
    void Shutdown()
    {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            closed_ = true;
            std::queue<CCMemcpyTask> empty;
            queue_.swap(empty);
        }
        cv_.notify_all();
    }

    // 按 streamId 移除尚未被 worker 领取的任务
    void CancelTasksByStream(uint32_t streamId)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        std::queue<CCMemcpyTask> remainingTasks;
        while (!queue_.empty()) {
            const CCMemcpyTask& task = queue_.front();
            if (task.streamId != streamId) {
                remainingTasks.push(task);
            }
            queue_.pop();
        }
        queue_.swap(remainingTasks);
    }

    std::queue<CCMemcpyTask> queue_;
    std::mutex mutex_;
    std::condition_variable cv_;
    bool closed_{false};
};

} // namespace runtime
} // namespace cce

#endif
