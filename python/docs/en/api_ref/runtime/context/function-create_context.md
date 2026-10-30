# Function: create\_context

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

Explicitly creates a context in the calling process or thread.

If [acl.rt.set\_device](../device/function-set_device.md) is not called in the application, when acl.rt.create\_context is called for the first time, the system binds a default stream to the device based on the device ID passed to this API. (A device is bound to only one default stream.) Therefore, when the acl.rt.create\_context API is called for the first time, the number of occupied streams is calculated as follows: Number of occupied streams = Number of default streams bound to the device + Number of streams contained in the context.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtCreateContext(aclrtContext *context, int32_t deviceId)
    ```

- **Python Function**

    ```python
    context, ret = acl.rt.create_context(device_id)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| device_id | Int, ID of the device for which the context is to be created.|

## Return Values

| Return Value| Description|
| --- | --- |
| context | Int, pointer address of the created context.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

The following application scenarios are supported:

- If [acl.rt.create\_context](function-create_context.md) is not called to explicitly create a context, the system uses the default context, which is created implicitly when [acl.rt.set\_device](../device/function-set_device.md) is called.
  - Implicit context creation: applies to simple apps with low complicity of interaction logic. However, in multithreaded programming, the execution result depends on the thread scheduling sequence.
  - Explicit context creation: applies to large apps with complex interaction logic, offering better app readability and maintainability.

- If a device is specified in a process, multiple threads in the process can share the context explicitly created on the device by calling [acl.rt.create\_context](function-create_context.md).
- If multiple contexts are created in a process (the number of contexts is related to the number of streams, which is limited. For details, see [acl.rt.create\_stream](../stream/function-create_stream.md)), the current thread can use only one context at a time. You are advised to call [acl.rt.set\_context](../context/function-set_context.md) to specify the context of the current thread to improve app maintainability.

## Reference

For details about the API call process and example, see "Runtime Resource Allocation and Deallocation" in "Application Development (Python)".
