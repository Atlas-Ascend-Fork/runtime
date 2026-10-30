# Function: unmap\_mem

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

Unmaps virtual memory from physical memory.

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
    aclError aclrtUnmapMem(void *virPtr)
    ```

- **Python Function**

    ```python
    ret = acl.rt.unmap_mem(vir_ptr)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| vir_ptr | Int, virtual address to be unmapped.|

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
