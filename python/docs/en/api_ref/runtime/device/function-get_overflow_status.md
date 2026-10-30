# Function: get\_overflow\_status

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

Queries the overflow status of tasks on all streams in the current device and copies the status value to the device memory that you requested. This is an asynchronous API.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtGetOverflowStatus(void *outputAddr, size_t outputSize, aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret = acl.rt.get_overflow_status(outputAddr, outputSize, stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| outputAddr | Int, device memory allocated by the user. It must be allocated by calling [acl.rt.malloc](../memory/function-malloc.md). To view data on the host, call [acl.rt.memcpy](../memory/function-memcpy.md) or [acl.rt.memcpy_async](../memory/function-memcpy_async.md) to transfer data from the device to the host.|
| outputSize | Int, size of the device memory to be allocated, in bytes. The fixed size is 64 bytes.|
| stream | Int, pointer address of a stream to deliver an overflow status query task.|

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
