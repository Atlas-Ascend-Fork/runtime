# Function: destroy\_stream

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

Destroys a stream created by calling [acl.rt.create\_stream](../stream/function-create_stream.md) or [acl.rt.create\_stream\_with\_config](function-create_stream_with_config.md). If there are unfinished tasks on the stream, the stream is destroyed after the tasks are complete.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtDestroyStream(aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret = acl.rt.destroy_stream(stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| stream | Int, pointer address of the stream to be destroyed.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- Before calling [acl.rt.destroy\_stream](../stream/function-destroy_stream.md) to destroy a specified stream, call [acl.rt.synchronize\_stream](function-destroy_stream.md) to ensure that all tasks in the stream are complete.
- When calling [acl.rt.destroy\_stream](../stream/function-destroy_stream.md) to destroy a specified stream, ensure that the stream is in the current context.
- Before calling [acl.rt.destroy\_stream](../stream/function-destroy_stream.md) to destroy a specified stream, ensure that the stream is not being used by other APIs.

## Reference

For details about the API call process and example, see "Runtime Resource Allocation and Deallocation" and "Synchronous Wait" in "Application Development (Python)".
