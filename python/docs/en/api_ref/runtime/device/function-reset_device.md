# Function: reset\_device

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

## Prototype

- **C Prototype**

    ```c
    aclError aclrtResetDevice(int32_t deviceId)
    ```

- **Python Function**

    ```python
    ret = acl.rt.reset_device(device_id)
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

If there are explicitly created contexts, streams, or events on the device to be reset, you are advised to follow the following calling sequence before resetting. Otherwise, exceptions may occur.

`API call sequence`: Call [acl.rt.destroy\_event](../event/function-destroy_event.md) to destroy the event, call [acl.rt.destroy\_stream](../stream/function-destroy_stream.md) to destroy the explicitly created Stream --\> Call [acl.rt.destroy\_context](../context/function-destroy_context.md) to destroy the explicitly created Context --\> Call [acl.rt.reset\_device](../device/function-reset_device.md).

## Reference

For details about the API call process and example, see "Runtime Resource Allocation and Deallocation" and "Synchronous Wait" in "Application Development (Python)".
