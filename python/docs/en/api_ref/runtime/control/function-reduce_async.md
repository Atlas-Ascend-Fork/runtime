# Function: reduce\_async

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

Performs a Reduce operation, including SUM, MIN, and MAX.

This API is asynchronous. The API call delivers a task rather than executes a task. After this API is called, you need to call a synchronization API (for example, [synchronize\_stream](../stream/function-synchronize_stream.md)) to ensure that the task is complete. Otherwise, service exceptions (such as training or inference exceptions) or unknown situations (such as device disconnection or card disconnection) may occur.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtReduceAsync(void *dst, const void *src, uint64_t count, aclrtReduceKind kind, aclDataType type, aclrtStream stream, void *reserve)
    ```

- **Python Function**

    ```python
    ret = acl.rt.reduce_async(dst, src, count, kind, type, stream, reserve)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| dst | Int, pointer to the destination memory address.|
| src | Int, pointer to the source memory address.|
| count | Int, size of the source memory, in bytes.|
| kind | Int, operation type. For details, see [aclrtReduceKind](../datatypes/aclrtReduceKind.md).|
| type | Int, data type.<br>For details, see [aclDataType](../datatypes/aclDataType.md).|
| stream | Int, stream. Pass `0` if the default stream is used.|
| reserve | Int, reserved parameter. Currently, this parameter is fixed at `NULL`.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

`dts` and `src` must be on the same device as `stream`.
<!-- npu="A3" id7 -->
Atlas A3 products support the following data types: int8, int16, int32, fp16, fp32, and bf16.
<!-- end id7 -->
<!-- npu="910b" id8 -->
Atlas A2 products support the following data types: int8, int16, int32, fp16, fp32, and bf16.
<!-- end id8 -->
<!-- npu="310b" id9 -->
Atlas 200I/500 A2 inference products support the following data types: int8, int16, int32, fp16, and fp32.
<!-- end id9 -->
<!-- npu="310p" id10 -->
Atlas inference products support the following data types: fp32, fp16, and int16.
<!-- end id10 -->
<!-- npu="910" id11 -->
Atlas training products support only the fp32 data type.
<!-- end id11 -->
