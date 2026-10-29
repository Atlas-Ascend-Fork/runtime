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
#include "rt_kernel_dsa_update.h"
#include <unordered_map>
#include <tuple>
#include <cinttypes>
#include <string>
#include "securec.h"
#include "rt_aicpu_kernel_base.h"

namespace RT_AICPU_KERNEL {

constexpr uint32_t MASK_32_BIT = 0xFFFFFFFFU;
constexpr uint32_t UINT32_BIT_NUM = 32U;
constexpr uint32_t VAL_TRUNCATED_NORMAL_DIS = 0b011;
constexpr uint32_t VLD_NORMAL_DIS = 0b11000;
constexpr uint32_t VLD_DROPOUT_BITMASK = 0b00001U;
constexpr uint32_t VLD_UNIFORM_DISTRIBUTIO = 0b00110U;
constexpr uint32_t RANDOM_SINGLE_PARAM_MAX_SIZE = 8U;
constexpr uint32_t RANDOM_INPUT_PARAM_SIZE = 16U;
constexpr uint32_t RANDOM_DROPOUT_RATION_INDEX = 0U;
constexpr uint32_t RANDOM_MIN_INDEX = 1U;
constexpr uint32_t RANDOM_MAX_INDEX = 2U;
constexpr uint32_t RANDOM_MEAN_INDEX = 3U;
constexpr uint32_t RANDOM_STDDEV_INDEX = 4U;
constexpr uint32_t RANDOM_SEED_INDEX = 5U;
constexpr uint32_t RANDOM_NUM_INDEX = 6U;

constexpr uint32_t ACL_FLOAT = 0;
constexpr uint32_t ACL_FLOAT16 = 1;
constexpr uint32_t ACL_INT32 = 3;
constexpr uint32_t ACL_UINT32 = 8;
constexpr uint32_t ACL_INT64 = 9;
constexpr uint32_t ACL_UINT64 = 10;
constexpr uint32_t ACL_BF16 = 27;

const std::unordered_map<int32_t, std::pair<RandomNumDataType, size_t>> ACL_DTYPE_2_DSA_DTYPE_MAP = {
    {ACL_INT32, {RT_RANDOM_NUM_DATATYPE_INT32, sizeof(int32_t)}},
    {ACL_INT64, {RT_RANDOM_NUM_DATATYPE_INT64, sizeof(int64_t)}},
    {ACL_UINT32, {RT_RANDOM_NUM_DATATYPE_UINT32, sizeof(uint32_t)}},
    {ACL_UINT64, {RT_RANDOM_NUM_DATATYPE_UINT64, sizeof(uint64_t)}},
    {ACL_BF16, {RT_RANDOM_NUM_DATATYPE_BF16, 2U}},
    {ACL_FLOAT16, {RT_RANDOM_NUM_DATATYPE_FP16, 2U}},
    {ACL_FLOAT, {RT_RANDOM_NUM_DATATYPE_FP32, 4U}}};

static inline uint32_t GetRandomNumDataTypeAndSize(int32_t data_type, RandomNumDataType& dsa_dtype, size_t& data_size)
{
    const auto iter = ACL_DTYPE_2_DSA_DTYPE_MAP.find(data_type);
    if (iter != ACL_DTYPE_2_DSA_DTYPE_MAP.end()) {
        dsa_dtype = iter->second.first;
        data_size = iter->second.second;
    } else {
        KERNEL_LOG_ERROR("dataType[%d] is invalid", data_type);
        return RT_AICPU_KERNEL_E_PARA;
    }

    return RT_AICPU_KERNEL_SUCCESS;
}

static uint32_t CheckRandomParam(const RandomParaInfo& param_info, const std::string paramName, size_t data_size)
{
    if ((param_info.is_addr != 0U) && (param_info.is_addr != 1U)) { // 0: value 1: addr
        KERNEL_LOG_ERROR("%s is_addr para is invalid, range=[0,1]", paramName.c_str());
        return RT_AICPU_KERNEL_E_PARA;
    }

    if ((param_info.size == 0U) || (param_info.size > data_size)) {
        KERNEL_LOG_ERROR(
            "%s size is exceed, current size=%hhu, range=[1,%zu]", paramName.c_str(), param_info.size, data_size);
        return RT_AICPU_KERNEL_E_PARA;
    }

    return RT_AICPU_KERNEL_SUCCESS;
}

static uint32_t CheckUniDisTaskInfo(
    const RandomNumTaskInfo* task_info, RandomNumDataType dsa_dtype, const size_t data_size)
{
    (void)dsa_dtype;
    const UniformDisInfo uni_dis_param = task_info->random_num_func_para_info.param_info.uniform_dis_info;
    const RandomParaInfo min = uni_dis_param.min;
    size_t real_data_size = min.is_addr ? sizeof(uint64_t) : data_size;
    uint32_t error = CheckRandomParam(min, "min", real_data_size);
    COND_RETURN_ERROR_MSG(
        error != RT_AICPU_KERNEL_SUCCESS, error, "min check error info: dataType=%d, dataSize=%zu, isAddr=%hhu",
        task_info->data_type, data_size, min.is_addr);

    const RandomParaInfo max = uni_dis_param.max;
    real_data_size = max.is_addr ? sizeof(uint64_t) : data_size;
    error = CheckRandomParam(max, "max", real_data_size);
    COND_RETURN_ERROR_MSG(
        error != RT_AICPU_KERNEL_SUCCESS, error, "max check error info: dataType=%d, dataSize=%zu, isAddr=%hhu",
        task_info->data_type, data_size, max.is_addr);

    return RT_AICPU_KERNEL_SUCCESS;
}

static uint32_t CheckoutDropoutBitmaskTaskInfo(
    const RandomNumTaskInfo* task_info, RandomNumDataType dsa_dtype, const size_t data_size)
{
    if (dsa_dtype != RT_RANDOM_NUM_DATATYPE_BF16 && dsa_dtype != RT_RANDOM_NUM_DATATYPE_FP16 &&
        dsa_dtype != RT_RANDOM_NUM_DATATYPE_FP32) {
        KERNEL_LOG_ERROR("Datatype(%d) is not supported by Dropout bitmask", task_info->data_type);
        return RT_AICPU_KERNEL_E_PARA;
    }
    const DropoutBitMaskInfo dropout_bitmap_para = task_info->random_num_func_para_info.param_info.dropout_bitmap_info;
    const RandomParaInfo ration = dropout_bitmap_para.dropout_ration;

    const size_t real_data_size = ration.is_addr ? sizeof(uint64_t) : data_size;
    uint32_t error = CheckRandomParam(ration, "dropoutRation", real_data_size);
    COND_RETURN_ERROR_MSG(
        error != RT_AICPU_KERNEL_SUCCESS, error,
        "dropoutRation check error info:dataType=%d, dataSize=%zu, isAddr=%hhu", task_info->data_type, data_size,
        ration.is_addr);

    return error;
}

static uint32_t CheckNorDisTaskInfo(
    const RandomNumTaskInfo* task_info, RandomNumDataType dsa_dtype, const size_t data_size)
{
    if (dsa_dtype != RT_RANDOM_NUM_DATATYPE_BF16 && dsa_dtype != RT_RANDOM_NUM_DATATYPE_FP16 &&
        dsa_dtype != RT_RANDOM_NUM_DATATYPE_FP32) {
        KERNEL_LOG_ERROR(
            "Datatype(%d) is not supported by Normal(Truncated normal) distribution", task_info->data_type);
        return RT_AICPU_KERNEL_E_PARA;
    }
    const NormalDisInfo nor_dis_param = task_info->random_num_func_para_info.param_info.normal_dis_info;
    const RandomParaInfo mean = nor_dis_param.mean;
    size_t real_data_size = mean.is_addr ? sizeof(uint64_t) : data_size;
    uint32_t error = CheckRandomParam(mean, "mean", real_data_size);
    COND_RETURN_ERROR_MSG(
        error != RT_AICPU_KERNEL_SUCCESS, error, "mean check error info: dataType=%d, dataSize=%zu, isAddr=%hhu",
        task_info->data_type, data_size, mean.is_addr);

    const RandomParaInfo stddev = nor_dis_param.stddev;
    real_data_size = stddev.is_addr ? sizeof(uint64_t) : data_size;
    error = CheckRandomParam(stddev, "stddev", real_data_size);
    COND_RETURN_ERROR_MSG(
        error != RT_AICPU_KERNEL_SUCCESS, error, "stddev check error info: dataType=%d, data_size=%zu, isAddr=%hhu",
        task_info->data_type, data_size, stddev.is_addr);

    return error;
}

static uint32_t SetDropoutBitmaskDiffSqeInfo(
    const RandomNumTaskInfo* task_info, StarsDsaSqe* sqe, RandomParamCfgInfo* random_param)
{
    const DropoutBitMaskInfo para_info = task_info->random_num_func_para_info.param_info.dropout_bitmap_info;
    sqe->param_vld_bitmap = VLD_DROPOUT_BITMASK;
    if (!para_info.dropout_ration.is_addr) {
        sqe->param_addr_val_bitmap |= (1U << RANDOM_DROPOUT_RATION_INDEX);
        KERNEL_LOG_INFO("dropoutRationIsAddr is false, paramAddrValBitmap=%u", sqe->param_addr_val_bitmap);
    }

    const auto rc = memcpy_s(
        RtPtrToPtr<void*>(&random_param->first_param), RANDOM_SINGLE_PARAM_MAX_SIZE,
        RtPtrToPtr<const void*>(para_info.dropout_ration.value_or_addr), para_info.dropout_ration.size);
    COND_RETURN_ERROR_MSG(
        rc != EOK, RT_AICPU_KERNEL_E_INTERNAL, "Memcpy_s failed, retCode=%d, size=%hhu", rc,
        para_info.dropout_ration.size);

    return RT_AICPU_KERNEL_SUCCESS;
}

static uint32_t SetUniDisDiffSqeInfo(
    const RandomNumTaskInfo* task_info, StarsDsaSqe* sqe, RandomParamCfgInfo* random_param)
{
    const UniformDisInfo para_info = task_info->random_num_func_para_info.param_info.uniform_dis_info;
    sqe->param_vld_bitmap = VLD_UNIFORM_DISTRIBUTIO;
    if (!para_info.min.is_addr) {
        sqe->param_addr_val_bitmap |= (1U << RANDOM_MIN_INDEX);
        KERNEL_LOG_INFO("minIsAddr is false, paramAddrValBitmap=%u", sqe->param_addr_val_bitmap);
    }

    if (!para_info.max.is_addr) {
        sqe->param_addr_val_bitmap |= (1U << RANDOM_MAX_INDEX);
        KERNEL_LOG_INFO("maxIsAddr is false, paramAddrValBitmap=%u", sqe->param_addr_val_bitmap);
    }

    auto rc = memcpy_s(
        RtPtrToPtr<void*>(&random_param->first_param), RANDOM_SINGLE_PARAM_MAX_SIZE,
        RtPtrToPtr<const void*>(para_info.min.value_or_addr), para_info.min.size);
    COND_RETURN_ERROR_MSG(
        rc != EOK, RT_AICPU_KERNEL_E_INTERNAL, "Memcpy_s failed, retCode=%d, size=%hhu", rc, para_info.min.size);
    KERNEL_LOG_INFO("min val=0x%llx, size=%hhu", random_param->first_param, para_info.min.size);

    rc = memcpy_s(
        RtPtrToPtr<void*>(&random_param->second_param), RANDOM_SINGLE_PARAM_MAX_SIZE,
        RtPtrToPtr<const void*>(para_info.max.value_or_addr), para_info.max.size);
    COND_RETURN_ERROR_MSG(
        rc != EOK, RT_AICPU_KERNEL_E_INTERNAL, "Memcpy_s failed, retCode=%d, size=%hhu", rc, para_info.max.size);
    KERNEL_LOG_INFO("max val=0x%llx, size=%hhu", random_param->second_param, para_info.max.size);

    return RT_AICPU_KERNEL_SUCCESS;
}

static uint32_t SetNorDisDiffSqeInfo(
    const RandomNumTaskInfo* task_info, StarsDsaSqe* sqe, RandomParamCfgInfo* random_param)
{
    const RandomNumFuncType func_type = task_info->random_num_func_para_info.func_type;
    sqe->param_vld_bitmap =
        (func_type == RT_RANDOM_NUM_FUNC_TYPE_NORMAL_DIS) ? VLD_NORMAL_DIS : VAL_TRUNCATED_NORMAL_DIS;

    const NormalDisInfo para_info = task_info->random_num_func_para_info.param_info.normal_dis_info;

    if (!para_info.mean.is_addr) {
        sqe->param_addr_val_bitmap |= (1U << RANDOM_MEAN_INDEX);
        KERNEL_LOG_INFO("meanIsAddr is false, paramAddrValBitmap=%u", sqe->param_addr_val_bitmap);
    }

    if (!para_info.stddev.is_addr) {
        sqe->param_addr_val_bitmap |= (1U << RANDOM_STDDEV_INDEX);
        KERNEL_LOG_INFO("stddevIsAddr is false, paramAddrValBitmap=%u", sqe->param_addr_val_bitmap);
    }
    auto rc = memcpy_s(
        RtPtrToPtr<void*>(&random_param->first_param), RANDOM_SINGLE_PARAM_MAX_SIZE,
        RtPtrToPtr<const void*>(para_info.mean.value_or_addr), para_info.mean.size);
    COND_RETURN_ERROR_MSG(
        rc != EOK, RT_AICPU_KERNEL_E_INTERNAL, "Memcpy_s failed, retCode=%d, size=%hhu", rc, para_info.mean.size);
    KERNEL_LOG_INFO("mean val=0x%llx, size=%hhu", random_param->first_param, para_info.mean.size);

    rc = memcpy_s(
        RtPtrToPtr<void*>(&random_param->second_param), RANDOM_SINGLE_PARAM_MAX_SIZE,
        RtPtrToPtr<const void*>(para_info.stddev.value_or_addr), para_info.stddev.size);
    COND_RETURN_ERROR_MSG(
        rc != EOK, RT_AICPU_KERNEL_E_INTERNAL, "Memcpy_s failed, retCode=%d, size=%hhu", rc, para_info.stddev.size);
    KERNEL_LOG_INFO("stddev val=0x%llx, size=%hhu", random_param->second_param, para_info.stddev.size);

    return RT_AICPU_KERNEL_SUCCESS;
}

static uint32_t SetRandomSqeCommonInfo(
    const RandomNumTaskInfo* const task_info, const RandomNumDataType dtype, StarsDsaSqe* sqe,
    RandomParamCfgInfo* random_param)
{
    sqe->function_type = task_info->random_num_func_para_info.func_type;
    sqe->data_type = static_cast<uint32_t>(dtype);
    if (!task_info->random_seed.is_addr) {
        sqe->param_addr_val_bitmap |= (1U << RANDOM_SEED_INDEX);
        KERNEL_LOG_INFO("seedIsAddr is false, paramAddrValBitmap=%u", sqe->param_addr_val_bitmap);
    }
    if (!task_info->random_num.is_addr) {
        sqe->param_addr_val_bitmap |= (1U << RANDOM_NUM_INDEX);
        KERNEL_LOG_INFO("numIsAddr is false, paramAddrValBitmap=%u", sqe->param_addr_val_bitmap);
    }

    sqe->dsa_cfg_param_addr_low =
        static_cast<uint32_t>(static_cast<uint64_t>(MASK_32_BIT) & RtPtrToPtr<uint64_t>(random_param));
    sqe->dsa_cfg_param_addr_high =
        static_cast<uint32_t>(RtPtrToPtr<uint64_t>(random_param) >> static_cast<uint64_t>(UINT32_BIT_NUM));

    sqe->dsa_cfg_result_addr_low =
        static_cast<uint32_t>(static_cast<uint64_t>(MASK_32_BIT) & RtPtrToPtr<uint64_t>(task_info->random_result_addr));
    sqe->dsa_cfg_result_addr_high = static_cast<uint32_t>(
        RtPtrToPtr<uint64_t>(task_info->random_result_addr) >> static_cast<uint64_t>(UINT32_BIT_NUM));

    sqe->dsa_cfg_state_addr_low = static_cast<uint32_t>(
        static_cast<uint64_t>(MASK_32_BIT) & RtPtrToPtr<uint64_t>(task_info->random_counter_addr));
    sqe->dsa_cfg_state_addr_high = static_cast<uint32_t>(
        RtPtrToPtr<uint64_t>(task_info->random_counter_addr) >> static_cast<uint64_t>(UINT32_BIT_NUM));

    uint64_t random_seed = 0ULL;
    auto rc = memcpy_s(
        &random_seed, sizeof(uint64_t), RtPtrToPtr<const void*>(task_info->random_seed.value_or_addr),
        task_info->random_seed.size);
    COND_RETURN_ERROR_MSG(
        rc != EOK, RT_AICPU_KERNEL_E_INTERNAL, "Memcpy_s failed, retCode=%d, size=%hhu", rc,
        task_info->random_seed.size);
    sqe->dsa_cfg_seed_low = static_cast<uint32_t>(static_cast<uint64_t>(MASK_32_BIT) & random_seed);
    sqe->dsa_cfg_seed_high = static_cast<uint32_t>(random_seed >> static_cast<uint64_t>(UINT32_BIT_NUM));

    uint64_t random_num = 0ULL;
    rc = memcpy_s(
        &random_num, sizeof(uint64_t), RtPtrToPtr<const void*>(task_info->random_num.value_or_addr),
        task_info->random_num.size);
    COND_RETURN_ERROR_MSG(
        rc != EOK, RT_AICPU_KERNEL_E_INTERNAL, "Memcpy_s failed, retCode=%d, size=%hhu", rc,
        task_info->random_num.size);
    sqe->dsa_cfg_number_low = static_cast<uint32_t>(static_cast<uint64_t>(MASK_32_BIT) & random_num);
    sqe->dsa_cfg_number_high = static_cast<uint32_t>(random_num >> static_cast<uint64_t>(UINT32_BIT_NUM));

    return RT_AICPU_KERNEL_SUCCESS;
}

static uint32_t SetRandomSqeDiffInfo(
    const RandomNumTaskInfo* task_info, StarsDsaSqe* sqe, RandomParamCfgInfo* random_param)
{
    uint32_t error = RT_AICPU_KERNEL_SUCCESS;
    switch (task_info->random_num_func_para_info.func_type) {
        case RT_RANDOM_NUM_FUNC_TYPE_DROPOUT_BITMASK:
            error = SetDropoutBitmaskDiffSqeInfo(task_info, sqe, random_param);
            break;
        case RT_RANDOM_NUM_FUNC_TYPE_UNIFORM_DIS:
            error = SetUniDisDiffSqeInfo(task_info, sqe, random_param);
            break;
        case RT_RANDOM_NUM_FUNC_TYPE_NORMAL_DIS:
        case RT_RANDOM_NUM_FUNC_TYPE_TRUNCATED_NORMAL_DIS:
            error = SetNorDisDiffSqeInfo(task_info, sqe, random_param);
            break;
        default:
            error = RT_AICPU_KERNEL_E_NOT_SUPPORT;
            KERNEL_LOG_ERROR(
                "funcType[%u] is invalid, should be [0, %u)", task_info->random_num_func_para_info.func_type,
                RT_RANDOM_NUM_FUNC_TYPE_MAX);
            break;
    }

    return error;
}

static uint32_t CheckRandomNumTaskInfo(const RandomNumTaskInfo* task_info, RandomNumDataType& dsa_dtype)
{
    size_t data_size = 0U;
    uint32_t error = GetRandomNumDataTypeAndSize(task_info->data_type, dsa_dtype, data_size);
    if (error != RT_AICPU_KERNEL_SUCCESS) {
        KERNEL_LOG_ERROR("get random num data size failed, dataType=%d, retCode=%#x", task_info->data_type, error);
        return error;
    }
    if ((task_info->random_counter_addr == nullptr) || (task_info->random_result_addr == nullptr)) {
        KERNEL_LOG_ERROR("randomCounterAddr or randomResultAddr is nullptr");
        return RT_AICPU_KERNEL_E_PARA;
    }

    // 随机种子和随机数个数均为64bit
    const RandomParaInfo seed = task_info->random_seed;
    error = CheckRandomParam(seed, "randomSeed", sizeof(uint64_t));
    if (error != RT_AICPU_KERNEL_SUCCESS) {
        KERNEL_LOG_ERROR("randomSeed check failed, retCode=%#x", static_cast<uint32_t>(error));
        return error;
    }

    const RandomParaInfo num = task_info->random_num;
    error = CheckRandomParam(num, "randomNum", sizeof(uint64_t));
    if (error != RT_AICPU_KERNEL_SUCCESS) {
        KERNEL_LOG_ERROR("randomNum check failed, retCode=%#x", static_cast<uint32_t>(error));
        return error;
    }

    // 通过funcType检查Random param
    switch (task_info->random_num_func_para_info.func_type) {
        case RT_RANDOM_NUM_FUNC_TYPE_DROPOUT_BITMASK:
            error = CheckoutDropoutBitmaskTaskInfo(task_info, dsa_dtype, data_size);
            break;
        case RT_RANDOM_NUM_FUNC_TYPE_UNIFORM_DIS:
            error = CheckUniDisTaskInfo(task_info, dsa_dtype, data_size);
            break;
        case RT_RANDOM_NUM_FUNC_TYPE_NORMAL_DIS:
        case RT_RANDOM_NUM_FUNC_TYPE_TRUNCATED_NORMAL_DIS:
            error = CheckNorDisTaskInfo(task_info, dsa_dtype, data_size);
            break;
        default:
            KERNEL_LOG_ERROR(
                "funcType[%u] is invalid, ", static_cast<uint32_t>(task_info->random_num_func_para_info.func_type));
            error = RT_AICPU_KERNEL_E_NOT_SUPPORT;
            break;
    }
    if (error != RT_AICPU_KERNEL_SUCCESS) {
        KERNEL_LOG_ERROR("check task info by func type failed, retCode=%#x", static_cast<uint32_t>(error));
        return error;
    }
    return error;
}

uint32_t DsaUpdate(void* args)
{
    COND_RETURN_ERROR_MSG(args == nullptr, RT_AICPU_KERNEL_E_PARA, "args is null.");
    auto* tl = RtPtrToPtr<RtAicpuKernelArgs*>(args);
    COND_RETURN_ERROR_MSG(tl == nullptr, RT_AICPU_KERNEL_E_PARA, "RtAicpuKernelArgs reinterpret failed.");
    if (tl->param_length != sizeof(DsaUpdateParam) || tl->kernel_type != RT_AICPU_KERNEL_DSA_UPDATE) {
        KERNEL_LOG_ERROR("kernelType(%u) or paramLength(%u) not correct.", tl->kernel_type, tl->param_length);
        return RT_AICPU_KERNEL_E_PARA;
    }
    // parse DsaUpdateParam
    DsaUpdateParam* param = RtPtrToPtr<DsaUpdateParam*>(static_cast<uint8_t*>(args) + sizeof(RtAicpuKernelArgs));
    COND_RETURN_ERROR_MSG(param == nullptr, RT_AICPU_KERNEL_E_PARA, "DsaUpdateParam reinterpret failed.");
    if (param->task_info == nullptr || param->sqe == nullptr) {
        KERNEL_LOG_ERROR("task_info or sqe in DsaUpdateParam is null.");
        return RT_AICPU_KERNEL_E_PARA;
    }
    // check task_info
    RandomNumTaskInfo* task_info = RtPtrToPtr<RandomNumTaskInfo*>(param->task_info);
    COND_RETURN_ERROR_MSG(task_info == nullptr, RT_AICPU_KERNEL_E_PARA, "RandomNumTaskInfo reinterpret failed.");

    RandomNumDataType dsa_dtype;
    uint32_t ret = CheckRandomNumTaskInfo(task_info, dsa_dtype);
    COND_RETURN_ERROR_MSG(ret != RT_AICPU_KERNEL_SUCCESS, ret, "CheckRandomNumTaskInfo failed.");

    // use task_info->random_para_addr as dsa_cfg_param addr firstly, if task_info->random_para_addr is null then
    // param->dsa_cfg_param.
    void* dsa_cfg_param = task_info->random_para_addr ? task_info->random_para_addr : param->dsa_cfg_param;
    // check dsa_cfg_param addr should be not null.
    COND_RETURN_ERROR_MSG(
        dsa_cfg_param == nullptr, RT_AICPU_KERNEL_E_PARA, "random task config param pointer is null.");

    StarsDsaSqe* sqe = RtPtrToPtr<StarsDsaSqe*>(param->sqe);
    COND_RETURN_ERROR_MSG(sqe == nullptr, RT_AICPU_KERNEL_E_PARA, "StarsDsaSqe reinterpret failed.");
    auto* random_param = RtPtrToPtr<RandomParamCfgInfo*>(dsa_cfg_param);
    COND_RETURN_ERROR_MSG(random_param == nullptr, RT_AICPU_KERNEL_E_PARA, "RandomParamCfgInfo reinterpret failed.");

    // should reset sqe some data segmemnt first, when Dsa update
    sqe->param_addr_val_bitmap = 0U;

    // update sqe info
    ret = SetRandomSqeDiffInfo(task_info, sqe, random_param);
    COND_RETURN_ERROR_MSG(
        ret != RT_AICPU_KERNEL_SUCCESS, ret, "set random task sqe diff info failed, retCode=%#x",
        static_cast<uint32_t>(ret));

    ret = SetRandomSqeCommonInfo(task_info, dsa_dtype, sqe, random_param);
    COND_RETURN_ERROR_MSG(
        ret != RT_AICPU_KERNEL_SUCCESS, ret, "set random task sqe common info failed, retCode=%#x",
        static_cast<uint32_t>(ret));

    KERNEL_LOG_INFO("update random task sqe successful.");
    return ret;
}

} // namespace RT_AICPU_KERNEL
