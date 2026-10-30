# Function: get\_input\_dynamic\_dims

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

Obtains the dynamic dimensions supported by a model based on the model description.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlGetInputDynamicDims(const aclmdlDesc *modelDesc, size_t index, aclmdlIODims *dims, size_t gearCount)
    ```

- **Python Function**

    ```python
    dims_out, ret = acl.mdl.get_input_dynamic_dims(model_desc, index, gear_count)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_desc | Int, pointer address of the data of the `aclmdlDesc` type. Call the [acl.mdl.create_desc](function-create_desc.md) API to create data of the aclmdlDesc type in advance.|
| index | Int, reserved. The value is fixed to<br> `1`.|
| gear_count | Int, number of dynamic dimension profiles supported by the model, which needs to be obtained through the `acl.mdl.get_input_dynamic_gear_count` call in advance.|

## Return Values

| Return Value| Description|
| --- | --- |
| dims_out | List, an array for the dynamic shape. The `dims_out` parameter is a list. The number of elements in the list is the same as the number of inputs of the model. Each element in the list is a [aclmdlIODims](aclmdlIODims.md) dictionary. `dims` in the `aclmdlIODims` dictionary is a list. Each element in the list corresponds to a specific value in each dimension size choice. Example: dims_out, ret = acl.mdl.get_input_dynamic_dims (model_desc, -1, gear_count)|
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|

## Constraints

This API can be called only after the `--dynamic_dims` parameter is specified for model conversion.

Assume that a model has three inputs: `data` (1, 1, 40, -1), `label` (1, -1), and `mask` (-1, -1), where `-1` indicates a dynamic dimension. If `dynamic_dims` is set to `--dynamic_dims="20,20,1,1; 40,40,2,2; 80,60,4,4"` for model conversion, then the dynamic shape returned by this API call is as follows (Note that the `name` parameter in the `aclmdlIODims` dictionary is reserved currently):

- Profile 0:

    - In `aclmdlIODims`, `dimCount: 8` indicates that the inputs have eight dimensions altogether.

    - In `aclmdlIODims`, `dims: 1,1,40,20,1,20,1,1` indicates shape profile 0 of each input: `data` (1, 1, 40, 20), `label` (1, 20), and `mask` (1, 1).

- Profile 1:

    - In `aclmdlIODims`, `dimCount: 8` indicates that the inputs have eight dimensions altogether.

    - In `aclmdlIODims`, `dims: 1,1,40,40,1,40,2,2` indicates shape profile 1 of each input: `data` (1, 1, 40, 40), `label` (1, 40), and `mask` (2, 2).

- Profile 2:

    - In `aclmdlIODims`, `dimCount: 8` indicates that the inputs have eight dimensions altogether.

    - In `aclmdlIODims`, `dims: 1,1,40,80,1,60,4,4` indicates shape profile 2 of each input: `data` (1, 1, 40, 80), `label` (1, 60), and `mask` (4, 4).
