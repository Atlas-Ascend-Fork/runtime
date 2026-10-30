# Function: set\_op\_wait\_timeout

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
- Atlas inference products: Not supported
<!-- end id5 -->
<!-- npu="910" id6 -->
- Atlas training products: Supported
<!-- end id6 -->

## Function

Sets the timeout interval for waiting for the completion of a specified event.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtSetOpWaitTimeout(uint32_t timeout)
    ```

- **Python Function**

    ```python
    ret = acl.rt.set_op_wait_timeout(timeout)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| timeout | Int, timeout interval, in seconds. The value `0` indicates no timeout.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- If this API is not called, no timeout occurs by default. If this API is called multiple times in a process, the last configured interval is used.
- You can call this API to set the timeout interval after [acl.init](../init/function-init.md) is called for initialization in a process. Tasks delivered by calling [acl.rt.stream_wait_event](function-stream_wait_event.md) in the process can wait within the configured timeout interval.

    [acl.rt.stream\_wait\_event](function-stream_wait_event.md) is an asynchronous API. When called, it delivers tasks, but not execute them. Therefore, if the wait time exceeds the configured timeout interval, an error is returned after [acl.rt.synchronize\_stream](../stream/function-synchronize_stream.md) is called.
