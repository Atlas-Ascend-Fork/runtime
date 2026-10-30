# Function: set\_input\_dynamic\_dims

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

Sets the runtime dimensions for model inference before model execution, assuming that the input shape is dynamic and the input data format is ND (supporting any format).

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlSetInputDynamicDims(uint32_t modelId, aclmdlDataset *dataset, size_t index, const aclmdlIODims *dims)
    ```

- **Python Function**

    ```python
    ret = acl.mdl.set_input_dynamic_dims(model_id, dataset_in, index, dims)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| modelId | Int, model ID. After the model loading API (such as [acl.mdl.load_from_file](function-load_from_file.md) or [acl.mdl.load_from_mem](function-load_from_mem.md)) is successfully called, the model ID is returned. The ID is used as the input of this API.|
| dataset | Int, model input data. Data of type `aclmdlDataset` describes the input data for model inference, while data of type `aclDataBuffer` describes the input buffer size and address. For details, see [acl.mdl.load_from_file](function-load_from_file.md).|
| index | Int, index of the dynamic dimension size input. The input index is obtained by the [acl.mdl.get_input_index_by_name](function-get_input_index_by_name.md) API. The input name is fixed at `ascend_mbatch_shape_data`.|
| dims | Dict, dimension size for model inference. For details, see [aclmdlIODims](aclmdlIODims.md). You can call the `acl.mdl.get_input_dynamic_dims` API to obtain the number of dimension size profiles as well as the size of each profile supported by the model. For example, if `input_shape="data:1,1,40,-1;label:1,-1;mask:-1,-1", dynamic_dims="20,20,1,1; 40,40,2,2; 80,60,4,4` are passed for model conversion and the actual input shape is (1, 1, 40, 20, 1, 20, 1, 1), the example `dims` input is as follows (with the `name` field reserved): `dims = {'dimCount': 8, 'name': '', 'dims': [1,1,40,20,1,20,1,1]}`|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Reference

For the API calling process and example, see [Dynamic Batch/Dynamic Image Size/Dynamic Dimension (Setting Multi-Dimension Profiles)](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/others/acldevg/aclpythondevg_0046.html).
