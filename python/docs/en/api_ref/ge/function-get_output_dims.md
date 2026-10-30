# Function: get\_output\_dims

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

Obtains tensor dimension information of an output based on the model description.

- Static-shape: This API is used to obtain the shape of the output tensors of a model.
- In the dynamic-shape scenario, this API is used to obtain the shape of the maximum batch/image size profile.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlGetOutputDims(const aclmdlDesc *modelDesc, size_t index, aclmdlIODims *dims)
    ```

- **Python Function**

    ```python
    dims, ret = acl.mdl.get_output_dims(model_desc, index)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_desc | Int, pointer address of the data of the `aclmdlDesc` type. Call the [acl.mdl.create_desc](function-create_desc.md) API to create data of the aclmdlDesc type in advance.|
| index | Int, sequence number of the input to obtain, indexed starting at 0|

## Return Values

| Return Value| Description|
| --- | --- |
| dims | Dict, maximum supported combinations for dynamic-batch or dynamic-size scenarios based on the dictionary array. For details, see [aclmdlIODims](aclmdlIODims.md). In dynamic batch/image size scenarios, if the batch size is `-1` or the width and height are `-1`, the tensor shape is dynamic. For example, if the format of the input tensor is NCHW, then the tensor shape [-1,3,224,224] indicates that the batch size is dynamic, and the tensor shape [1,3,-1,-1] indicates that the image size is dynamic. The italic numbers are examples only. If the length of a tensor name exceeds 127, the API replaces it with the format `acl_modelId_${id}_input_${index}_${random string}` when outputting `dims.name`. If the converted name conflicts with an existing tensor name, a random string (`_${random string}`) is appended; otherwise, no random string is added. The API also maintains a mapping between the converted and original names. You can call [acl.mdl.get_tensor_real_name](function-get_tensor_real_name.md) to retrieve the original name by passing the converted one (or simply pass the original name to get it back unchanged). For a tensor name that has a length of 127 or fewer, `dims.name` directly reflects the original tensor name.|
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|
