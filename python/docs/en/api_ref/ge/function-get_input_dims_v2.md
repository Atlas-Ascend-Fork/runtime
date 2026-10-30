# Function: get\_input\_dims\_v2

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

Obtains dimension information of the input tensor based on the model description.

If the model contains static AIPP configuration, call `acl.mdl.get_input_dims` or `acl.mdl.get_input_dims_v2` to obtain the shape as required. The differences between the two APIs are as follows:

- `acl.mdl.get_input_dims`: The obtained dimension values are consistent with those of the input image. For details, see Table 1.

- `acl.mdl.get_input_dims_v2`: The obtained value of the H dimension is that of the input image multiplied by a coefficient, and the value of the C dimension varies according to the image format. For details, see Table 1 in `acl.mdl.get_input_dims_v2`. The multiplied dimension values are consistent with those obtained by calling `acl.mdl.get_input_size_by_index`.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlGetInputDimsV2(const aclmdlDesc *modelDesc, size_t index, aclmdlIODims *dims)
    ```

- **Python Function**

    ```python
    dims, ret = acl.mdl.get_input_dims_v2(model_desc, index)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_desc | Int, pointer address of the data of the `aclmdlDesc` type. Call the [acl.mdl.create_desc](function-create_desc.md) API to create data of the aclmdlDesc type in advance.|
| index | Int, sequence number of the input whose `dims` is to be obtained, starting at 0.|

## Return Values

| Return Value| Description|
| --- | --- |
| dims | Dict, maximum supported combinations for dynamic-batch or dynamic-size scenarios based on the dictionary array. For details, see [aclmdlIODims](aclmdlIODims.md). In dynamic batch/image size scenarios, if the batch size is `1` or the width and height are<br> `1`, the tensor shape is dynamic. For example, if the format of the input tensor is NCHW, then the tensor shape [-1,3,224,224] indicates that the batch size is dynamic, and the tensor shape [1,3,-1,-1] indicates that the image size is dynamic. The italic numbers are examples only. If the length of a tensor name exceeds 127, the API replaces it with the format `acl_modelId_${id}_input_${index}_${random string}` when outputting `dims.name`. If the converted name conflicts with an existing tensor name, a random string (`_${random string}`) is appended; otherwise, no random string is added. The API also maintains a mapping between the converted and original names. You can call [acl.mdl.get_tensor_real_name](function-get_tensor_real_name.md) to retrieve the original name by passing the converted one (or simply pass the original name to get it back unchanged). For a tensor name that has a length of 127 or fewer, `dims.name` directly reflects the original tensor name.|
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|

**Table 1** Mapping between the supported image formats and dims shapes with dynamic AIPP

| Image Format| Format| Shape|
| --- | --- | --- |
| YUV420SP_U8 | NHWC | "n,h*1.5,w,1" |
| XRGB8888_U8 | NHWC | "n,h,w,4" |
| RGB888_U8 | NHWC | "n,h,w,3" |
| YUV400_U8 | NHWC | "n,h,w,1" |
| ARGB8888_U8 | NHWC | "n,h,w,4" |
| YUYV_U8 | NHWC | "n,h,w,2" |
| YUV422SP_U8 | NHWC | "n,h*2,w,1" |
| AYUV444_U8 | NHWC | "n,h,w,4" |
