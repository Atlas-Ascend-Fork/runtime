# Function: reset\_overflow\_status

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

Resets the overflow status of tasks on all streams in the current device. This API is asynchronous.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtResetOverflowStatus(aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret = acl.rt.reset_overflow_status(stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| stream | Specified stream to deliver an overflow status resetting task.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

This API is asynchronous. A successful call indicates only that the task has been delivered, not that it has completed. After calling this API, call a synchronization API (for example, [acl.rt.synchronize\_stream](../stream/function-synchronize_stream.md)) to ensure that the task is complete.

<!-- npu="950,A3,910b" id7 -->
For the following product models, the overflow status queried by this API is at the process level.

<!-- npu="950" id8 -->
- Ascend 950PR&950DT products
<!-- end id8 -->
<!-- npu="A3" id9 -->
- Atlas A3 products
<!-- end id9 -->
<!-- npu="910b" id10 -->
- Atlas A2 products
<!-- end id10 -->
<!-- end id7 -->
