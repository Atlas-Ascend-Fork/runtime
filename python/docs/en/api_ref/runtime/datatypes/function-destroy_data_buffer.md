# Function: destroy\_data\_buffer

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

Destroys data of the `aclDataBuffer` type.

For aclDataBuffer data created by calling [acl.create\_data\_buffer](function-create_data_buffer.md), the input data buffer needs to be freed by you.

## Prototype

- **C Prototype**

    ```c
    aclError aclDestroyDataBuffer(const aclDataBuffer *dataBuffer)
    ```

- **Python Function**

    ```python
    ret = acl.destroy_data_buffer(data_buffer)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| data_buffer | Int, pointer address of `aclDataBuffer`.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br>`0`: success<br>If [other values](../datatypes/aclError.md) are returned, the operation fails.|
