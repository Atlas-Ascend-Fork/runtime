# Function: set\_kernel\_args

## Applicable Products

<!-- npu="950" id1 -->
- Ascend 950PR&950DT products: Not supported
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

Sets tiling arguments and number of concurrency times of a dynamic-shape operator.

## Prototype

- **C Prototype**

    ```c
    aclError aclopSetKernelArgs(aclopKernelDesc *kernelDesc,
    const char *kernelId,
    uint32_t blockDim,
    const void *args,
    uint32_t argSize)
    ```

- **Python Function**

    ```python
    ret = acl.op.set_kernel_args(kernel_desc, kernel_id, block_dim, args, arg_size)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| kernel_desc | Int, kernel description buffer, pointer address of the `aclopKernelDesc` type.|
| kernel_id | Str, kernel ID. It must be the same as that passed to the `acl.op.create.kernel` call.|
| block_dim | Int, number of blocks for kernel concurrent execution.|
| args | Int, tiling parameter. Use the NumPy array `tobytes` to obtain the bytes object, and then call `acl.utils.bytes_to_ptr()` to obtain the tiling parameter pointer address.|
| arg_size | Int, memory size of the tiling parameter, in bytes. It is the object length of bytes converted from `numpy.tobytes()` and can be obtained by using the `len` function.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|
