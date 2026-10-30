# Function: get\_cur\_output\_dims

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

Obtains the runtime shape of an output tensor based on the model description.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlGetCurOutputDims(const aclmdlDesc *modelDesc, size_t index, aclIODims *dims)
    ```

- **Python Function**

    ```python
    dims, ret = acl.mdl.get_cur_output_dims(model_desc, index)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_desc | Int, pointer address of the data of the `aclmdlDesc` type. Call the [acl.mdl.create_desc](function-create_desc.md) API to create data of the aclmdlDesc type in advance.|
| index | Int, index of the output whose dimensions to obtain, indexed from 0.|

## Return Values

| Return Value| Description|
| --- | --- |
| dims | Dict, runtime shape.<br>If the length of a tensor name exceeds 127, the API replaces it with the format `acl_modelId_${id}_input_${index}_${random string}` when outputting `dims.name`. If the converted name conflicts with an existing tensor name, a random string (`_${random string}`) is appended; otherwise, no random string is added. The API also maintains a mapping between the converted and original names. You can call [acl.mdl.get_tensor_real_name](function-get_tensor_real_name.md) to retrieve the original name by passing the converted one (or simply pass the original name to get it back unchanged). For a tensor name that has a length of 127 or fewer, `dims.name` directly reflects the original tensor name.|
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|

## Constraints

Currently, this API can be used to obtain the shape of the model output tensors only in the following scenarios:

- Set the batch size, resolution, or dimension value through model conversion to implement dynamic batch, dynamic image size, or dynamic dimension (ND format).
    - If you have set batch by calling [acl.mdl.set\_dynamic\_batch\_size](function-set_dynamic_batch_size.md), set the width and height of the input image by calling [acl.mdl.set\_dynamic\_hw\_size](function-set_dynamic_hw_size.md), or set the value of a dynamic dimension by calling [acl.mdl.set\_input\_dynamic\_dims](function-set_input_dynamic_dims.md), you can call this API to obtain the actual dimension information of the output tensor of a specified model.
    - If you have not called the [acl.mdl.set\_dynamic\_batch\_size](function-set_dynamic_batch_size.md), [acl.mdl.set\_dynamic\_hw\_size](function-set_dynamic_hw_size.md), or [acl.mdl.set\_input\_dynamic\_dims](function-set_input_dynamic_dims.md) API, you can call this API to obtain the maximum dimension information.

- Static-shape: This API is used to obtain the shape of the output tensors of a model.
