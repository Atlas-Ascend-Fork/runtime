# Function: acl.rt.device\_get\_limit

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

Obtains the device resource limits of the current process.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtDeviceGetLimit(aclrtDeviceLimit limit, size_t *value)
    ```

- **Python Function**

    ```python
    value, ret = acl.rt.device_get_limit(limit)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| limit | Int, resource type. For details, see [aclrtDeviceLimit](../datatypes/aclrtDeviceLimit.md).|

## Return Values

| Return Value| Description|
| --- | --- |
| value | Int, resource limit, in bytes.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- The device resource limit configured by calling acl.rt.device\_set\_limit applies to the current process. All devices share the same configuration, and the same value is returned when the limit is queried on any device.
- The instantaneous value of the current process is obtained through this API, which does not ensure multi-thread concurrency security.

    For example, call acl.rt.device\_set\_limit to set the stack size to A, and then call acl.rt.set\_device to make the setting take effect. In this case, the value obtained by calling acl.rt.device\_get\_limit is A, and the resource limit is also A. Then, acl.rt.device\_set\_limit is called again to change the value to B, but acl.rt.set\_device is not called again. In this case, the value obtained by calling acl.rt.device\_get\_limit is B, but the actual resource limit is still A.
