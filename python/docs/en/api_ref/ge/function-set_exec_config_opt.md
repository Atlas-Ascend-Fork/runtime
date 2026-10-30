# Function: set\_exec\_config\_opt

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

Sets the value of each attribute of the configuration object executed by the model.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlSetExecConfigOpt(aclmdlExecConfigHandle *handle, aclmdlExecConfigAttr attr, const void *attrValue, size_t valueSize)
    ```

- **Python Function**

    ```python
    ret = acl.mdl.set_exec_config_opt(handle, attr, attrValue)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| handle | Int, pointer address of the configuration object executed by the model. Call [acl.mdl.create_exec_config_handle](function-create_exec_config_handle.md) to create the pointer address in advance.|
| attr | Int, attribute to be set. For details, see [aclmdlExecConfigAttr](aclmdlExecConfigAttr.md).|
| attrValue | Int, value corresponding to `attr`.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Constraints

This API must be used together with other APIs to implement model execution. The API call sequence is as follows:

1. Call [acl.mdl.create_exec_config_handle](function-create_exec_config_handle.md) to create a configuration object for model execution.
2. Call [acl.mdl.set\_exec\_config\_opt](function-set_exec_config_opt.md) multiple times to set the value of each attribute in the configuration object.
3. Call [acl.mdl.execute\_v2](function-execute_v2.md) to specify the configuration information required for model execution, and execute the model.
4. Call [acl.mdl.destroy\_exec\_config\_handle](function-destroy_exec_config_handle.md) to destroy the configuration object after the model is successfully loaded.
