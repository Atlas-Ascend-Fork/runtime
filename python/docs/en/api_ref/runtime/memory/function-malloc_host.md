# Function: malloc\_host

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

Allocates the host memory (lock page memory) if the app is running on the host. The system ensures that the start address of the memory is 64-byte aligned.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtMallocHost(void **hostPtr, size_t size)
    ```

- **Python Function**

    ```python
    host_ptr, ret = acl.rt.malloc_host(size)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| size | Int, allocated memory size, in bytes. Must not be `0`.|

## Return Values

| Return Value| Description|
| --- | --- |
| host_ptr | Int, address of the pointer to the allocated host memory.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- The memory allocated by this API is not initialized. Call [acl.rt.memset](function-memset.md) to initialize the memory and clear random numbers in the memory before using the memory.
- This API does not perform implicit device synchronization or stream synchronization. The memory allocation result, either success or failure, is returned immediately.
- The memory allocated by calling acl.rt.malloc\_host needs to be freed by calling [acl.rt.free\_host](function-free_host.md).
- If acl.rt.malloc\_host is used to allocate too much locked page memory, the physical memory used for paging by the OS will decrease, thereby deteriorating the overall system performance.
- Performance deterioration will be caused by the frequent calling of acl.rt.malloc\_host to allocate memory and [acl.rt.free\_host](function-free_host.md) to free memory. You are advised to allocate or manage memory in advance to avoid frequent memory allocation and deallocation.
<!-- npu="310p" id7 -->
- In Ascend RC mode and open Ctrl CPU mode, the host and device are integrated. Therefore, allocating host memory is equivalent to allocating device memory. In addition, memory is allocated based on normal pages. If the start address needs to be 64-byte aligned, you need to handle the alignment problem by yourself.
<!-- end id7 -->
<!-- npu="310p" id8 -->
- In Ascend RC mode and open Ctrl CPU mode, if you use this API to allocate a large memory block and divide and manage the memory by yourself, each memory segment must meet the following requirements. `len` indicates the size of a memory segment, and `ALIGN\_UP\[len,k\]` indicates rounding up to the nearest multiple of k bytes: \(\(len-1\)/k+1\) x k:
  - The memory size is rounded up to the nearest multiple of 32, plus 32 bytes (m = ALIGN\_UP[len, 32] + 32 bytes).
  - The memory start address must be 64-byte aligned (ALIGN_UP[m, 64]).
<!-- end id8 -->
