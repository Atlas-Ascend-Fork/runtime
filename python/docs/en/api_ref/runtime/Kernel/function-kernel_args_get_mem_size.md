# Function: kernel\_args\_get\_mem\_size

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

Obtains the actual memory size required by the parameter list during kernel launch.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtKernelArgsGetMemSize(aclrtFuncHandle funcHandle, size_t userArgsSize, size_t *actualArgsSize)
    ```

- **Python Function**

    ```python
    actual_args_size, ret = acl.rt.kernel_args_get_mem_size(func_handle, user_args_size)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| func_handle | Int, kernel function handle.<br>Call [acl.rt.binary_get_function](function-binary_get_function.md) to obtain the kernel function handle, and then pass the handle to this API as an argument.|
| user_args_size | Int, memory size (in bytes) required for storing the parameter list data.<br>The memory size of each parameter data must be 8-byte aligned. `user_args_size` is the sum of the memory sizes of all aligned parameter data.|

## Return Values

| Return Value| Description|
| --- | --- |
| actual_args_size | Int, actual memory size (in bytes) required by the parameter list during kernel launch.|
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
