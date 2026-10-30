# Function: get\_primary\_ctx\_state

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

Obtains the status of the default context.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtGetPrimaryCtxState(int32_t deviceId, uint32_t *flags, int32_t *active)
    ```

- **Python Function**

    ```python
    active, flags, ret = acl.rt.get_primary_ctx_state(device_id)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| device_id | Int, device ID.|

## Return Values

| Return Value| Description|
| --- | --- |
| active | Int, pointer to the status of the default context. `0`: deactivated; `1`: activated.|
| flags | Int, reserved value. Currently, the value is fixed at `0`.|
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
