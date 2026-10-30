# Function: record\_notify

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

Records a Notify object in a specified stream. When [acl.rt.record_notify](function-record_notify.md) and [acl.rt.wait_and_reset_notify](function-wait_and_reset_notify.md) are used together, they are mainly used to implement synchronization between multiple streams.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtRecordNotify(aclrtNotify notify, aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret = acl.rt.record_notify(notify, stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| notify | Int, pointer address of the Notify to be recorded.|
| stream | Int, pointer address of the stream. For example, in the scenario where Stream2 waits for Stream1, set this parameter to `Stream1`.<br>Pass `0` if the default stream is used.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
