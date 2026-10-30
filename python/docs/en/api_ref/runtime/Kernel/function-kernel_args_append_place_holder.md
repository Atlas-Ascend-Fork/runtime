# Function: kernel\_args\_append\_place\_holder

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

For the placeholder parameter, this API is called to reserve a placeholder, and the `param_handle` placeholder is returned.

If there are multiple parameters in the parameter list, append the parameters in sequence. After all parameters are appended, you can call [acl.rt.kernel\_args\_get\_place\_holder\_buffer](function-kernel_args_get_place_holder_buffer.md) to obtain the memory address to which the `param_handle` placeholder points.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtKernelArgsAppendPlaceHolder(aclrtArgsHandle argsHandle, aclrtParamHandle *paramHandle)
    ```

- **Python Function**

    ```python
    param_handle, ret = acl.rt.kernel_args_append_place_holder(args_handle)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| args_handle | Int, handle of the parameter list.|

## Return Values

| Return Value| Description|
| --- | --- |
| param_handle | Int, parameter handle.|
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
