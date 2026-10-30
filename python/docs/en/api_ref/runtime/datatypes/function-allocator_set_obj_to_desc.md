# Function: allocator\_set\_obj\_to\_desc

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

Sets the allocator object in the allocator description when the user-provided allocator is used.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtAllocatorSetObjToDesc(aclrtAllocatorDesc allocatorDesc,  aclrtAllocator allocator)
    ```

- **Python Function**

    ```python
    ret = acl.rt.allocator_set_obj_to_desc(allocatorDesc, allocator)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| allocatorDesc | Int, pointer address of the allocator descriptor. Call [acl.rt.allocator_create_desc](function-allocator_create_desc.md) to set the allocator description in advance.|
| allocator | Int, pointer address of the allocator object provided by the user.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
