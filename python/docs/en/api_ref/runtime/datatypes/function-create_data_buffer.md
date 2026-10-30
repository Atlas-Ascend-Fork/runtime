# Function: create\_data\_buffer

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

Creates data of the `aclDataBuffer` type to describe the buffer address and size.

To destroy data of the `aclDataBuffer` type, see [Function: destroy_data_buffer](function-destroy_data_buffer.md).

## Prototype

- **C Prototype**

    ```c
    aclDataBuffer *aclCreateDataBuffer(void *data, size_t size)
    ```

- **Python Function**

    ```python
    output = acl.create_data_buffer(data, size)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| data | Int, pointer address of `aclDataBuffer` data. `data` can be set to `0`, indicating that an empty data type is created. In this case, the value of `size` must be set to `0`.<br>The memory needs to be managed by the user. Call the [acl.rt.malloc](../memory/function-malloc.md) or [acl.rt.free](../memory/function-free.md) API to allocate or free memory, or call the [acl.rt.malloc_host](../memory/function-malloc_host.md) or [acl.rt.free_host](../memory/function-free_host.md) API to allocate or free memory.|
| size | Int, memory size. If you need to use an empty tensor, set the minimum memory size to 1 byte during memory allocation to ensure normal running of subsequent services.|

## Return Values

| Return Value| Description|
| --- | --- |
| output | Int, pointer address of the output `aclDataBuffer`.|
