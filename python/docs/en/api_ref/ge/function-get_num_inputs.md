# Function: get\_num\_inputs

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

Obtains the number of model inputs based on data of the `aclmdlDesc` type.

## Prototype

- **C Prototype**

    ```c
    size_t aclmdlGetNumInputs(aclmdlDesc *modelDesc)
    ```

- **Python Function**

    ```python
    size = acl.mdl.get_num_inputs(model_desc)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_desc | Int, pointer address of the data of the `aclmdlDesc` type. Call the [acl.mdl.create_desc](function-create_desc.md) API to create data of the aclmdlDesc type in advance.|

## Return Values

| Return Value| Description|
| --- | --- |
| size | Int, number of model inputs.|
