# Function: get\_device\_capability

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

Queries the hardware specifications of the corresponding device in the operating environment.

## Prototype

- **C Prototype**

    ```c
    aclError aclGetDeviceCapability(uint32_t deviceId, aclDeviceInfo deviceInfo, int64_t *value)
    ```

- **Python Function**

    ```python
    value, ret = acl.get_device_capability(device_id, device_info)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| device_id | Int, device ID.<br>After the number of available devices is obtained by calling [acl.rt.get_device_count](../device/function-get_device_count.md), the value range of the device ID is [0, Number of available devices – 1].|
| device_info | Int, hardware specification type of the device. For details, see [aclDeviceInfo](../datatypes/aclDeviceInfo.md).|

## Return Values

| Return Value| Description|
| --- | --- |
| value | Int, hardware specifications.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
