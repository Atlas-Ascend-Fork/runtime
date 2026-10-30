# Function: synchronize\_stream\_with\_timeout

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

Blocks the application until all tasks in the specified stream are complete. This API is an enhanced version of [acl.rt.synchronize\_stream](../stream/function-synchronize_stream.md). It allows you to set a timeout interval. If the application is abnormal, it automatically exits based on the configured timeout interval.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtSynchronizeStreamWithTimeout(aclrtStream stream, int32_t timeout)
    ```

- **Python Function**

    ```python
    ret = acl.rt.synchronize_stream_with_timeout(stream, timeout)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| stream | Int, pointer address of the stream object that needs to complete all tasks.|
| timeout | Int, API timeout interval. The value can be:<br>-1: permanent wait, which is the same as the function of the [acl.rt.synchronize_stream](function-synchronize_stream.md) API.<br>> 0: specific timeout interval, in milliseconds.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
