# Function: get\_tensor\_desc\_dim

**Note: This API will be deprecated in later versions. Use the [acl.get\_tensor\_desc\_dim\_v2](function-get_tensor_desc_dim_v2.md) API instead.**

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

Obtains the size of a specified dimension of a tensor description.

## Prototype

- **C Prototype**

    ```c
    int64_t aclGetTensorDescDim(const aclTensorDesc *desc, size_t index)
    ```

- **Python Function**

    ```python
    dim_size = acl.get_tensor_desc_dim(desc, index)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| desc | Int, pointer address of the `aclTensorDesc` type. Call [acl.create_tensor_desc](function-create_tensor_desc.md) to create data of the `aclTensorDesc` type in advance.|
| index | Int, sequence number of the dimension whose size is to be obtained, starting from 0. Value range: [0, Dimension count – 1]. Call `acl.get_tensor_desc_dim` to obtain the dimension count.<br>  |

## Return Values

| Return Value| Description|
| --- | --- |
| dim_size | Int, size of a specified dimension of a tensor description.|
