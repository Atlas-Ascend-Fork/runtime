# Function: start

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

Starts profile data collection.

You can call [acl.prof.start](function-start.md) as required during model execution. The data collected by profiling is the data generated after this API is called.

## Prototype

- **C Prototype**

    ```c
    aclError aclprofStart(const aclprofConfig *profilerConfig)
    ```

- **Python Function**

    ```python
    ret = acl.prof.start(profiler_config)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| profiler_config | Int, profiling configuration.<br>Call the [acl.prof.create_config](function-create_config.md) API to create data of the aclprofConfig type in advance.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br>`0`: success<br>If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

This API is used in pair with [acl.prof.stop](function-stop.md). Call acl.prof.start before acl.prof.stop.
