# Function: notify\_batch\_reset

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
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas inference products: Not supported
<!-- end id5 -->
<!-- npu="910" id6 -->
- Atlas training products: Not supported
<!-- end id6 -->

## Function

Resets Notify objects in batches.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtNotifyBatchReset(aclrtNotify *notifies, size_t num)
    ```

- **Python Function**

    ```python
    ret = acl.rt.notify_batch_reset(notifies)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| notifies | List, list of Notify pointer addresses.<br>Definition: notifies=[notify_1, notify_2,...]<br>The Notify pointer address elements in the list are obtained by calling [acl.rt.create_notify](function-create_notify.md).|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|

## Constraints

This operation is not supported in the Ascend virtual instance scenario.
