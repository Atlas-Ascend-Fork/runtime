# Function: set\_config

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

Functions as an extended API of [acl.prof.create_config](function-create_config.md) to set profile data collection parameters.

This API can be called multiple times. You need to ensure data consistency and accuracy.

## Prototype

- **C Prototype**

    ```c
    aclError aclprofSetConfig(aclprofConfigType configType, const char *config, size_t configLength)
    ```

- **Python Function**

    ```python
    ret = acl.prof.set_config(config_type, config)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| config_type | Int, value of the `config_type` parameter. Each constant indicates a different collection configuration. To collect multiple types of profile data, you need to call this API multiple times. For details, see [aclprofConfigType](./../datatypes/aclprofConfigType.md).|
| config | Str, configuration parameter value.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br>`0`: success<br>If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

Call acl.prof.set_config and then [acl.prof.start](function-start.md). You can call this API as required.
