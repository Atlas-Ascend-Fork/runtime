# Function: query\_device\_status

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

Queries the status of a device (normal or abnormal).

## Prototype

- **C Prototype**

    ```c
    aclError aclrtQueryDeviceStatus(int32_t deviceId, aclrtDeviceStatus *deviceStatus)
    ```

- **Python Function**

    ```python
    device_status, ret = acl.rt.query_device_status(device_id)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| device_id | Int, device ID.<br>After the number of available devices is obtained by calling [acl.rt.get_device_count](function-get_device_count.md), the value range of the device ID is [0, Number of available devices – 1].|

## Return Values

| Return Value| Description|
| --- | --- |
| device_status | Int, device status. For details, see [aclrtDeviceStatus](../datatypes/aclrtDeviceStatus.md).|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
