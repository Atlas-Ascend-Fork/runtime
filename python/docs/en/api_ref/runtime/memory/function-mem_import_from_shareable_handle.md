# Function: mem\_import\_from\_shareable\_handle

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

Obtains the information in `shareable\_handle` in this process and returns the handle in this process to establish the mapping between virtual addresses and physical addresses in this process. This API can also be used to generate a handle for a specified device.

This API must be used together with other APIs to implement memory sharing. For details about the process, see the description of [acl.rt.mem_export_to_shareable_handle](function-mem_export_to_shareable_handle.md).

## Prototype

- **C Prototype**

    ```c
    aclError aclrtMemImportFromShareableHandle(uint64_t shareableHandle, int32_t deviceId, aclrtDrvMemHandle *handle)
    ```

- **Python Function**

    ```python
    handle, ret = acl.rt.mem_import_from_shareable_handle(shareable_handle, device_id)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| shareable_handle | Int, shareable handle to be shared.<br>The value must be the same as the shareable handle exported by the [acl.rt.mem_export_to_shareable_handle](function-mem_export_to_shareable_handle.md) call.|
| deviceId | Int, ID of the device for which a handle is to be generated.<br>After the number of available devices is obtained by calling [acl.rt.get_device_count](../device/function-get_device_count.md), the value range of the device ID is [0, Number of available devices – 1].|

## Return Values

| Return Value| Description|
| --- | --- |
| handle | Int, physical memory handle to the process.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

<!-- npu="310b" id7 -->
- On Atlas 200I/500 A2 inference products, this API cannot be called in Ascend RC mode.
<!-- end id7 -->

- Before calling this API, ensure that the physical memory to be shared exists and cannot be released in advance.
- Each handle must correspond to only one shareable handle in the same process. One-to-many or many-to-one mapping is not allowed.
- You can call [acl.rt.mem\_export\_to\_shareable\_handle](function-mem_export_to_shareable_handle.md) on a device to export a handle, and then call this API to generate a handle on another device.
- When finishing using the memory, call [acl.rt.free\_physical](function-free_physical.md) to destroy the handle. The handle is destroyed only when all processes that call this API destroy the shareable handle.
<!-- npu="A3,910b,910,310p" id8 -->
- Physical memory can be shared across devices.

    Cross-device physical memory sharing is supported only by the following models and must be used together with the [acl.rt.device\_enable\_peer\_access](../device/function-device_enable_peer_access.md) API:

    <!-- npu="A3" id9 -->
    Atlas A3 products
    <!-- end id9 -->

    <!-- npu="910b" id10 -->
    Atlas A2 products
    <!-- end id10 -->

    <!-- npu="910" id11 -->
    Atlas training products
    <!-- end id11 -->

    <!-- npu="310p" id12 -->
    Atlas inference products
    <!-- end id12 -->
<!-- end id8 -->
