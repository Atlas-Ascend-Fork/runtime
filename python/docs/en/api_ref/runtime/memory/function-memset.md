# Function: memset

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

Initializes memory to a specified value.

The system determines whether the memory to be initialized is on the host or device based on the address. If the host memory is not allocated using the ACL API (for example, acl.rt.malloc\_host), undefined behavior will occur.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtMemset(void *devPtr, size_t maxCount, int32_t value, size_t count)
    ```

- **Python Function**

    ```python
    ret = acl.rt.memset(dev_ptr, max_count, value, count)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| dev_ptr | Int, start address of the memory.|
| max_count | Int, maximum memory size, in bytes.|
| value | Int, value to be set.|
| count | Int, memory length to be set to a specified value, in bytes.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

This API initializes the memory immediately. No implicit device synchronization or stream synchronization is performed within the function.
