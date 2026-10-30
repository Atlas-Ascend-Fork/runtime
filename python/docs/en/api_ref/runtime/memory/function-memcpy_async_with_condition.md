# Function: memcpy\_async\_with\_condition (Deprecated)

**Note: This API will be deprecated in future releases. Use [acl.rt.memcpy\_async](function-memcpy_async.md) instead.**

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

This API extends the functionality of aclrtMemcpyAsync. If the input memory is not allocated through the API provided by PyACL, this API returns only after the memory copy is complete. Otherwise, this API is asynchronous. A successful API call only indicates that the task is delivered, but not executed. After this API is called, call the synchronization API (for example, [acl.rt.synchronize\_stream](../stream/function-synchronize_stream.md)) to ensure that the memory copy task is complete.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtMemcpyAsyncWithCondition(void *dst, size_t destMax, const void *src, size_t count, aclrtMemcpyKind kind,aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret = acl.rt.memcpy_async_with_condition(dst, dest_max, src, count, kind, stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| dst | Int, pointer to the destination memory address.|
| destMax | Int, memory size in bytes in the destination address|
| src | Int, pointer to the source memory address.|
| count | Int, size in bytes to copy.|
| kind | Int, memory copy type.<br>`0`: ACL_MEMCPY_HOST_TO_HOST, memory copy within the host.<br>`1`: ACL_MEMCPY_HOST_TO_DEVICE, memory copy from the host to the device.<br>`2`: ACL_MEMCPY_DEVICE_TO_HOST, memory copy from the device to the host.<br>`3`: ACL_MEMCPY_DEVICE_TO_DEVICE, memory copy within the device. This API is not supported on the Atlas 500 Pro AI edge server (model 3000).<br>`4`: ACL_MEMCPY_DEFAULT. The system determines the copy direction based on the source and destination memory addresses.|
| stream | Int, stream.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- In Ascend EP mode, this API does not support asynchronous memory copy within the host. If the input kind is `ACL\_MEMCPY\_HOST\_TO\_HOST`, the API returns the error code `ACL\_ERROR\_RT\_FEATURE\_NOT\_SUPPORT`.
<!-- npu="310b" id7 -->
- In Ascend RC mode, when an application is running on the board, if the kind passed to this API call is `ACL\_MEMCPY\_HOST\_TO\_DEVICE`, `ACL\_MEMCPY\_DEVICE\_TO\_HOST`, or `ACL\_MEMCPY\_HOST\_TO\_HOST`, the system uses `ACL\_MEMCPY\_DEVICE\_TO\_DEVICE` by default to perform memory copy within the device.
<!-- end id7 -->
<!-- npu="310p" id8 -->
- In open Ctrl CPU mode, when an application is running on the device, if the kind passed to this API call is `ACL\_MEMCPY\_HOST\_TO\_DEVICE`, `ACL\_MEMCPY\_DEVICE\_TO\_HOST`, or `ACL\_MEMCPY\_HOST\_TO\_HOST`, the system uses `ACL\_MEMCPY\_DEVICE\_TO\_DEVICE` by default to perform memory copy within the device.
<!-- end id8 -->
