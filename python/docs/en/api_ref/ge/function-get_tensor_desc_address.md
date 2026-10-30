# Function: get\_tensor\_desc\_address

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

Obtains the tensor pointer address of a specified operator input or output.

## Prototype

- **C Prototype**

    ```c
    void *aclGetTensorDescAddress(const aclTensorDesc *desc)
    ```

- **Python Function**

    ```python
    addr = acl.get_tensor_desc_address(desc)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| desc | Int, pointer address of the tensor description. Call [acl.get_tensor_desc_by_index](function-get_tensor_desc_by_index.md) to obtain the tensor description of all inputs or all outputs of the operator as the input of this API.|

## Return Values

| Return Value| Description|
| --- | --- |
| addr | Int, tensor pointer address of a specified operator input or output.|
