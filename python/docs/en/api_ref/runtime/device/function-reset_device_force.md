# Function: reset\_device\_force

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

Resets the current compute device and releases the resources on the device. The resources to be released include the default context, default stream, and all streams created in the default context. If tasks in the default context or default stream have not yet completed, the system will wait for the tasks to finish before releasing the resources.

[acl.rt.reset_device_force](function-reset_device_force.md) can be used with [acl.rt.set_device](../device/function-set_device.md) or not with aclrtSetDevice. If they are not used in pairs, this API needs to be called only once after [acl.rt.set_device](../device/function-set_device.md) is called for one or more times for the same device in a process to release resources on the device.

```python
# This API is used together with acl.rt.set_device.
acl.rt.set_device(1) -> acl.rt.reset_device_force(1) -> acl.rt.set_device(1) -> acl.rt.reset_device_force(1)
 
# This API is not used together with acl.rt.set_device:
acl.rt.set_device(1) -> acl.rt.set_device(1) -> acl.rt.reset_device_force(1)
```

## Prototype

- **C Prototype**

    ```c
    aclError aclrtResetDeviceForce(int32_t deviceId)
    ```

- **Python Function**

    ```python
    ret = acl.rt.reset_device_force(device_id)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| device_id | Int, device ID.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- In a multi-thread scenario, if the [acl.rt.set\_device](../device/function-set_device.md) and acl.rt.reset\_device\_force APIs are called in each thread for the same device, as shown below, the acl.rt.reset\_device\_force API in thread 2 will return an error because the acl.rt.reset\_device\_force API in thread 1 has already released the resources of device 1.

    ```python
    Timeline ------------------------------------------------------------------------------>
    Thread 1: acl.rt.set_device(1)  acl.rt.reset_device_force(1)
    Thread 2: acl.rt.set_device(1)                                acl.rt.reset_device_force(1)
    ```

    In multi-thread scenarios, call acl.rt.reset\_device\_force once at the end of thread execution to release device resources, as shown below:

    ```python
    Timeline ------------------------------------------------------------------------------>
    Thread 1: acl.rt.set_device(1)   
    Thread 2: acl.rt.set_device(1)                                acl.rt.reset_device_force(1)
    ```

- The [acl.rt.reset\_device](../device/function-reset_device.md) and acl.rt.reset\_device\_force APIs can be used together. However, if the number of calls and the call sequence of the two reset APIs are incorrect, an error is returned.

    ```python
    # Positive example:
    # The two reset APIs are used with the set APIs in pairs, and acl.rt.reset_device_force is called after acl.rt.reset_device.
    acl.rt.set_device(1) -> acl.rt.reset_device(1) -> acl.rt.set_device(1) -> acl.rt.reset_device_force(1)
    acl.rt.set_device(1) -> acl.rt.set_device(1) -> acl.rt.reset_device(1) -> acl.rt.reset_device_force(1)
    
    # Negative example:
    # The acl.rt.reset_device API implements reference counting. Each time the acl.rt.reset_device API is called, the reference count is decreased by 1.
    # When the reference count decreases to 0, the resources on the device are released. If the acl.rt.reset_device or acl.rt.reset_device_force API is called again, an error is reported.
    acl.rt.set_device(1) -> acl.rt.set_device(1) -> acl.rt.reset_device(1) -> acl.rt.reset_device(1) -> acl.rt.reset_device_force(1)
    acl.rt.set_device(1) -> acl.rt.set_device(1) -> acl.rt.reset_device(1) -> acl.rt.reset_device_force(1) -> acl.rt.reset_device_force(1)
    # The acl.rt.reset_device_force API must be called after the acl.rt.reset_device API. Otherwise, an error is reported.
    acl.rt.set_device(1) -> acl.rt.set_device(1) -> acl.rt.reset_device_force(1) -> acl.rt.reset_device(1)
    ```
