# Function: create\_stream\_with\_config

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

Creates a stream in the calling process or thread.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtCreateStreamWithConfig(aclrtStream *stream, uint32_t priority, uint32_t flag)
    ```

- **Python Function**

    ```python
    stream, ret = acl.rt.create_stream_with_config(priority, flag)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| priority | `priority`: int, priority.<br>The value range is [0, 7]. A maximum of eight priorities are available. A smaller value indicates a higher priority. `0` indicates the highest priority and `7` indicates the lowest priority. If the configured priority exceeds the value range, the priority is changed to the boundary value.|
| flag | Int, flag of the stream.<br>For details about the value of `flag`, see "flag Values."|

## flag Values

The flag can be set to a single value or a combination of multiple values using the bitwise OR operator (|), for example, `0x0 | 0x2`. If a value that does not support bitwise OR is specified, the API returns an error. If a value beyond the specified range is configured, the stream created by this API is equivalent to that created by the [acl.rt.create\_stream](../stream/function-create_stream.md) API.

- `0x00000001: ACL\_STREAM\_FAST\_LAUNCH`: When a stream is created in this mode, the task delivery speed is faster.

    In ACL\_STREAM\_FAST\_LAUNCH mode, internal system resources are pre-allocated when the stream is created. Therefore, the stream creation duration is longer but the task launching duration is shorter. If a stream is created once and used multiple times, the total duration will be shorter. However, pre-allocation for internal resources during stream creation increases memory consumption. By contrast, if you create a stream by calling [acl.rt.create\_stream](../stream/function-create_stream.md), internal system resources are allocated only when the stream is used. As a result, the task launching duration is longer.

- `0x00000002: ACL\_STREAM\_FAST\_SYNC`: Creates a stream that blocks the current thread and queries the task execution status to return a result upon task completion after you call [acl.rt.synchronize_stream](../stream/function-synchronize_stream.md).

    Compared with the stream created by calling [acl.rt.create_stream](../stream/function-create_stream.md), the stream created by calling this API in ACL\_STREAM\_FAST\_SYNC mode does not wait for the notification of task completion on the device when [acl.rt.synchronize_stream](../stream/function-synchronize_stream.md) is called. This reduces the total duration, but the active query operation increases the CPU performance consumption.

## Return Values

| Return Value| Description|
| --- | --- |
| stream | Int, stream object pointer address.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
