# Function: launch\_kernel

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

Starts the computation task of a kernel. Only Ascend C custom operators are supported.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtLaunchKernel(aclrtFuncHandle funcHandle, uint32_t numBlocks, const void *argsData, size_t argsSize, aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret = acl.rt.launch_kernel(func_handle, num_blocks, args_data, args_size, stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| func_handle | int, func_handle obtained by calling [acl.rt.binary_get_function](function-binary_get_function.md) based on kernel_name.|
| num_blocks | Int, number of cores on which the kernel function will be executed.|
| args_data | Int, pointer to the memory address of the device that stores all input parameters of the kernel. For details about the memory allocation API, see [Memory Management](../memory/memory_management.md).|
| args_size | Int, size of the `args_data` parameter, in bytes.|
| stream | Int, stream for executing a task, which can be a created stream for saving resources or newly created by calling [acl.rt.create_stream](../stream/function-create_stream.md).|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

This API is asynchronous. A successful call indicates only that the task has been delivered, not that it has completed. After calling this API, call a synchronization API (for example, [acl.rt.synchronize\_stream](../stream/function-synchronize_stream.md)) to ensure that the task is complete.
