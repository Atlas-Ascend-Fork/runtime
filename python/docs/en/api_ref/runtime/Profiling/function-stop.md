# Function: stop

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

Stops profile data collection.

## Prototype

- **C Prototype**

    ```c
    aclError aclprofStop(const aclprofConfig *profilerConfig)
    ```

- **Python Function**

    ```python
    ret = acl.prof.stop(profiler_config)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| profiler_config | Int, pointer address for stopping Profiling.<br>The value must be the same as the data of the aclprofConfig type in the [acl.prof.start](function-start.md) call.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br>`0`: success<br>If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

This API is used in pair with [acl.prof.start](function-start.md). Call acl.prof.start before acl.prof.stop.
