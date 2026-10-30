# Function: allocator\_set\_get\_addr\_from\_block\_func\_to\_desc

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

Sets the callback function for obtaining the device memory address based on the allocated block when the user-provided allocator is used.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtAllocatorSetGetAddrFromBlockFuncToDesc(aclrtAllocatorDesc allocatorDesc, aclrtAllocatorGetAddrFromBlockFunc func)
    ```

- **Python Function**

    ```python
    ret = acl.rt.allocator_set_get_addr_from_block_func_to_desc(allocatorDesc, func)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| allocatorDesc | Int, pointer address of the allocator descriptor. Call [acl.rt.allocator_create_desc](function-allocator_create_desc.md) to set the allocator description in advance.|
| func | Callback function for obtaining the device memory address based on the allocated block.<br>Callback function definition:<br>`def allocator_get_addr_from_block_func(block): pass` |

## Return Values

| Return Value| Description|
| --- | --- |
| ret | int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
