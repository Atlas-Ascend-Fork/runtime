# Function: get\_input\_dynamic\_gear\_count

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

Obtains the number of dynamic dimension profiles supported by a model based on the model description.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlGetInputDynamicGearCount(const aclmdlDesc *modelDesc, size_t index, size_t *gearCount)
    ```

- **Python Function**

    ```python
    gear_count, ret = acl.mdl.get_input_dynamic_gear_count(model_desc, index)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_desc | Int, pointer address of the `aclmdlDesc` model description data. Call the [acl.mdl.create_desc](function-create_desc.md) API to create data of the aclmdlDesc type in advance.|
| index | Int, reserved. The value is fixed to<br> `1`.|

## Return Values

| Return Value| Description|
| --- | --- |
| gear_count | Int, number of dynamic shape profiles. For example, if the input tensor of a model is 4-dimensional and the dimension size profiles specified by the<br> `--dynamic_dims` parameter for model conversion are `1, 3, 224, 224; 2, 3, 224, 224; 1, 3, 256, 256`, the number of dynamic dimension profiles obtained by this API call is 3.|
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|

## Constraints

If no dynamic dimension profile is set during model building, this API call returns 0 dynamic dimension profiles. For details about model building, see [Model Building](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/others/acldevg/aclpythondevg_0030.html).
