# Function: range\_start

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

Records the start time of the time span by msproftx when an event occurs.

After this API is called, the Profiling tool automatically records the start timestamp in `stamp` and sets the event type to `Start` or `Stop`. The tool also generates a unique process ID, and saves the stamp in a map maintained by process.

## Prototype

- **C Prototype**

    ```c
    aclError aclprofRangeStart(void *stamp, uint32_t *rangeId)
    ```

- **Python Function**

    ```python
    range_id, ret = acl.prof.range_start(stamp)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| stamp | Int, stamp pointer address, indicating the msproftx event stamp. This specifies the pointer to the [function: create_stamp](function-create_stamp.md) API.|

## Return Values

| Return Value| Description|
| --- | --- |
| range_id | Int, unique ID of a msproftx event stamp. Used to distinguish between threads.|
| ret | Int, error code.<br>`0`: success<br>Other values: failure|

## Constraints

- This API is used in pair with [Function: range_stop](function-range_stop.md) to indicate the start and end time of a time span.
- Cross-thread calls are supported.
- Call this API between [Function: create_stamp](function-create_stamp.md) and [Function: destroy_stamp](function-destroy_stamp.md).
