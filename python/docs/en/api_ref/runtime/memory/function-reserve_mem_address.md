# Function: reserve\_mem\_address

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

Reserves virtual memory.

**This API needs to work with other APIs** to allocate virtual memory with consecutive addresses and maximize the use of physical memory.

1. Call [acl.rt.reserve\_mem\_address](function-reserve_mem_address.md) to allocate virtual memory.
2. Call [acl.rt.malloc\_physical](function-malloc_physical.md) to allocate physical memory.
3. Call [acl.rt.map\_mem](function-map_mem.md) to map the virtual memory to the physical memory.
4. Call specific task APIs to execute tasks.
5. Call [acl.rt.unmap\_mem](function-unmap_mem.md) to cancel the mapping between the virtual memory and the physical memory.
6. Call [acl.rt.free\_physical](function-free_physical.md) to free the physical memory.
7. Call [acl.rt.release\_mem\_address](function-release_mem_address.md) to free the virtual memory.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtReserveMemAddress(void **virPtr, size_t size, size_t alignment, void *expectPtr, uint64_t flags)
    ```

- **Python Function**

    ```python
    vir_ptr, ret = acl.rt.reserve_mem_address(size, alignment, expect_ptr, flags)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| size | Int, size of the virtual address space, in bytes. Must not be `0`.|
| alignment | Int, alignment value of the virtual address. This parameter is reserved and can only be set to `0`.|
| expectPtr | Int, start address of the virtual address space to be returned. This parameter is reserved and can only be set to `0`.|
| flags | Int, huge page/common page flag. This parameter is reserved. The recommended value is `0`.|

## Return Values

| Return Value| Description|
| --- | --- |
| virPtr | Int, pointing to the address of the allocated virtual address space.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- On Atlas 200I/500 A2 inference products, this API cannot be called in Ascend RC mode.
- To use the virtual memory reserved by this API, only [memcpy\_async](function-memcpy_async.md) can be called to copy data between two devices in the single-process scenario.
