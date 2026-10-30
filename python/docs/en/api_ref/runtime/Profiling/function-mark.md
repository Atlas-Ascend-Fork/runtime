# Function: mark

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

Marks an instantaneous event by msproftx.

After this API is called, the Profiling tool automatically adds the current timestamp to `stamp` and sets the event type to `Mark`, indicating that a msproftx profiling process starts.

## Prototype

- **C Prototype**

    ```c
    aclError aclprofMark(void *stamp)
    ```

- **Python Function**

    ```python
    ret = acl.prof.mark(stamp)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| stamp | Int, stamp pointer address, indicating the msproftx event stamp. Specifies the pointer address of the [function: create_stamp](function-create_stamp.md) API.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br>`0`: success<br>Other values: failure|

## Constraints

Call this API between [Function: create_stamp](function-create_stamp.md) and [Function: destroy_stamp](function-destroy_stamp.md).
