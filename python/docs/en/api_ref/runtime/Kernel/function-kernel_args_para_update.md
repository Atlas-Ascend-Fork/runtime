# Function: kernel\_args\_para\_update

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

Updates the parameter value appended by [acl.rt.kernel_args_append](function-kernel_args_append.md).

## Prototype

- **C Prototype**

    ```c
    aclError aclrtKernelArgsParaUpdate(aclrtArgsHandle argsHandle, aclrtParamHandle paramHandle, void *param, size_t paramSize)
    ```

- **Python Function**

    ```python
    ret = acl.rt.kernel_args_para_update(args_handle, param_handle, param, param_size)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| args_handle | Int, handle of the parameter list.|
| param_handle | Int, parameter handle.|
| param | Int, memory address of the parameter value to be appended. This is a host memory address.|
| param_size | Int, memory size, in bytes.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
