# Function: kernel\_args\_init\_by\_user\_mem

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

Initializes the parameter list based on the kernel function handle and obtains the handle that identifies the parameter list.

The difference between this API and [acl.rt.kernel\_args\_init](function-kernel_args_init.md) is that this API indicates that the user manages the memory.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtKernelArgsInitByUserMem(aclrtFuncHandle funcHandle, aclrtArgsHandle argsHandle, void *userHostMem, size_t actualArgsSize)
    ```

- **Python Function**

    ```python
    ret = acl.rt.kernel_args_init_by_user_mem(func_handle, args_handle, user_host_mem, actual_args_size)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| func_handle | Int, kernel function handle.<br>Call [acl.rt.binary_get_function](function-binary_get_function.md) to obtain the kernel function handle, and then pass the handle to this API as an argument.|
| args_handle | Int, handle of the parameter list.<br>Call [acl.rt.kernel_args_get_handle_mem_size](function-kernel_args_get_handle_mem_size.md) in advance to obtain the memory size, allocate the host memory, and then pass the host memory address as the input parameter.|
| user_host_mem | Int, host memory address.<br>Call [acl.rt.kernel_args_get_mem_size](function-kernel_args_get_mem_size.md) in advance to obtain the memory size, allocate the host memory, and then pass the host memory address as the input parameter.|
| actual_args_size | Int, memory size.<br>Call [acl.rt.kernel_args_get_mem_size](function-kernel_args_get_mem_size.md) in advance to obtain the memory size, and then pass the memory size as the input parameter.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
