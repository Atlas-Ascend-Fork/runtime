# Function: device\_get\_uuid

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
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas inference products: Not supported
<!-- end id5 -->
<!-- npu="910" id6 -->
- Atlas training products: Not supported
<!-- end id6 -->

## Function

Obtains the universally unique identifier (UUID) of a device.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtDeviceGetUuid(int32_t deviceId, aclrtUuid *uuid)
    ```

- **Python Function**

    ```python
    uuid, ret = acl.rt.device_get_uuid(device_id)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| device_id | Int, NPU device ID.|

## Return Values

| Return Value| Description|
| --- | --- |
| uuid | Attribute value, which is the UUID of a device. For details, see `aclrtUuid`.|
| ret | Int. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
