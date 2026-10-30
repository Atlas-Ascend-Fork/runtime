# Function: synchronize\_event\_with\_timeout

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

Blocks the current thread until all tasks captured by the event are complete. For details, see the event capture details in the [acl.rt.record\_event](function-record_event.md) API reference.

This API is enhanced based on [acl.rt.synchronize\_event](function-synchronize_event.md). You can set permanent waiting or a specific timeout interval. If a specific timeout interval is set, the application automatically exits when it is abnormal.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtSynchronizeEventWithTimeout(aclrtEvent event, int32_t timeout)
    ```

- **Python Function**

    ```python
    ret = acl.rt.synchronize_event_with_timeout(event, timeout)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| event | Int, event object pointer address to be waited for.|
| timeout | Int, API timeout interval.<br>The value can be:<br>-1: permanent wait, which is the same as the function of the [acl.rt.synchronize_event](function-synchronize_event.md) API.<br>> 0: specific timeout interval, in milliseconds.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
