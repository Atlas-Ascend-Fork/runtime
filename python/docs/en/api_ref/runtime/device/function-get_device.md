# Function: get\_device

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

Obtains the ID of the device currently in use.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtGetDevice(int32_t *deviceId)
    ```

- **Python Function**

    ```python
    device_id, ret = acl.rt.get_device()
    ```

## Parameters

None

## Return Values

| Return Value| Description|
| --- | --- |
| device_id | Pointer to the device ID.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

If no device is specified in advance, an error is returned when acl.rt.get\_device is called.
