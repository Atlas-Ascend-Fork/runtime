# Function: init

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

Initializes profiling and sets the path for saving profile data files.

## Prototype

- **C Prototype**

    ```c
    aclError aclprofInit(const char *profilerResultPath, size_t length)
    ```

- **Python Function**

    ```python
    ret = acl.prof.init(profiler_result_path)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| profiler_result_path | Str, an absolute path for saving profile data files.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br>`0`: success<br>If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

This API is used in pair with [acl.prof.finalize](function-finalize-Profiling.md). Call aclprofInit before aclprofFinalize.
