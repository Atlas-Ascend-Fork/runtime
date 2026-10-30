# Function: unsubscribe\_report

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

Unsubscribes from a thread in the asynchronous scenario. The callback function in the stream will no longer be processed by the thread.

**This API must work with the following APIs** to implement the callback function in asynchronous scenarios:

1. Create a thread. Call [acl.rt.process\_report](function-process_report.md) in the thread function to set the timeout interval (cyclic calling is required), and wait for the function callback task delivered by [acl.rt.launch\_callback](function-launch_callback.md).
2. Call [acl.rt.subscribe\_report](function-subscribe_report.md) to bind the thread created in step 1 to the stream. The callback task delivered by the stream is executed in the bound thread.
3. Execute an asynchronous job (for example, an asynchronous inference job) on the specified stream.
4. Define and implement the callback function, call acl.rt.launch\_callback to deliver a callback task in the task queue of the stream, and trigger the thread to process the callback function subscribed by acl.rt.subscribe\_report. Each time acl.rt.launch\_callback is called, a callback task is delivered.
5. Call [acl.rt.unsubscribe\_report](function-unsubscribe_report.md) to unsubscribe from threads and unbind threads from streams after all asynchronous tasks are executed.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtUnSubscribeReport(uint64_t threadId, aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret = acl.rt.unsubscribe_report(thread_id, stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| thread_id | Int, thread ID.|
| stream | Int, pointer address of the stream to be processed.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
