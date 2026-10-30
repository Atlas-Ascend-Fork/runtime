# Function: set\_device

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

Sets the compute device in the current thread. aclrtSetDevice can be called to specify the same device for computation in different threads.

If there are multiple devices, aclrtSetDevice can be called in the process to switch to another device.

Calling this API implicitly creates a default context that contains a default stream. In multiple threads of the same process, if aclrtSetDevice is called and the same device is specified for computation, these threads share the same default context.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtSetDevice(int32_t deviceId)
    ```

- **Python Function**

    ```python
    ret = acl.rt.set_device(device_id)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| device_id | Int, device ID.<br>Must be in the range of [0, Device count – 1]. Call [acl.rt.get_device_count](function-get_device_count.md) to obtain the device count.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

If [acl.rt.set_device](../device/function-set_device.md) is called for multiple times in a process, [acl.rt.reset_device](../device/function-reset_device.md) does not need to be called to reset the device resources, because the device resources will be reset when the process exits. You are advised to use [acl.rt.set\_device](../device/function-set_device.md) and [acl.rt.reset\_device](../device/function-reset_device.md) in pairs. When the device resources are no longer needed, call [acl.rt.reset\_device](../device/function-reset_device.md) to reset the device resources used by the current process promptly.

You can call [acl.rt.set\_device](../device/function-set_device.md) to specify the same device for computation in different processes or threads. In a multithreaded process, if [acl.rt.set\_device](../device/function-set_device.md) is called to specify the same compute device, they use the same default context.

## Reference

For details about the API call process and example, see "Runtime Resource Allocation and Deallocation" and "Synchronous Wait" in "Application Development (Python)".
