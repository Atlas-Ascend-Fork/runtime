# Function: create\_dataset

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

Creates data of the `aclmdlDataset` type.

This data type is used to describe input and output data during model inference. A model may have multiple inputs or outputs, and data of type `aclDataBuffer` is used to describe the buffer address and buffer size of each input or output.

To destroy data of the `aclmdlDataset` type, see [Function: destroy\_dataset](function-destroy_dataset.md).

## Prototype

- **C Prototype**

    ```c
    aclmdlDataset *aclmdlCreateDataset()
    ```

- **Python Function**

    ```python
    mdl_dataset = acl.mdl.create_dataset()
    ```

## Parameters

None

## Return Values

| Return Value| Description|
| --- | --- |
| mdl_dataset | Int, pointer address of the `aclmdlDataset` type.|
