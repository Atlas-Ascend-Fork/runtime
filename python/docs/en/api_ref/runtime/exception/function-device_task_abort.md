# Function: device\_task\_abort

## Applicable Products

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

Stops the tasks that are being executed on a specified device and discards the tasks that have been delivered to the device. This API allows you to set an infinite wait interval or a specific timeout interval. If a specific timeout interval is configured, the API returns an error when the timeout interval is exceeded after this API is called.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtDeviceTaskAbort(int32_t deviceId, uint32_t timeout);
    ```

- **Python Function**

    ```python
    ret = acl.rt.device_task_abort(device_id, timeout)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| deviceId | Int, device ID. The value must be the same as the device ID in [set_device](../device/function-set_device.md).|
| timeout | Int, timeout interval.<br>The value can be:<br>0: waits forever.<br>> 0: specific timeout interval, in milliseconds. The maximum timeout interval is 36 minutes.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

This API is reserved and is not supported currently.
