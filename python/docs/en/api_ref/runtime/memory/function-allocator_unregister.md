# Function: allocator\_unregister

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
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas inference products: Supported
<!-- end id5 -->
<!-- npu="910" id6 -->
- Atlas training products: Supported
<!-- end id6 -->

## Function

Deregisters the user-provided Allocator and its callback function, so that the Allocator cannot be used.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtAllocatorUnregister(aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret = acl.rt.allocator_unregister(stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| stream | Int, stream corresponding to the Allocator.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- Before destroying an allocator, call this API to deregister the allocator.
- If the stream to be deregistered does not exist or this API is called for multiple times to deregister the stream, no operation will be performed and a success message is returned.
