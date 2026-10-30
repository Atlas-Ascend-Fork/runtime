# Function: reset\_stream\_res\_limit

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

After calling [acl.rt.set_stream_res_limit](function-set_stream_res_limit.md) to set the device resource limits of a specified stream, call this API to reset the device resource limits of the specified stream to the default setting. You can call [acl.rt.get_stream_res_limit](function-get_stream_res_limit.md) to query the default resource limits.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtResetStreamResLimit(aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret = acl.rt.reset_stream_res_limit(stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| stream | Int, specified stream. If `0` is passed, it indicates the default stream.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
