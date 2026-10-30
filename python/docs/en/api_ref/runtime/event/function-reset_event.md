# Function: reset\_event

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

Resets an event. Resets the event only after all tasks in the stream are completely executed. This API is asynchronous.

For stream synchronization, this API is called after an [acl.rt.stream\_wait\_event](function-stream_wait_event.md) call.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtResetEvent(aclrtEvent event, aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret = acl.rt.reset_event(event, stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| event | Int, pointer address of the event object to be reset.|
| stream | Int, pointer address of the stream object where the event is located.<br>For stream synchronization, for example, if `Stream2` waits for `Stream1`, set this parameter to `Stream2`.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

Only the events created by [acl.rt.creat\_event\_with\_flag](function-create_event_with_flag.md) with the ACL\_EVENT\_SYNC flag can be reset.

**Note**: If tasks in multiple streams need to wait for the same event, calling this API to reset the event is not recommended. As shown in the figure, if aclrtResetEvent is called after aclrtStreamWaitEvent in stream 2, the event will be reset. As a result, aclrtStreamWaitEvent in stream 3 will fail.

![](../figures/relationship_among_Device_Context_Stream.png)
