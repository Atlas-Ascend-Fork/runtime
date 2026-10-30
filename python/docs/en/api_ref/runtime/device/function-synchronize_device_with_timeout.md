# Function: synchronize\_device\_with\_timeout

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

Blocks app execution until the compute device has completed all preceding requested tasks. This API is enhanced based on [synchronize\_device](function-synchronize_device.md) and allows you to set the timeout interval. When an application is abnormal, the application automatically exits based on the configured timeout interval. In this case, this API returns ACL\_ERROR\_RT\_STREAM\_SYNC\_TIMEOUT.

If there are multiple devices, this API is called to wait for the device corresponding to the current context.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtSynchronizeDeviceWithTimeout(int32_t timeout)
    ```

- **Python Function**

    ```python
    ret = acl.rt.synchronize_device_with_timeout(timeout)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| timeout | Int, API timeout interval.<br>The value can be:<br>-1: permanent wait, which is the same as the function of the [synchronize_device](function-synchronize_device.md) API.<br>> 0: specific timeout interval, in milliseconds.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
