# Function: get\_notify\_id

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

Obtains the ID of a specified Notify object.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtGetNotifyId(aclrtNotify notify, uint32_t *notifyId)
    ```

- **Python Function**

    ```python
    notify_id, ret = acl.rt.get_notify_id(notify)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| notify | Int, pointer address of the Notify to be queried.|

## Return Values

| Return Value| Description|
| --- | --- |
| notify_id | Int, Notify ID.|
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
