# Function: device\_can\_access\_peer

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

Queries whether memory copy is supported between two devices.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtDeviceCanAccessPeer(int32_t *canAccessPeer, int32_t deviceId, int32_t peerDeviceId)
    ```

- **Python Function**

    ```python
    can_access_peer, ret = acl.rt.device_can_access_peer(dev_id, peer_dev_id)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| dev_id | Int, specified device ID, which must be different from that of `peer_dev_id`.<br>Must be in the range of [0, Device count – 1]. Call [acl.rt.get_device_count](function-get_device_count.md) to obtain the device count.|
| peer_dev_id | Int, specified device ID, which must be different from that of `dev_id`.<br>Must be in the range of [0, Device count – 1]. Call [acl.rt.get_device_count](function-get_device_count.md) to obtain the device count.|

## Return Values

| Return Value| Description|
| --- | --- |
| can_access_peer | Int, whether memory copy is supported between the device specified by `dev_id` and the device specified by `peer_dev_id`. `1`: supported; `0`: not supported.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- This API supports memory copy only in physical machines and containers.
- This API supports memory copy only between devices in the same PCIe switch. In AI Server applications, memory copy between devices is supported although they reside in different PCIe switches.
- This API supports memory copy only between devices in the same physical machine or container.
- This API supports memory copy only between devices of threads in the same process.
- This API supports memory copy between devices in the same PCIe switch only when the related ports of the host are enabled (such as the host BIOS).
- This API is not supported on the Atlas 500 Pro AI edge server (model 3000).
