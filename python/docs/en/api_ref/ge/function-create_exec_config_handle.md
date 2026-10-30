# Function: create\_exec\_config\_handle

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

Creates data of the `aclmdlExecConfigHandle` type, indicating the pointer address of the configuration object executed by the model.

To destroy data of the `aclmdlExecConfigHandle` type, see [Function: destroy\_exec\_config\_handle](function-destroy_exec_config_handle.md).

## Prototype

- **C Prototype**

    ```c
    aclmdlExecConfigHandle *aclmdlCreateExecConfigHandle()
    ```

- **Python Function**

    ```python
    handle = acl.mdl.create_exec_config_handle()
    ```

## Parameters

None

## Return Values

| Return Value| Description|
| --- | --- |
| handle | Int, pointer address of the `aclmdlExecConfigHandle` type.<br> If a non-zero value is returned, the operation is successful.<br> If `0` is returned, the operation fails.|
