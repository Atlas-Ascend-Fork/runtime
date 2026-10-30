# Function: create\_tensor\_desc

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

Creates data of the `aclTensorDesc` type as a tensor description, describing the data type, shape, and format of a tensor.

To destroy data of the `aclTensorDesc` type, see [Function: destroy\_tensor\_desc](function-destroy_tensor_desc.md).

## Prototype

- **C Prototype**

    ```c
    aclTensorDesc *aclCreateTensorDesc(aclDataType dataType, int numDims, const int64_t *dims, aclFormat format)
    ```

- **Python Function**

    ```python
    tensor_desc = acl.create_tensor_desc(data_type, dims, format)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| data_type | Int, data type of the tensor description.|
| dims | List, size of the specified dimensions of the tensor description. `dims` is a list of ints. Each element in the list indicates the size of each dimension in the tensor. If the value of an element is `0`, the tensor is empty. If you need to use an empty tensor, set the minimum memory size to 1 byte during memory allocation to ensure normal running of subsequent services.|
| format | Int, format of the tensor description.|

## Return Values

| Return Value| Description|
| --- | --- |
| tensor_desc | Int, address object for creating the tensor description.|
