# Function: set\_device\_sat\_mode

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

Sets the output mode of the floating-point computation result of the device.

The setting takes effect only for the streams created on the device after this API call.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtSetDeviceSatMode(aclrtFloatOverflowMode mode)
    ```

- **Python Function**

    ```python
    ret = acl.rt.set_device_sat_mode(mode)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| mode | Int, output mode of the floating-point calculation result. For details, see [aclrtFloatOverflowMode](../datatypes/aclrtFloatOverflowMode.md).|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

The setting takes effect only for the streams created on the device after this API call.
