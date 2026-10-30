# Function: get\_tensor\_desc\_dim\_v2

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
    aclError aclGetTensorDescDimV2(const aclTensorDesc *desc, size_t index, int64_t *dimSize)
    ```

- **Python Function**

    ```python
    dim_size, ret = acl.get_tensor_desc_dim_v2(desc, index)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| desc | Int, pointer address of the `aclTensorDesc` type. Call [acl.create_tensor_desc](function-create_tensor_desc.md) to create data of the `aclTensorDesc` type in advance.|
| index | Int, sequence number of the dimension whose size is to be obtained, starting from 0. Value range: [0, Dimension count – 1]. Call [acl.get_tensor_desc_num_dims](function-get_tensor_desc_num_dims.md) to obtain the dimension count.<br>  |

## Return Values

| Return Value| Description|
| --- | --- |
| dim_size | Int, size of the dimension specified by `index` in the tensor description. If `-1` is returned, the dimension size is not determinable until runtime.|
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|

## Constraints

If the return value of [acl.get\_tensor\_desc\_num\_dims](function-get_tensor_desc_num_dims.md) is `ACL_UNKNOWN_RANK(0xFFFFFFFFFFFFFFFE)`, the dimension count is unknown. In this case, calling `acl.get_tensor_desc_dim_range_v2` cannot obtain the range of the specified dimension.
