# Function: get\_tensor\_desc\_by\_index

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

Obtains a tensor description based on the specified index of an operator.

## Prototype

- **C Prototype**

    ```c
    aclTensorDesc *aclGetTensorDescByIndex(aclTensorDesc *desc, size_t index)
    ```

- **Python Function**

    ```python
    tensor_desc = acl.get_tensor_desc_by_index(desc, index)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| desc | Int, pointer address of the tensor description data. Call [acl.mdl.create_and_get_op_desc](function-create_and_get_op_desc.md) to obtain the tensor description of all inputs or all outputs of the operator as the input of this API.|
| index | Int, sequence number of the dimension whose size is to be obtained, starting from 0. Value range: [0, Operator input or output count – 1]. Call [acl.mdl.create_and_get_op_desc](function-create_and_get_op_desc.md) to obtain the operator input or output count.<br>  |

## Return Values

| Return Value| Description|
| --- | --- |
| tensor_desc | Int, pointer address of the tensor description of a specified input or output.|
