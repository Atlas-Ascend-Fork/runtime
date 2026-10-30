# Function: map\_mem

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

Maps virtual memory to physical memory.

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
    aclError aclrtMapMem(void *virPtr, size_t size, size_t offset, aclrtDrvMemHandle handle, uint64_t flags)
    ```

- **Python Function**

    ```python
    ret = acl.rt.map_mem(vir_ptr, size, offset, handle, flags)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| vir_ptr | Int, virtual address to be mapped. The address may not be the start address. You can also offset the address based on the start address and then map the address.|
| size | Int, size of the memory to be mapped, in bytes.<br>The value of size must be the same as that of the size parameter of the [acl.rt.malloc_physical](function-malloc_physical.md) API. The value of `size` must be aligned with the value of ACL_RT_MEM_ALLOC_GRANULARITY_MINIMUM obtained by the [acl.rt.mem_get_allocation_granularity](function-mem_get_allocation_granularity.md) API.|
| offset | Int, physical memory offset. It can only be set to `0` currently.|
| handle | Int, physical memory pointer address.<br>A virtual address segment reserved by using [acl.rt.reserve_mem_address](function-reserve_mem_address.md) is managed and allocated by the user and cannot be bound to the physical addresses allocated on two devices at the same time.<br>A virtual address segment reserved by using [acl.rt.reserve_mem_address](function-reserve_mem_address.md) is managed and allocated by the user and cannot be bound to the handles output by [acl.rt.malloc_physical](function-malloc_physical.md) and [acl.rt.mem_import_from_shareable_handle](function-mem_import_from_shareable_handle.md) at the same time.|
| flags | Int, reserved. Currently, this parameter can only be set to `0`.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

<!-- npu="310b" id7 -->
## Constraints

<!-- npu="310b" id8 -->
On Atlas 200I/500 A2 inference products, this API cannot be called in Ascend RC mode.
<!-- end id8 -->
<!-- end id7 -->
