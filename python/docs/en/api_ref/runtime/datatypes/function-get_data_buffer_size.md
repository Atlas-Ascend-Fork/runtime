# Function: get\_data\_buffer\_size

## Applicable Products

<!-- npu="950" id1 -->
- Ascend 950PR&950DT products: Supported
<!-- end id1 -->
<!-- npu="A3" id2 -->
- Atlas A3 products: supported
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

Obtains the memory size of data of the `aclDataBuffer` type, in bytes.

>NOTICE
>This API will be deprecated in later versions. Use the [acl.get\_data\_buffer\_size\_v2](function-get_data_buffer_size_v2.md) API instead.

## Prototype

- **C Prototype**

    ```c
    size_t aclGetDataBufferSize(const aclDataBuffer *dataBuffer)
    ```

- **Python Function**

    ```python
    size = acl.get_data_buffer_size(data_buffer)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| data_buffer | Int, pointer address of `aclDataBuffer`.<br>Call the [acl.create_data_buffer](function-create_data_buffer.md) API to create data of the aclDataBuffer type in advance.|

## Return Values

| Return Value| Description|
| --- | --- |
| size | Int, memory size of data of the `aclDataBuffer` type.|
