# Function: create\_stream

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

Creates a stream in the calling process or thread.

This API does not allow for setting the stream priority. By default, streams are assigned the highest priority if none is specified. For details about how to set the priority when creating a stream, see [acl.rt.create\_stream\_with\_config](function-create_stream_with_config.md).

If the stream creation API is not explicitly called, each context corresponds to a default stream. The default stream is implicitly created by calling [acl.rt.set\_device](../device/function-set_device.md) or [acl.rt.create\_context](../context/function-create_context.md). The priority of the default stream cannot be set and is the highest priority. The default stream is suitable for simple applications without complex interaction logic. However, in multithread programming, the execution result depends on the thread scheduling sequence. Explicit stream creation **(recommended)** applies to large-scale applications with complex interaction logic, improving application readability and maintainability.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtCreateStream(aclrtStream *stream)
    ```

- **Python Function**

    ```python
    stream, ret = acl.rt.create_stream()
    ```

## Parameters

None

## Return Values

| Return Value| Description|
| --- | --- |
| stream | Int, pointer address of the created streamed.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- Each context corresponds to a default stream. The default stream is implicitly created by calling [acl.rt.set\_device](../device/function-set_device.md) or [acl.rt.create\_context](../context/function-create_context.md). The priority of the default stream cannot be set and is the highest priority. You are advised to use `aclrtCreateStream` to explicitly create a stream.
  - Implicit stream creation: applies to simple apps with low complexity of interaction logic. However, in multithreaded programming, the execution result depends on the thread scheduling sequence.
  - (Recommended) Explicit stream creation: applies to large apps with complex interaction logic, offering better app readability and maintainability.

- The maximum number of streams supported by hardware varies depending on the hardware model. If multiple streams (including the default stream) exist, only *N* streams can be explicitly created, where *N* = Maximum number of streams – Number of existing streams. For example, if the maximum number of streams is 1,024 and there are already two streams, you can only call this API to explicitly create 1,022 streams.
  <!-- npu="950,A3,910b" id7 -->
  - For Ascend 950PR&950DT, Atlas A3, and Atlas A2 products, the maximum number of streams is 1,984.
  <!-- end id7 -->
  <!-- npu="310b" id8 -->
  - For Atlas 200I/500 A2 inference products, the maximum number of streams is 512.
  <!-- end id8 -->
  <!-- npu="310p" id9 -->
  - For Atlas inference products, the maximum number of streams is 1,024.
  <!-- end id9 -->
  <!-- npu="910" id10 -->
  - For Atlas training products, the maximum number of streams is 2,024.

    In the multi-process scenario, if the total number of streams created at a time is close to 2,048, streams may fail to be created. In this case, you are advised to perform the following operations:

    (1) Clear redundant streams.

    (2) Adjust the code logic to create streams batch by batch. For example, create some streams in the first batch, then the second batch, and so on until the total number of streams is close to 2,048.

  <!-- end id10 -->

## Reference

For details about the API call process and example, see "Runtime Resource Allocation and Deallocation" in "Application Development (Python)".
