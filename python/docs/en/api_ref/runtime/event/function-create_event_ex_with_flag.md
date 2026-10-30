# Function: create\_event\_ex\_with\_flag

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

Creates an event with a flag. Events with different flags are used for different functions. When an event is created, multiple flags can be carried (bitwise OR operation) to enable the corresponding flag function. Event resources are not restricted by hardware for the creation of events.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtCreateEventExWithFlag(aclrtEvent *event, uint32_t flag)
    ```

- **Python Function**

    ```python
    event, ret = acl.rt.create_event_ex_with_flag(flag)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| flag | Int, event pointer flag. The options are as follows:<br>`0x00000008: ACL_EVENT_TIME_LINE`: The number of created events is not limited, and the created events can be used to compute the elapsed time between events.<br>`0x00000001: ACL_EVENT_SYNC`: The number of created events is limited, and the created events can be used for synchronization between multiple streams.<br>`0x00000002: ACL_EVENT_CAPTURE_STREAM_PROGRESS`: The created event is used to trace the task execution progress of the stream.|

## Return Values

| Return Value| Description|
| --- | --- |
| event | Int, pointer address of the created event object.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- Events created by calling this API cannot be used in the following APIs: [acl.rt.reset\_event](function-reset_event.md), [acl.rt.query\_event](function-query_event.md) and [acl.rt.query_event_wait_status](function-query_event_wait_status.md).
- When this API is called to create an event, flag is a bitmap. You can perform operations on one or more flags, for example, acl.rt.create_event_ex_with_flag (`ACL_EVENT_TIME_LINE | ACL_EVENT_SYNC`).
  - If the value of `flag` contains `ACL_EVENT_SYNC`, the system allocates event resources only when [acl.rt.record_event](function-record_event.md) is called. Therefore, the number of events is limited. After the number of events reaches the upper limit, the system waits for resource release.

    Limit on the number of events:

    <!-- npu="310p" id7 -->
    - For Atlas inference products, a maximum of 1,023 events are supported per device.
    <!-- end id7 -->

    <!-- npu="310b" id8 -->
    - For Atlas 200I/500 A2 inference products, a maximum of 65,536 events are supported per device.
    <!-- end id8 -->

    <!-- npu="910" id9 -->
    - For Atlas training products, a maximum of 65,535 events are supported per device.
    <!-- end id9 -->

    <!-- npu="910b" id10 -->
    - For Atlas A2 products, a maximum of 65,536 events are supported per device.
    <!-- end id10 -->

    <!-- npu="A3" id11 -->
    - For Atlas A3 products, a maximum of 65,536 events are supported per device.
    <!-- end id11 -->

  - If the value of `flag` does not contain `ACL\_EVENT\_SYNC`, the event created by this API cannot be used in the [acl.rt.stream\_wait\_event](function-stream_wait_event.md) API.
