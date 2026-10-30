# Function: pop

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

Records the end time of the time span by msproftx when an event occurs.

After this API is called, the profiling tool automatically records the end timestamp in `stamp`.

## Prototype

- **C Prototype**

    ```c
    aclError aclprofPop()
    ```

- **Python Function**

    ```python
    ret = acl.prof.pop()
    ```

## Parameters

None

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br>`0`: success<br>Other values: failure|

## Constraints

- This API is used in pair with [Function: push](function-push.md) to indicate the start and end time of a time span.
- Cross-thread calls are not supported. To perform cross-thread calls, use [Function: range_start](function-range_start.md) or [Function: range_stop](function-range_stop.md).
- Call this API between [Function: create_stamp](function-create_stamp.md) and [Function: destroy_stamp](function-destroy_stamp.md).
