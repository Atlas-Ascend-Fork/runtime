# Function: stream\_abort

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

Stops tasks that are being executed in a specified stream and discards tasks that have been delivered but not executed in the specified stream. New tasks delivered to the specified stream do not take effect during the execution of this API.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtStreamAbort(aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret = acl.rt.stream_abort(stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| stream | Int, stream with tasks to be cleared.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- If other streams depend on the stream specified in this API (for example, two streams are synchronized by calling [acl.rt.record\_event](../event/function-record_event.md) or [acl.rt.stream\_wait\_event](../event/function-stream_wait_event.md), the execution of other streams may be suspended. In this case, you need to explicitly call this API to clear tasks on other streams.
- If this API is called to clear tasks on a specified stream, and then a synchronization API (such as [acl.rt.synchronize\_stream](../stream/function-synchronize_stream.md) or [acl.rt.synchronize\_event](../event/function-synchronize_event.md)) is called, the synchronization API exits and returns the `ACL\_ERROR\_RT\_STREAM\_ABORT` error code.
