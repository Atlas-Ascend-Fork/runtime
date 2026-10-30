# Function: destroy\_exec\_config\_handle

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

Destroys data of the `aclmdlExecConfigHandle` type created by the [acl.mdl.create\_exec\_config\_handle](function-create_exec_config_handle.md) call.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlDestroyExecConfigHandle(const aclmdlExecConfigHandle *handle)
    ```

- **Python Function**

    ```python
    ret = acl.mdl.destroy_exec_config_handle(handle)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| handle | Int, pointer address of the `aclmdlExecConfigHandle` data type to be destroyed.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|
