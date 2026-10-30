# Function: query\_event\_status

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

Queries the execution status of all tasks captured in an event. For details, see the [acl.rt.record\_event](function-record_event.md) API reference.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtQueryEventStatus(aclrtEvent event, aclrtEventRecordedStatus *status)
    ```

- **Python Function**

    ```python
    status, ret = acl.rt.query_event_status(event)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| event | Int, pointer address of the event object to be queried.|

## Return Values

| Return Value| Description|
| --- | --- |
| status | Int, pointer address of the event status.<br>`ACL_EVENT_RECORDED_STATUS_NOT_READY = 0`: The event is not recorded in the stream, or the event recorded in the stream is not executed or fails to be executed.<br>`ACL_EVENT_RECORDED_STATUS_COMPLETE = 1`: The event recorded in the stream is successfully executed.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

If [acl.rt.record\_event](function-record_event.md) and acl.rt.query\_event\_status are called in different threads, the execution time of the two APIs may be out of order due to multi-threading. As a result, the completion status of the queried event object does not meet the expectation.
