# aclrtDeviceLimit

| Data Format| Description|
| --- | --- |
| ACL_RT_DEV_LIMIT_SIMT_STACK_SIZE = 0 | SIMT stack size (per-thread)|
| ACL_RT_DEV_LIMIT_SIMT_DVG_WARP_STACK_SIZE = 1 | SIMT branch stack size (per-warp)|
| ACL_RT_DEV_LIMIT_SIMD_STACK_SIZE = 2 | AI Core stack size (per core)|
| ACL_RT_DEV_LIMIT_SIMD_PRINTF_FIFO_SIZE_PER_CORE = 3 | SIMD printf FIFO size (per core)|
| ACL_RT_DEV_LIMIT_SIMT_PRINTF_FIFO_SIZE = 4 | SIMT printf FIFO size register|

<!-- npu="950" id1 -->
For Ascend 950PR&950DT products, all the preceding options are supported. However, ACL_RT_DEV_LIMIT_SIMT_STACK_SIZE and ACL_RT_DEV_LIMIT_SIMT_DVG_WARP_STACK_SIZE cannot be set to 0 at the same time. Otherwise, ACL_ERROR_RT_PARAM_INVALID is returned.
<!-- end id1 -->

<!-- npu="A3,910b" id2 -->
For Atlas A3 products and Atlas A2 products, only SIMD-related options (for example, ACL_RT_DEV_LIMIT_SIMD_STACK_SIZE) are supported, and SIMT-related options (for example, ACL_RT_DEV_LIMIT_SIMT_STACK_SIZE) are not supported.
<!-- end id2 -->

The enumeration items are described as follows:

- ACL\_RT\_DEV\_LIMIT\_SIMT\_STACK\_SIZE

    Sets the stack size of each thread of the Single Instruction Multiple Thread (SIMT) operator, in bytes. The default value is 1152 bytes.

    If set to the ACL_RT_DEV_LIMIT_SIMT_STACK_SIZE type, the value must be an integer multiple of 128 bytes. If the input value is not an integer multiple of 128 bytes, the API automatically rounds up the value to ensure that it is an integer multiple of 128 bytes. The actual stack size of each thread is ((value rounded up to the nearest multiple of 128) x 32) bytes.

- ACL\_RT\_DEV\_LIMIT\_SIMT\_DVG\_WARP\_STACK\_SIZE

    Sets the divergence stack size of an SIMT operator, in bytes. The default value is 1024 bytes.

    If set to the ACL_RT_DEV_LIMIT_SIMT_DVG_WARP_STACK_SIZE type, the value must be an integer multiple of 128 bytes. If the input value is not an integer multiple of 128 bytes, the API automatically rounds up the value to ensure that it is an integer multiple of 128 bytes.

- ACL\_RT\_DEV\_LIMIT\_SIMD\_STACK\_SIZE

    Sets the size of the stack space allocated to each AI Core during the execution of a Single Instruction Multiple Data (SIMD) operator in a process, in bytes. The default value is 32768 bytes (32 KB).

    For Atlas A3 and Atlas A2 products, if the value is of the ACL_RT_DEV_LIMIT_SIMD_STACK_SIZE type, the value range is (32768, 196608] bytes, that is, (32, 192] KB.

    For Ascend 950PR&950DT products, if the value is of the ACL_RT_DEV_LIMIT_SIMD_STACK_SIZE type, the value range is (32768, 131072] bytes, that is, (32, 128] KB.

    If the value is greater than 32 KB, the API rounds up the value to ensure that the value is an integer multiple of 16 KB. If the value is less than or equal to 32 KB, 32 KB is used by default.

- ACL\_RT\_DEV\_LIMIT\_SIMD\_PRINTF\_FIFO\_SIZE\_PER\_CORE

    Sets the size of the space for an SIMD operator to print information on each core, in bytes. The default value is 32768 bytes (32 KB).

    If set to the ACL_RT_DEV_LIMIT_SIMD_PRINTF_FIFO_SIZE_PER_CORE type, the value must be an integer multiple of 8 bytes. If the input value is not an integer multiple of 8 bytes, the API automatically rounds up the value to ensure that it is an integer multiple of 8 bytes. The value range is [1024, 67108864] bytes, that is, [1 KB, 64 MB].

- ACL\_RT\_DEV\_LIMIT\_SIMT\_PRINTF\_FIFO\_SIZE

    Sets the size of the space for an SIMT operator to print information, in bytes. The default value is 2097152 bytes (2 MB).

    If set to the ACL_RT_DEV_LIMIT_SIMT_PRINTF_FIFO_SIZE type, the value must be an integer multiple of 8 bytes. If the input value is not an integer multiple of 8 bytes, the API automatically rounds up the value to ensure that it is an integer multiple of 8 bytes. The value range is [1048576, 67108864] bytes, that is, [1, 64] MB.
