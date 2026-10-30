# Function: create\_binary

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

Creates data of the acl.rt.binary type. This data type is used to describe the binary information of an operator. Only Ascend C custom operators are supported.

To destroy data of the acl.rt.binary type, see [acl.rt.destroy\_binary](function-destroy_binary.md).

## Prototype

- **C Prototype**

    ```c
    aclrtBinary aclrtCreateBinary(const void *data, size_t dataLen)
    ```

- **Python Function**

    ```python
    binary = acl.rt.create_binary(data, data_len)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| data | Int, pointer address of the memory address for storing the operator binary file (.o file).|
| data_len | Int, memory size, in bytes.|

## Return Values

| Return Value| Description|
| --- | --- |
| binary | Int, pointer address of the acl.rt.binary type.|

## Constraints

In Ascend EP standard mode, allocate memory on the host for the data parameter. In Ascend RC mode or open Ctrl CPU mode, allocate memory on the device for the data parameter.
