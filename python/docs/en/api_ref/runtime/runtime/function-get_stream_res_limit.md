# Function: get\_stream\_res\_limit

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

Obtains the device resource limits of a specified stream.

If [acl.rt.set_stream_res_limit](function-set_stream_res_limit.md) is not called to set the device resource limits, the device resource limits obtained by calling this API are prioritized as follows: device resource limits of the current process (set by calling [acl.rt.set_stream_res_limit](function-set_stream_res_limit.md)) \> AI default resource limits of the processor hardware.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtGetStreamResLimit(aclrtStream stream, aclrtDevResLimitType type, uint32_t *value)
    ```

- **Python Function**

    ```python
    value, ret = acl.rt.get_stream_res_limit(stream,  type)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| stream | Int, specified stream. If `0` is passed, it indicates the default stream.|
| type | Int, resource type. Currently, Cube Core and Vector Core are supported. For details, see [aclrtDevResLimitType](../datatypes/aclrtDevResLimitType.md).|

## Return Values

| Return Value| Description|
| --- | --- |
| value | Int, resource limit.|
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
