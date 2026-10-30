# Function: set\_device\_res\_limit

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

Sets the device resource limits of the current process.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtSetDeviceResLimit(int32_t deviceId, aclrtDevResLimitType type, uint32_t value)
    ```

- **Python Function**

    ```python
    ret = acl.rt.set_device_res_limit(device_id, type, value)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| device_id | Int, device ID.|
| type | Int, enumerated value. For details, see [aclrtDevResLimitType](../datatypes/aclrtDevResLimitType.md).|
| value | Int, resource limit.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

This API must be called after [set_device](../device/function-set_device.md) is called and before the operator is executed. If the same device is set for multiple times, the last setting takes effect.
