# Function: set\_dataset\_tensor\_desc

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

Sets the tensor description of the dynamic-shape model input or output before the model is executed.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlSetDatasetTensorDesc(aclmdlDataset *dataset, aclTensorDesc *tensorDesc, size_t index)
    ```

- **Python Function**

    ```python
    dataset, ret = acl.mdl.set_dataset_tensor_desc(dataset, tensor_desc, index)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| dataset | Int, address of `aclmdlDataset` to be added with `aclTensorDesc`, indicating the input or output data structure for model execution. Call [acl.mdl.create_dataset](function-create_dataset.md) to create data of the `aclmdlDataset` type, and then call [acl.mdl.add_dataset_buffer](function-add_dataset_buffer.md) to add `aclDataBuffer` to `aclmdlDataset`.|
| tensor_desc | Int, address of `aclTensorDesc`, indicating the input or output tensor description for model execution. Call [acl.create_tensor_desc](function-create_tensor_desc.md) to create data of the `aclTensorDesc` type. In the model input or output tensor description, only the shape configurations take effect, which correspond to the `numDims` parameter that specifies the dimension count and the `dims` parameter that specifies the dimension sizes passed to the [acl.create_tensor_desc](function-create_tensor_desc.md) call. The data type and format configurations are invalid. The configured dimension count and sizes must be within the shape range specified at model build. For details, see the model build section.|
| index | Int, input or output index. When a model has multiple inputs and outputs, call [acl.mdl.get_input_name_by_index](function-get_input_name_by_index.md) and [acl.mdl.get_output_name_by_index](function-get_output_name_by_index.md) to obtain the input or output names and set the `index` accordingly.|

## Return Values

| Return Value| Description|
| --- | --- |
| dataset | Int, address of `aclmdlDataset` to be added with `aclTensorDesc`, indicating the input or output data structure for model execution.|
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|

## Constraints

For the same model, only one of the [acl.mdl.set\_dynamic\_batch\_size](function-set_dynamic_batch_size.md), [acl.mdl.set\_dynamic\_hw\_size](function-set_dynamic_hw_size.md), [acl.mdl.set\_input\_dynamic\_dims](function-set_input_dynamic_dims.md), and [acl.mdl.set\_dataset\_tensor\_desc](function-set_dataset_tensor_desc.md) APIs can be called.
