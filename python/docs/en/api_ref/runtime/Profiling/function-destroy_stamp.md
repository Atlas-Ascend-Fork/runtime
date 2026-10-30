# Function: destroy\_stamp

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

Destroys a msproftx event stamp.

## Prototype

- **C Prototype**

    ```c
    void aclprofDestroyStamp(void *stamp)
    ```

- **Python Function**

    ```python
    acl.prof.destroy_stamp(stamp)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| stamp | Int, stamp pointer address, indicating the msproftx event stamp. Specifies the pointer address of the [function: create_stamp](function-create_stamp.md) API.|

## Return Values

None

## Constraints

This API is used in pair with [function: create_stamp](function-create_stamp.md) and called before [Function: stop](function-stop.md).
