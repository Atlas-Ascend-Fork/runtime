# Function: event\_get\_timestamp

## Applicable Products

<!-- npu="950" id1 -->
- Ascend 950PR&950DT products: Supported
<!-- end id1 -->
<!-- npu="A3" id2 -->
- Atlas A3 products: supported
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

Obtains the execution end time of an event (time since the AI processor starts).

This API must be used together with other key APIs. The API call sequence is as follows:

- Call [acl.rt.create\_event](function-create_event.md)/[acl.rt.create\_event\_with\_flag](function-create_event_with_flag.md) to create an event.
- Call [acl.rt.record\_event](function-record_event.md) to record an event in a stream.
- Call [acl.rt.synchronize\_stream](../stream/function-synchronize_stream.md) to block the app until all tasks in the specified stream are complete.
- Call [acl.rt.event_get_timestamp](function-event_get_timestamp.md) to obtain the event execution time.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtEventGetTimestamp(aclrtEvent event, uint64_t *timestamp)
    ```

- **Python Function**

    ```python
    timestamp, ret = acl.rt.event_get_timestamp(event)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| event | Int, event to be queried.|

## Return Values

| Return Value| Description|
| --- | --- |
| timestamp | Int, time when the event execution ends, in microseconds.|
| ret | Int. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
