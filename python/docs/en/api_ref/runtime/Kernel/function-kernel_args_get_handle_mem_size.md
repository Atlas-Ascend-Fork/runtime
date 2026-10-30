# Function: kernel\_args\_get\_handle\_mem\_size

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

Obtains the memory size occupied by the parameter list handle.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtKernelArgsGetHandleMemSize(aclrtFuncHandle funcHandle, size_t *memSize)
    ```

- **Python Function**

    ```python
    mem_size, ret = acl.rt.kernel_args_get_handle_mem_size(func_handle)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| func_handle | Int, kernel function handle.<br>Call [acl.rt.binary_get_function](function-binary_get_function.md) to obtain the kernel function handle, and then pass the handle to this API as an argument.|

## Return Values

| Return Value| Description|
| --- | --- |
| mem_size | Int, memory size (in bytes) occupied by the parameter list handle.|
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
