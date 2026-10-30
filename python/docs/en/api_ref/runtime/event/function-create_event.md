# Function: create\_event

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

Creates an event, which can be used to compute the elapsed time between two events and synchronize streams.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtCreateEvent(aclrtEvent *event)
    ```

- **Python Function**

    ```python
    event, ret = acl.rt.create_event()
    ```

## Parameters

None

## Return Values

| Return Value| Description|
| --- | --- |
| event | Int, pointer address of the created event object.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

The event created using this API cannot be used in [acl.rt.reset\_event](function-reset_event.md). Otherwise, undefined behavior may occur.

After an event is created by calling this API, the system allocates event resources only when [acl.rt.record\_event](function-record_event.md) is called. Therefore, the number of events is limited. After the number of events reaches the upper limit, the system waits for resource release.

Limit on the number of events:

<!-- npu="950,A3,910b,310b" id7 -->
- For the following product models, a maximum of 65,536 events are supported by a single device is:

    <!-- npu="950" id8 -->
    Ascend 950PR&950DT products
    <!-- end id8 -->

    <!-- npu="A3" id9 -->
    Atlas A3 products
    <!-- end id9 -->

    <!-- npu="910b" id10 -->
    Atlas A2 products
    <!-- end id10 -->

    <!-- npu="310b" id11 -->
    Atlas 200I/500 A2 inference products
    <!-- end id11 -->

<!-- end id7 -->
<!-- npu="310p" id12 -->
- For Atlas inference products, a maximum of 1023 events are supported per device.
<!-- end id12 -->
<!-- npu="910" id13 -->
- For Atlas training products, a maximum of 65535 events are supported per device.
<!-- end id13 -->
