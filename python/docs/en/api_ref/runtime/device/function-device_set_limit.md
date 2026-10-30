# Function: acl.rt.device\_set\_limit

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

Sets the device resource limit of the current process, such as the stack space size of the Single Instruction Multiple Thread (SIMT) operator and the debugging and testing space size of the SIMT printf.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtDeviceSetLimit(aclrtDeviceLimit limit, size_t value)
    ```

- **Python Function**

    ```python
    ret = acl.rt.device_set_limit(limit, value)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| limit | Int, resource type. For details, see [aclrtDeviceLimit](../datatypes/aclrtDeviceLimit.md).|
| value | Int, resource limit, in bytes. The value of this parameter is related to the limit type. For details, see [aclrtDeviceLimit](../datatypes/aclrtDeviceLimit.md).|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- The support for the limit resource type varies according to the product model. For resource types that are not supported, `ACL\_ERROR\_RT\_FEATURE\_NOT\_SUPPORT` is returned.
- It is recommended that this API be called after acl.init and before acl.rt.set\_device to ensure that the resource limit configuration takes effect.
- If acl.rt.set\_device is called multiple times, acl.rt.set\_device and acl.rt.reset\_device are used in pairs because they involve reference counting. After the reference count decreases to 0, call this API to configure the resource limit, and then call acl.rt.set\_device again. The configuration takes effect only after these steps are performed. The call sequence is as follows:

    ```text
    acl.init --> acl.rt.device_set_limit (called for the first time) --> acl.rt.set_device (the resource limit configuration takes effect) --> service processing --> acl.rt.reset_device (reset device resources) --> acl.rt.device_set_limit (called for the second time) --> acl.rt.set_device (the resource limit configuration takes effect)
    ```

- You can use either this API or acl.init to configure resource limits, such as the stack space size of the SIMT operator and the debugging and testing space size of the SIMT printf. Using this API is more flexible and convenient for adjusting resource limits. If the resource limit is configured using both methods, the later configuration will overwrite the previous one.
- The device resource limit configured using this API applies to the current process. All devices share the same configuration, and different resource limits cannot be set for different devices.
- This API uses device 0 for configuration internally. If the `ASCEND\_RT\_VISIBLE\_DEVICES` environment variable is set and does not contain device 0, configuring the resource limit using this API or acl.init will fail. Therefore, if the `ASCEND\_RT\_VISIBLE\_DEVICES` environment variable is used, ensure that its value contains device 0.
