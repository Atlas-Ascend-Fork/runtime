# Function: get\_input\_dims\_range

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

Obtains the dimension range of an input tensor based on the model description.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlGetInputDimsRange(const aclmdlDesc *modelDesc, size_t index, aclmdlIODimsRange *dimsRange)
    ```

- **Python Function**

    ```python
    dims_range, ret = acl.mdl.get_input_dims_range(model_desc, index)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_desc | Int, pointer to data of the `aclmdlDesc` type. Call the [create_desc](function-create_desc.md) API to create data of the `aclmdlDesc` type in advance.|
| index | Int, index of the input dimension information to be obtained, starting from 0.|

## Return Values

| Return Value| Description|
| --- | --- |
| dims_range | Dict, dictionary of input dimension information. See [aclmdlIODimsRange](aclmdlIODimsRange.md).<br> Returns the shape range when the dynamic shape is used and the shape range is configured. The dynamic dimension upper and lower limits are different, but the static dimension upper and lower limits are the same. For example, if `format` of the input tensor is `NCHW`, `dims` is [1, 3, 10–224, 10–300], the N and C dimensions are fixed values, and the H and W dimensions are dynamic ranges, then `aclmdlIODimsRange.rangeCount` is `4`, the `aclmdlIODimsRange.range` array contains four elements: {1,1}, {3, 3}, {10, 224} and {10, 300}.<br> This API is not supported in the dynamic shape scenario when rank data is configured. The `aclmdlIODimsRange.rangeCount` returns `0`.<br> In the static-shape scenario, the shape range is returned, but the upper and lower limits of each dimension are the same.|
| ret | Int, `0` on success; else, failure.|
