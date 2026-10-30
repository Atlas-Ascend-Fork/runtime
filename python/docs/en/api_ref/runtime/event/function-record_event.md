# Function: record\_event

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

Records an event in a stream. When this API is called, the tasks that have been delivered in the current stream are captured and recorded in the event. Therefore, when [acl.rt.query\_event\_status](function-query_event_status.md) or [acl.rt.stream\_wait\_event](function-stream_wait_event.md) is called, the system checks or waits until all the tasks captured in the event are complete.

For events created using [acl rt.create\_event\_ex\_with\_flag](function-create_event_ex_with_flag.md):

- **This API supports event reuse for multiple records of the same event**. Each record captures the tasks that have been delivered on the current stream and overwrites the tasks in the event. When [acl.rt.stream\_wait\_event](function-stream_wait_event.md) is called, the tasks saved in the latest event are used and are not affected by subsequent calls to acl.rt.record\_event.
- **Before this API is called for the first time**, no task is in the event. Therefore, `ACL\_EVENT\_RECORDED\_STATUS\_COMPLETE` is returned when [acl.rt.query\_event\_status](function-query_event_status.md) is called.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtRecordEvent(aclrtEvent event, aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret = acl.rt.record_event(event, stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| event | Int, pointer address of the event to be recorded.|
| stream | Int, stream (pointer address) to which the event is recorded. Pass `0` if the default stream is used.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- This API is asynchronous. A successful call indicates only that the task has been delivered, not that it has completed. After calling this API, call a synchronization API (for example, [acl.rt.synchronize\_stream](../stream/function-synchronize_stream.md)) to ensure that the task is complete.
- [acl.rt.record\_event](function-record_event.md) and [acl.rt.stream\_wait\_event](function-stream_wait_event.md) are used in pair for synchronization between streams. When [acl.rt.record\_event](function-record_event.md) is called, an event resource is allocated. After [acl.rt.stream\_wait\_event](function-stream_wait_event.md) is called, [acl.rt.reset\_event](function-reset_event.md) should be called to free the event resource promptly.

    **API call sequence**: [acl.rt.create\_event](function-create_event.md) --\> [acl.rt.record\_event](function-record_event.md) --\> [acl.rt.stream\_wait\_event](function-stream_wait_event.md) --\> [acl.rt.reset\_event](function-reset_event.md)
