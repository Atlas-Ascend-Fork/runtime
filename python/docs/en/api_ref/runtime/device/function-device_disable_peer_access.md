# Function: device\_disable\_peer\_access

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

Disables memory copy between the current device and a specified device. This API disables device-level memory copy.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtDeviceDisablePeerAccess(int32_t peerDeviceId)
    ```

- **Python Function**

    ```python
    ret = acl.rt.device_disable_peer_access(peer_dev_id)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| peer_dev_id | Int, device ID, which must be different from the current device ID.<br>Must be in the range of [0, Device count – 1]. Call [acl.rt.get_device_count](function-get_device_count.md) to obtain the device count.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- Call [acl.rt.device\_disable\_peer\_access](function-device_disable_peer_access.md) twice to enable data exchange between two devices. For example, call [acl.rt.device\_enable\_peer\_access](../device/function-device_enable_peer_access.md) once to enable data exchange between device 0 and device 1, and call [acl.rt.device\_disable\_peer\_access](function-device_disable_peer_access.md) again to enable data exchange between device 1 and device 0.
- This API is not supported on the Atlas 500 Pro AI edge server (model 3000).
