/**
 * Copyright (c) Huawei Technologies Co., Ltd. 2025. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef RT_KERNEL_DSA_UPDATE_H
#define RT_KERNEL_DSA_UPDATE_H

#include <vector>
#include <cstdint>
#include <sys/types.h>

namespace RT_AICPU_KERNEL {

struct RandomParaInfo {
    uint8_t is_addr;          // 0:value 1:addr
    uint8_t value_or_addr[8]; // 当is_addr=0, 请根据data_type填充相应字节数，如fp16,bf16填充前2个字节;
                              // fp32,uint32,int32,则填充前4个字节；
                              // uint64,int64,则填充8个字节。当is_addr=1时，则填充8字节的地址值
    uint8_t size;
    uint8_t rsv[6];
};

// dropout bitmask
struct DropoutBitMaskInfo {
    RandomParaInfo dropout_ration;
};

// 均匀分布
struct UniformDisInfo {
    RandomParaInfo min;
    RandomParaInfo max;
};

// 正态分布、截断正态分布
struct NormalDisInfo {
    RandomParaInfo mean;
    RandomParaInfo stddev;
};

enum RandomNumFuncType : uint32_t {
    RT_RANDOM_NUM_FUNC_TYPE_DROPOUT_BITMASK = 0U, // dropout bitmask
    RT_RANDOM_NUM_FUNC_TYPE_UNIFORM_DIS,          // 均匀分布
    RT_RANDOM_NUM_FUNC_TYPE_NORMAL_DIS,           // 正态分布
    RT_RANDOM_NUM_FUNC_TYPE_TRUNCATED_NORMAL_DIS, // 截断正态分布
    RT_RANDOM_NUM_FUNC_TYPE_MAX
};

enum RandomNumDataType : uint32_t {
    RT_RANDOM_NUM_DATATYPE_INT32 = 0U,
    RT_RANDOM_NUM_DATATYPE_INT64,
    RT_RANDOM_NUM_DATATYPE_UINT32,
    RT_RANDOM_NUM_DATATYPE_UINT64,
    RT_RANDOM_NUM_DATATYPE_BF16,
    RT_RANDOM_NUM_DATATYPE_FP16,
    RT_RANDOM_NUM_DATATYPE_FP32,
    RT_RANDOM_NUM_DATATYPE_MAX
};

struct RandomNumFuncParaInfo {
    RandomNumFuncType func_type;
    union {
        DropoutBitMaskInfo dropout_bitmap_info; // for dropout bitmask
        UniformDisInfo uniform_dis_info;        // 均匀分布
        NormalDisInfo normal_dis_info;          // 正态分布、截断正态分布
    } param_info;
};

struct RandomNumTaskInfo {
    int32_t data_type;
    RandomNumFuncParaInfo random_num_func_para_info;
    void* random_para_addr;    // 判断是否为空指针
    void* random_result_addr;  // GE申请内存
    void* random_counter_addr; // GE申请内存
    RandomParaInfo random_seed;
    RandomParaInfo random_num;
    uint8_t rsv[8];
};

#pragma pack(push)
#pragma pack(1)
struct DsaUpdateParam {
    void* task_info;     // pointer to RandomNumTaskInfo sturct
    void* sqe;           // sqe addr
    void* dsa_cfg_param; // pointer to dsa_cfg_param
};

struct StarsDsaSqe {
    // 0-7 bytes
    uint8_t sqe_header[8];
    // 8-11 bytes
    uint32_t start : 1;
    uint32_t function_type : 3;
    uint32_t data_type : 3;
    uint32_t algo_type : 3;
    uint32_t param_vld_bitmap : 5;
    uint32_t param_addr_val_bitmap : 7;
    uint32_t reserved0 : 10;
    // 12-15 bytes
    uint16_t sqe_index;
    uint8_t kernel_credit;
    uint8_t reserved1;
    // 16-31 bytes
    uint32_t dsa_cfg_result_addr_low;
    uint32_t dsa_cfg_result_addr_high;
    uint32_t dsa_cfg_state_addr_low;
    uint32_t dsa_cfg_state_addr_high;
    // 32-47 bytes
    uint32_t dsa_cfg_param_addr_low;
    uint32_t dsa_cfg_param_addr_high;
    uint32_t dsa_cfg_seed_low;
    uint32_t dsa_cfg_seed_high;
    // 48-63 bytes
    uint32_t dsa_cfg_number_low;
    uint32_t dsa_cfg_number_high;
    uint32_t reserved2[2];
};

/*
 * random num task for dsa
 * dropout bitmask  : first_param --> dropout ration;
 * 均匀分布          : first_param --> min; second_param --> max
 * 正态分布          : first_param --> mean; second_param --> stddev
 * 截断正态分布       : first_param --> mean; second_param --> stddev
 */
struct RandomParamCfgInfo {
    uint64_t first_param;
    uint64_t second_param;
};
#pragma pack(pop)

uint32_t DsaUpdate(void* args);

template <typename TO, typename TI>
inline auto RtPtrToPtr(const TI ptr) -> TO
{
    return reinterpret_cast<TO>(ptr);
}
} // namespace RT_AICPU_KERNEL

#endif // RT_KERNEL_DSA_UPDATE_H
