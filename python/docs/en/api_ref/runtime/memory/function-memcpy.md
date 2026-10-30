# Function: memcpy

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

Copies memory.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtMemcpy(void *dst, size_t destMax, const void *src, size_t count, aclrtMemcpyKind kind)
    ```

- **Python Function**

    ```python
    ret = acl.rt.memcpy(dst, dest_max, src, count, kind)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| dst | Int, pointer address of the destination memory address.|
| destMax | Int, memory size in bytes in the destination address|
| src | Int, pointer address of the source memory address.|
| count | Int, size in bytes to copy.|
| kind | Int, memory copy type, reserved. The enumerated values are invalid. The system determines whether the data from the source address can be copied to the destination address based on the pointer addresses of the source and destination memory addresses. If the data cannot be copied to the destination address, the system returns an error.<br>`0`: ACL_MEMCPY_HOST_TO_HOST, memory copy within the host.<br>`1`: ACL_MEMCPY_HOST_TO_DEVICE, memory copy from the host to the device.<br>`2`: ACL_MEMCPY_DEVICE_TO_HOST, memory copy from the device to the host.<br>`3`: ACL_MEMCPY_DEVICE_TO_DEVICE, memory copy within the device. This API is not supported on the Atlas 500 Pro AI edge server (model 3000).<br>`4`: ACL_MEMCPY_DEFAULT. The system determines the copy direction based on the source and destination memory addresses.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- This API copies the memory immediately. No implicit device synchronization or stream synchronization is performed within the function.
<!-- npu="950,910b,910,310p" id7 -->
- To perform memory copy between two devices, call [acl.rt.device\_can\_access\_peer](../device/function-device_can_access_peer.md) to query whether inter-device data exchange is supported by the devices, call [acl.rt.device\_enable\_peer\_access](../device/function-device_enable_peer_access.md) to enable inter-device data exchange between the devices, and then call this API to perform memory copy.

    **This restriction applies to the following models:**

    <!-- npu="950" id8 -->
    Ascend 950PR&950DT products
    <!-- end id8 -->

    <!-- npu="910b" id9 -->
    Atlas A2 products
    <!-- end id9 -->

    <!-- npu="310p" id10 -->
    Atlas inference products
    <!-- end id10 -->

    <!-- npu="910" id11 -->
    Atlas training products
    <!-- end id11 -->
<!-- end id7 -->
