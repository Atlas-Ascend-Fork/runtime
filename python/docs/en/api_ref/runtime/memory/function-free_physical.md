# Function: free\_physical

## Applicable Products

<!-- npu="950" id1 -->
- Ascend 950PR&950DT products: Supported
<!-- end id1 -->
<!-- npu="A3" id2 -->
- Atlas A3 products: supported
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

Frees the physical memory allocated by calling [acl.rt.malloc\_physical](function-malloc_physical.md).

If the physical memory is mapped to the virtual memory, the physical memory will not be freed here. The physical memory is actually freed only after the mapping between the physical memory and the virtual memory is canceled by calling [acl.rt.unmap\_mem](function-unmap_mem.md).

## Prototype

- **C Prototype**

    ```c
    aclError aclrtFreePhysical(aclrtDrvMemHandle handle)
    ```

- **Python Function**

    ```python
    ret = acl.rt.free_physical(handle)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| handle | Int, handle of the physical address to be freed.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

<!-- npu="310b" id7 -->
## Constraints

On Atlas 200I/500 A2 inference products, this API cannot be called in Ascend RC mode.
<!-- end id7 -->
