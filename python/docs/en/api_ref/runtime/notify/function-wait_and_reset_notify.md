# Function: wait\_and\_reset\_notify

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

Makes a stream wait on a Notify object, and then resets the Notify object.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtWaitAndResetNotify(aclrtNotify notify, aclrtStream stream, uint32_t timeout)
    ```

- **Python Function**

    ```python
    ret = acl.rt.wait_and_reset_notify(notify, stream, timeout)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| notify | Int, pointer address of the Notify to be recorded.|
| stream | Int, stream pointer address. For example, in the Stream1 scenario such as Stream2, set this parameter to Stream2.<br>Pass `0` if the default stream is used.|
| timeout | Int, timeout interval of the wait.<br>The value can be:<br>`0`: permanent wait.<br>> 0: specific timeout interval, in milliseconds.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
