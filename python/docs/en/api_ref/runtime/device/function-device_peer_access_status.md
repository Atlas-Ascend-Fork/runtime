# Function: device\_peer\_access\_status

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

Queries the data exchange status between two devices.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtDevicePeerAccessStatus(int32_t deviceId, int32_t peerDeviceId, int32_t *status)
    ```

- **Python Function**

    ```python
    status, ret = acl.rt.device_peer_access_status(device_id, peer_device_id)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| device_id | Int, device ID.|
| peer_dev_id | Int, device ID.<br>Must be in the range of [0, Device count – 1]. Call [acl.rt.get_device_count](function-get_device_count.md) to obtain the device count.|

## Return Values

| Return Value| Description|
| --- | --- |
| status | Int, device status.<br>`0`: Data exchange is disabled.<br>`1`: Data exchange is enabled.|
| ret | Int. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

This API can only be used to query the data exchange status of two devices whose IDs are within the value range. If the input device ID is out of the range [0, (Number of available devices – 1)], the query result is 0 or the error code `ACL\_ERROR\_RT\_PARAM\_INVALID` is returned.
