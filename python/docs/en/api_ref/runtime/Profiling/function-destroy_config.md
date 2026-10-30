# Function: destroy\_config

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

Destroys data of the aclprofConfig type created by calling [acl.prof.create\_config](function-create_config.md).

## Prototype

- **C Prototype**

    ```c
    aclError aclprofDestroyConfig(const aclprofConfig *profilerConfig)
    ```

- **Python Function**

    ```python
    ret = acl.prof.destroy_config(profiler_config)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| profiler_config | Int, pointer address of the `aclprofConfig` type to be destroyed.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br>`0`: success<br>If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- This API is used in pair with [acl.prof.create_config](function-create_config.md). Call `acl.prof.create_config` before `aclprofDestroyConfig`.
- If the same `aclprofConfig` data repeatedly calls the `acl.prof.destroy_config` API, an error indicating repeated memory release will be reported.
