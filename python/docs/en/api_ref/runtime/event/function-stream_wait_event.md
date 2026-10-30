# Function: stream\_wait\_event

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

Blocks the running of a specified stream or multiple streams until the specified event is complete. This API is asynchronous.

All subsequent tasks submitted to the stream can be executed only after all tasks captured by the event are complete. For details about event capture, see [acl.rt.record\_event](function-record_event.md).

## Prototype

- **C Prototype**

    ```c
    aclError aclrtStreamWaitEvent(aclrtStream stream, aclrtEvent event)
    ```

- **Python Function**

    ```python
    ret = acl.rt.stream_wait_event(stream, event)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| stream | Int, pointer address of the stream that needs to wait for the event to complete. Pass `0` if the default stream is used.|
| event | Int, pointer address of the event to be waited for.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- This API is asynchronous. A successful call indicates only that the task has been delivered, not that it has completed. After calling this API, call a synchronization API (for example, [acl.rt.synchronize\_stream](../stream/function-synchronize_stream.md)) to ensure that the task is complete.
- [acl.rt.record\_event](function-record_event.md) and [acl.rt.stream\_wait\_event](function-stream_wait_event.md) are used in pair for synchronization between streams. When [acl.rt.record\_event](function-record_event.md) is called, an event resource is allocated. After [acl.rt.stream\_wait\_event](function-stream_wait_event.md) is called, [acl.rt.reset\_event](function-reset_event.md) should be called to free the event resource promptly.

    **API call sequence**: [acl.rt.create\_event](function-create_event.md) --\> [acl.rt.record\_event](function-record_event.md) --\> [acl.rt.stream\_wait\_event](function-stream_wait_event.md) --\> [acl.rt.reset\_event](function-reset_event.md)

- After initialization by calling [acl.init](../init/function-init.md) in a process, you can call [acl.rt.set\_op\_wait\_timeout](function-set_op_wait_timeout.md) to set the timeout interval. Tasks delivered by calling [acl.rt.stream\_wait\_event](function-stream_wait_event.md) in the process can wait within the configured timeout interval. If the wait time exceeds the configured timeout interval, an error is returned.

    acl.rt.stream\_wait\_event is an asynchronous API. When called, it delivers tasks, but not execute them. Therefore, if the wait time exceeds the configured timeout interval, an error is returned after [acl.rt.synchronize\_stream](../stream/function-synchronize_stream.md) is called.
