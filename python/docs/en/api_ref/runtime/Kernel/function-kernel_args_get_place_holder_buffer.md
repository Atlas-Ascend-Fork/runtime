# Function: kernel\_args\_get\_place\_holder\_buffer

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

Obtains the memory address to which the `param\_handle` placeholder points based on the memory size specified by the user.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtKernelArgsGetPlaceHolderBuffer(aclrtArgsHandle argsHandle, aclrtParamHandle paramHandle, size_t dataSize, void **bufferAddr)
    ```

- **Python Function**

    ```python
    buffer_addr, ret = acl.rt.kernel_args_get_place_holder_buffer(args_handle, param_handle, data_size)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| args_handle | Int, handle of the parameter list.|
| param_handle | Int, parameter handle.<br>The value of param_handle must be the same as that of param_handle in the [acl.rt.kernel_args_append_place_holder](function-kernel_args_append_place_holder.md) call.|
| data_size | Int, memory size.|

## Return Values

| Return Value| Description|
| --- | --- |
| buffer_addr | Int, memory address pointed to by the `param_handle` placeholder.<br>You need to manage the data in the memory, but not the memory lifetime.|
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
