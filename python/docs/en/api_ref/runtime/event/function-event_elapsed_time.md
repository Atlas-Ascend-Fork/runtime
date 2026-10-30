# Function: event\_elapsed\_time

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

Computes the elapsed time between two events.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtEventElapsedTime(float *ms, aclrtEvent startEvent, aclrtEvent endEvent)
    ```

- **Python Function**

    ```python
    ms, ret = acl.rt.event_elapsed_time(start, end)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| start | Int, pointer address of the start event object.|
| end | Int, pointer address of the end event object.|

## Return Values

| Return Value| Description|
| --- | --- |
| ms | Float, elapsed time between two events, in milliseconds.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

API call sequence: Call [acl.rt.create\_event](function-create_event.md)/[acl.rt.create\_event\_with\_flag](function-create_event_with_flag.md) to create an event. --\> Call [acl.rt.record\_event](function-record_event.md) to record the start event and end event in the same stream. --\> Call [acl.rt.synchronize\_stream](../stream/function-synchronize_stream.md) to block the application until all tasks in the specified stream are complete. --\> Call [acl.rt.event\_elapsed\_time](function-event_elapsed_time.md) to calculate the elapsed time between two events.
