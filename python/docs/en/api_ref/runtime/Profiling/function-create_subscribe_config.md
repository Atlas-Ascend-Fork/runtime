# Function: create\_subscribe\_config

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

Creates the data of the `aclprofSubscribeConfig` type as a subscription configuration.

To destroy data of the `aclprofSubscribeConfig` type, see [acl.prof.destroy\_subscribe\_config](function-destroy_subscribe_config.md).

## Prototype

- **C Prototype**

    ```c
    aclprofSubscribeConfig *aclprofCreateSubscribeConfig(int8_t timeInfoSwitch, aclprofAicoreMetrics aicoreMetrics, void *fd)
    ```

- **Python Function**

    ```python
    subscribe_config = acl.prof.create_subscribe_config(time_info_switch, aicore_metrics, fd)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| time_info_switch | Int, whether to enable operator profiling in the model.<br>`1`: yes<br>`0`: no|
| aicore_metrics | Int, AI Core performance metrics. For details, see [aclprofAicoreMetrics](../datatypes/aclprofAicoreMetrics.md).<br>This API traces operator call duration only and does not support Profiling of AI Core metrics.|
| fd | Int, write file descriptor of the pipe created by the user.<br>After [acl.prof.model_unsubscribe](function-model_unsubscribe.md) is called, the system closes the pipe write file descriptor of the model after the data is sent.|

## Return Values

| Return Value| Description|
| --- | --- |
| subscribe_config | Int<br>If a non-zero value is returned, the operation is successful. In this case, the address object of `aclprofSubscribeConfig` is returned.<br>If `0` is returned, the operation fails.|

## Constraints

- Call [acl.prof.destroy\_subscribe\_config](function-destroy_subscribe_config.md) to destroy data of the `aclprofSubscribeConfig` type. If the data is not destroyed, the memory will not be freed.

- This API is used in pair with [acl.prof.destroy\_subscribe\_config](function-destroy_subscribe_config.md). Call `acl.prof.create_subscribe_config` before [acl.prof.destroy\_subscribe\_config](function-destroy_subscribe_config.md).
