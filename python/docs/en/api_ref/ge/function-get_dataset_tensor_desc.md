# Function: get\_dataset\_tensor\_desc

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
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas inference products: Supported
<!-- end id5 -->
<!-- npu="910" id6 -->
- Atlas training products: Supported
<!-- end id6 -->

## Function

Obtains the tensor description of the specified input or output from the data of the `aclmdlDataset` type (used to describe the input and output data during model inference) after the model is executed if the input or output shape of a model is dynamic.

**Typical scenario**: If the input shape of a model is dynamic, call [acl.mdl.set\_dataset\_tensor\_desc](function-set_dataset_tensor_desc.md) to set the tensor description before the model is executed. After the model is executed, call `acl.mdl.get_dataset_tensor_desc` to obtain the tensor description of the dynamic output of the model.

## Prototype

- **C Prototype**

    ```c
    aclTensorDesc *aclmdlGetDatasetTensorDesc(const aclmdlDataset *dataset, size_t index)
    ```

- **Python Function**

    ```python
    tensorDesc = acl.mdl.get_dataset_tensor_desc(dataset, index)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| dataset | Int, pointer address of the input or output data structure for model execution.|
| index | Int, input or output index. When a model has multiple inputs and outputs, call [acl.mdl.get_input_name_by_index](function-get_input_name_by_index.md) and [acl.mdl.get_output_name_by_index](function-get_output_size_by_index.md) to obtain the input or output names and set the index accordingly.|

## Return Values

| Return Value| Description|
| --- | --- |
| tensor_desc | Int, pointer address of the tensor description of the specified input or output.|
