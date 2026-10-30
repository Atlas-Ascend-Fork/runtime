# Function: set\_stream\_failure\_mode

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

Specifies the task scheduling mode to determine whether to continue the next task after a task fails, when multiple tasks are delivered to a stream.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtSetStreamFailureMode(aclrtStream stream, uint64_t mode)
    ```

- **Python Function**

    ```python
    ret = acl.rt.set_stream_failure_mode(stream, mode)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| stream | Int, pointer address of the stream to be operated.|
| mode | Int, the task scheduling mode to determine whether to continue the next task after a task fails, when multiple tasks are delivered to a stream.<br>The options are as follows:<br>`ACL_CONTINUE_ON_FAILURE = 0`: default value. If a task fails, the system continues to execute the next task.<br>`ACL_STOP_ON_FAILURE = 1`: After a task fails, the subsequent tasks are stopped.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- This API can be called only once for a specified stream to set the task scheduling mode.
- If the stop-on-failure mode is set for a stream, the stop-on-failure mode also applies to other streams in the context of the stream.
<!-- npu="950,A3,910b" id7 -->
- For Ascend 950PR&950DT, Atlas A3, and Atlas A2 products, the default stream can be specified (that is, the stream parameter is set to 0).
<!-- end id7 -->
<!-- npu="910,310p,310b" id8 -->
- For Atlas 200I/500 A2 inference products, Atlas inference products, and Atlas training products, the default stream cannot be specified (that is, the stream parameter cannot be set to 0).
<!-- end id8 -->
