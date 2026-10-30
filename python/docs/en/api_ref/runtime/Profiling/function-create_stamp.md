# Function: create\_stamp

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

Creates a msproftx event stamp. When [Function: mark](function-mark.md), [Function: set_stamp_trace_message](function-set_stamp_trace_message.md), [Function: push](function-push.md), and [Function: range_start](function-range_start.md) are called later, the pointer address that describes the event must be used as the input to record the time span of the event.

This API is used in pair with [Function: destroy_stamp](function-destroy_stamp.md) and after [Function: start](function-start.md) is called.

## Prototype

- **C Prototype**

    ```c
    void *aclprofCreateStamp(void)
    ```

- **Python Function**

    ```python
    stamp = acl.prof.create_stamp()
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| stamp | Int, pointer address.<br>If `0` is returned, the operation fails.<br>If a pointer address of the `void` type is returned, the operation is successful.|

## Constraints

This API is used in pair with [Function: destroy_stamp](function-destroy_stamp.md) and after [acl.prof.start](function-start.md) is called.
