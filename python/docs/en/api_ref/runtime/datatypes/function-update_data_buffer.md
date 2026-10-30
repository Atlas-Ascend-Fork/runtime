# Function: update\_data\_buffer

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

Updates the memory and size of data in aclDataBuffer.

After `aclDataBuffer` is updated, free the `aclDataBuffer` memory when it is no longer needed to avoid memory leak.

## Prototype

- **C Prototype**

    ```c
    aclError aclUpdateDataBuffer(aclDataBuffer *dataBuffer, void *data, size_t size)
    ```

- **Python Function**

    ```python
    ret = acl.update_data_buffer(data_buffer, data, size)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| data_buffer | Int, pointer address of the aclDataBuffer type.<br>Call the [acl.create_data_buffer](function-create_data_buffer.md) API to create data of the aclDataBuffer type in advance.<br>The memory needs to be managed by the user. Call the [acl.rt.malloc](../memory/function-malloc.md) or [acl.rt.free](../memory/function-free.md) API to allocate or free memory, or call the [acl.rt.malloc_host](../memory/function-malloc_host.md) or [acl.rt.free_host](../memory/function-free_host.md) API to allocate or free memory.|
| data | Int, pointer address for storing the data memory address.|
| size | Int, memory size, in bytes. If an empty tensor is needed, allocate at least 1 byte buffer.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br>`0`: success<br>If [other values](../datatypes/aclError.md) are returned, the operation fails.|
