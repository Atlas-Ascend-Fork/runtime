# Function: get\_device\_capability

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

Queries whether the device feature is supported.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtGetDeviceCapability(int32_t deviceId, aclrtDevFeatureType devFeatureType, int32_t *value)
    ```

- **Python Function**

    ```python
    value, ret = acl.rt.get_device_capability(device_id, dev_feature_type)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| device_id | Int, device ID.|
| dev_feature_type | Int, enumerated value. For details, see [aclrtDevFeatureType](../datatypes/aclrtDevFeatureType.md).|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
| value | Int, whether the feature is supported.<br>`0`: no<br>`1`: yes|
