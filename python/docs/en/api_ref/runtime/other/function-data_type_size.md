# Function: data\_type\_size

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

Obtains the size of the [aclDataType](../datatypes/aclDataType.md) data, in bytes.

## Prototype

- **C Prototype**

    ```c
    size_t aclDataTypeSize(aclDataType dataType)
    ```

- **Python Function**

    ```python
    size = acl.data_type_size(data_type)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| data_type | Int, size of the `aclDataType` data to be obtained.|

## Return Values

| Return Value| Description|
| --- | --- |
| size | Int, size of the `aclDataType` data, in bytes.|
