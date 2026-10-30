# Function: free

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

Frees device memory.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtFree(void *devPtr)
    ```

- **Python Function**

    ```python
    ret = acl.rt.free(dev_ptr)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| dev_ptr | Int, pointer address of the memory to be freed.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- The acl.rt.free API can be used to free only the memory allocated by the [acl.rt.malloc](../memory/function-malloc.md) or [acl.rt.malloc\_cached](function-malloc_cached.md) API.
- This API immediately frees the input memory. No implicit device synchronization or stream synchronization is performed within the function. Ensure that the memory pointer is not accessed after this API is called.
