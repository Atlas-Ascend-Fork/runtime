# Function: memcpy\_async\_with\_desc

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
- Atlas training products: Not supported
<!-- end id6 -->

## Function

Copies memory using a memory copy descriptor (level-2 pointer mode).

This API is asynchronous. The API call delivers a task rather than executes a task. After this API is called, call the synchronization API (for example, [acl.rt.synchronize\_stream](../stream/function-synchronize_stream.md)) to ensure that the task is complete. Otherwise, unknown problems may occur, such as training or inference exceptions, device disconnection, or card disconnection.

This API must be used together with the following APIs to implement memory copy:

- Call [acl.rt.get\_memcpy\_desc\_size](function-get_memcpy_desc_size.md) to obtain the memory size required by the memory descriptor.
- Allocate the device memory for storing the memory descriptor.
- Allocate the source and destination memory for storing the data before and after the copy.
- Call [acl.rt.set\_memcpy\_desc](function-set_memcpy_desc.md) to set information such as the source and destination memory addresses in the memory descriptor.
- Call [acl.rt.memcpy\_async\_with\_desc](function-memcpy_async_with_desc.md) to copy the memory.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtMemcpyAsyncWithDesc(void *desc, aclrtMemcpyKind kind, aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret = acl.rt.memcpy_async_with_desc(desc, kind, stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| desc | Int, pointer to the memory copy descriptor address on the device. Call [acl.rt.set_memcpy_desc](function-set_memcpy_desc.md) to set the memory copy descriptor, and then pass the address pointer of the memory copy descriptor to this API as an argument.|
| kind | Int, memory copy type. Currently, only `ACL_MEMCPY_INNER_DEVICE_TO_DEVICE` is supported, indicating memory copy within a device.|
| stream | Int, stream.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
