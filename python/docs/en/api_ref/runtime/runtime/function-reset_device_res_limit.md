# Function: reset\_device\_res\_limit

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

After the device resource limit is set by calling [acl.rt.set_device_res_limit](function-set_device_res_limit.md), you can call this API to reset the device resource limit for the current process and restore the default setting.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtResetDeviceResLimit(int32_t deviceId)
    ```

- **Python Function**

    ```python
    ret = acl.rt.reset_device_res_limit(device_id)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| device_id | Int, device ID.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
