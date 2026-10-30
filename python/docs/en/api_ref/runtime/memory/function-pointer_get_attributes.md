# Function: pointer\_get\_attributes

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

Obtains the memory attribute information, including whether the memory is on the host or device and the page table size.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtPointerGetAttributes(const void *ptr, aclrtPtrAttributes *attributes)
    ```

- **Python Function**

    ```python
    attributes, ret = acl.rt.pointer_get_attributes(ptr)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| ptr | Int, memory address.<br>Do not pass the device address mapped by [acl.rt.host_register](function-host_register.md) or the device address obtained by calling [acl.rt.host_get_device_pointer](function-host_get_device_pointer.md). Otherwise, undefined behavior may occur.|

## Return Values

| Return Value| Description|
| --- | --- |
| attributes | Dict, memory attributes. For details, see [aclrtPtrAttributes](../datatypes/aclrtPtrAttributes.md).|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
