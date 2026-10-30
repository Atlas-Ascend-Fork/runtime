# Function: get\_tensor\_desc\_name

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

Obtains the name of a tensor description.

## Prototype

- **C Prototype**

    ```c
    const char *aclGetTensorDescName(aclTensorDesc *desc)
    ```

- **Python Function**

    ```python
    name = acl.get_tensor_desc_name(desc)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| desc | Int, pointer address of the `aclTensorDesc` type. Call [acl.create_tensor_desc](function-create_tensor_desc.md) to create data of the `aclTensorDesc` type in advance.|

## Return Values

| Return Value| Description|
| --- | --- |
| name | Str, tensor description name.|
