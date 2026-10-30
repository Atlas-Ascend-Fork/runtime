# Function: kernel\_args\_append

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

Appends and copies a user-defined parameter value to the parameter data area to which `argsHandle` points. If there are multiple parameters in the parameter list, append the parameters in sequence.

To update the parameter values, call [acl.rt.kernel\_args\_para\_update](function-kernel_args_para_update.md).

## Prototype

- **C Prototype**

    ```c
    aclError aclrtKernelArgsAppend(aclrtArgsHandle argsHandle, void *param, size_t paramSize, aclrtParamHandle *paramHandle)
    ```

- **Python Function**

    ```python
    param_handle, ret = acl.rt.kernel_args_append(args_handle, param, param_size)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| args_handle | Int, handle of the parameter list.|
| param | Int, memory address of the parameter value to be appended. This is a host memory address.|
| param_size | Int, memory size, in bytes.|

## Return Values

| Return Value| Description|
| --- | --- |
| param_handle | Int, parameter handle.|
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
