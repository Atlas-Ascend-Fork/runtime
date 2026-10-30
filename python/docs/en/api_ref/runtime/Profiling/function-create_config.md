# Function: create\_config

## Applicable Products
<!-- npu="950" id1 -->
- Ascend 950PR&950DT products: Supported
<!-- end id1 -->
<!-- npu="A3" id2 -->
- Atlas A3 products: Supported
<!-- end id2 -->
<!-- npu="910b" id3 -->
- Atlas A2 products: Supported
<!-- end id3 -->
<!-- npu="310b" id4 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas inference products: Supported
<!-- end id5 -->
<!-- npu="910" id6 -->
- Atlas training products: Supported
<!-- end id6 -->

## Function

Creates data of the `aclprofConfig` type as a Profiling configuration.

Created `aclProfConfig` data can be reused in multiple calls. You need to ensure the consistency and accuracy of the data.

To destroy data of the `aclprofConfig` type, see [Function: destroy_config](function-destroy_config.md).

## Prototype

- **C Prototype**

    ```c
    aclprofConfig *aclprofCreateConfig(uint32_t *deviceIdlist, uint32_t deviceNums, aclprofAicoreMetrics aicoreMetrics, aclprofAicoreEvents *aicoreEvents, uint64_t dataTypeConfig)
    ```

- **Python Function**

    ```python
    prof_config = acl.prof.create_config(device_list, aicore_metrics, aicore_events, data_type_config)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| device_list | List, device ID list. Set this parameter based on the actual device ID.|
| aicore_metrics | int, indicating [aclprofAicoreMetrics](../datatypes/aclprofAicoreMetrics.md).|
| aicore_events | Int, AI Core event, which is set to `0`.|
| data_type_config | Int, ORed value of multiple [aclproftype](../datatypes/aclproftype.md) values (for example, `ACL_PROF_ACL_API\|ACL_PROF_AICORE_METRICS`) selected by the user, which is used as the value of the `data_type_config` parameter. Each value indicates a type of profile data.<br>`ACL_PROF_ACL_API`: collects API profile data, including synchronous/asynchronous memory copy latency (host-device).<br>`ACL_PROF_TASK_TIME`: collects operator dispatch and execution time, and basic operator information. This level provides comprehensive profile data for in-depth analysis.<br>`ACL_PROF_TASK_TIME_L0`: collects operator dispatch and execution time. Compared with `ACL_PROF_TASK_TIME`, `ACL_PROF_TASK_TIME_L0` omits basic operator information collection, reducing performance overhead and enabling more accurate timing statistics.<br>`ACL_PROF_AICORE_METRICS`: collects AI Core metrics. This value must be included in the logical OR combination; otherwise, metrics specified in `aicore_metrics` will not take effect.<br>`ACL_PROF_TASK_MEMORY`: controls whether to collect CANN operator memory usage. Only data of GE operators is collected.<br>`ACL_PROF_AICPU`: collects the start and end data of AICPU tasks.<br>`ACL_PROF_L2CACHE`: collects L2 Cache data.<br>`ACL_PROF_HCCL_TRACE`: specifies whether to collect communication data.<br>`ACL_PROF_MSPROFTX`: obtains profile data output by the user and upper-layer framework program. In the application script, you need to add one of the following APIs:<br>For details about the mstx API (MindStudio Tools Extension API) operations, see Appendixes > mstx API Usage Examples in [Performance Tuning Tool](https://hiascend.com/en/document/redirect/CannCommunityToolProfiling).<br>[msproftx Extension APIs](msproftx_extension_apis.md).<br>`ACL_PROF_TRAINING_TRACE`: specifies whether to collect iteration traces.<br>`ACL_PROF_RUNTIME_API`: specifies whether to collect runtime API profile data.|

## Return Values

| Return Value| Description|
| --- | --- |
| prof_config | Int<br>If a non-zero value is returned, the operation is successful. The return value is the pointer address of data of the `aclprofConfig` type.<br>If `0` is returned, the operation fails.|

## Constraints

- Call [acl.prof.destroy\_config](function-destroy_config.md) to destroy data of the `aclprofConfig` type. If the data is not destroyed, the memory will not be freed.

- This API is used in pair with [acl.prof.destroy\_config](function-destroy_config.md). Call `acl.prof.create_config` before [acl.prof.destroy\_config](function-destroy_config.md).
