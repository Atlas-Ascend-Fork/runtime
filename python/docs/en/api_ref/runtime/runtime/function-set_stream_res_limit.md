# Function: set\_stream\_res\_limit

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

Sets the device resource limits for a specified stream.

This API must be called after [acl.rt.set_device](../device/function-set_device.md) and before operator execution. If the same stream is set multiple times, the last setting takes effect.

After calling this API to set the device resource limit for a specified stream, call [acl.rt.use\_stream\_res\_in\_current\_thread](function-use_stream_res_in_current_thread.md) to set the device resource limit for the specified stream in the current thread. You can call [acl.rt.get\_stream\_res\_limit](function-set_stream_res_limit.md) to query the default resource limits.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtSetStreamResLimit(aclrtStream stream, aclrtDevResLimitType type, uint32_t value)
    ```

- **Python Function**

    ```python
    ret = acl.rt.set_stream_res_limit(stream, type, value)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| stream | Int, specified stream. If `0` is passed, it indicates the default stream.|
| type | Int, resource type. Currently, Cube Core and Vector Core are supported. For details, see [aclrtDevResLimitType](../datatypes/aclrtDevResLimitType.md).|
| value | Int, resource limit.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
