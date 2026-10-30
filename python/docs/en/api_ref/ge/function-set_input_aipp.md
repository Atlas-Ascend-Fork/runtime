# Function: set\_input\_aipp

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

Sets the AIPP attributes for model inference based on the index of the dynamic AIPP input in the dynamic AIPP scenario.

Dynamic AIPP provides the following functions and they are executed in the exact sequence: Cropping -> CSC -> Mean subtraction/normalization -> Padding.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlSetInputAIPP(uint32_t modelId, aclmdlDataset *dataset, size_t index, const aclmdlAIPP *aippParmsSet)
    ```

- **Python Function**

    ```python
    ret = acl.mdl.set_input_aipp(model_id, dataset, index, aipp_parms_set)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_id | Int, model ID, which can be obtained after the model is successfully loaded by calling the following APIs:<br> [acl.mdl.load_from_file](function-load_from_file.md)<br> [acl.mdl.load_from_mem](function-load_from_mem.md)<br> [acl.mdl.load_from_file_with_mem](function-load_from_file_with_mem.md)<br> [acl.mdl.load_from_mem_with_mem](function-load_from_mem_with_mem.md) |
| dataset | Int, pointer address of a model's input data. Data of type `aclmdlDataset` describes the input data for model inference, while data of type `aclDataBuffer` describes the input buffer size and address.|
| index | Int, input index of the dynamic AIPP input.<br> When the model has more than one dynamic AIPP input, you can call [acl.mdl.get_aipp_type](function-get_aipp_type.md) to obtain the specified input index.<br> To ensure forward compatibility, if there is only one dynamic AIPP input, you can call [acl.mdl.get_input_index_by_name](function-get_input_index_by_name.md) to obtain the input index. The input name is fixed to `ascend_dynamic_aipp_data`.|
| aipp_parms_set | Int, pointer address of the dynamic AIPP configuration object. The `aclmdlAIPP` data must be created by the [acl.mdl.create_aipp](function-create_aipp.md) call in advance.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|

## Constraints

- The image size after dynamic AIPP processing must be the same as that defined by the input shape required by the original model.
- In the scenario with the batch size greater than 1, the image size after dynamic AIPP are calculated based on the configuration of each batch. After dynamic AIPP, the output image size must be consistent across batches. Table 1 describes the formulas for calculating the result image size.
- After image cropping, resizing, or padding, the rules for verifying the image size after dynamic AIPP are as follows. `aippOutputW` and `aippOutputH` indicate the width and height of the AIPP output image, respectively. Other parameters are the input parameters of the [acl.mdl.set\_aipp\_src\_image\_size](function-set_aipp_src_image_size.md), [acl.mdl.set\_aipp\_crop\_params](function-set_aipp_crop_params.md), and [acl.mdl.set\_aipp\_padding\_params](function-set_aipp_padding_params.md) APIs.

## Reference

For the API call example, see [Dynamic AIPP (Single Dynamic AIPP Input)](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/others/acldevg/aclpythondevg_0041.html).

**Table 1** Formulas for calculating the image size after dynamic AIPP

| Cropping| Scaling| Padding| Output Width and Height|
| --- | --- | --- | --- |
| No| No| No| aippOutputW = srcImageSizeW aippOutputH = srcImageSizeH |
| Yes| No| No| aippOutputW = cropSizeW aippOutputH = cropSizeH |
| Yes| Yes| No| aippOutputW = scfOutputSizeW aippOutputH = scfOutputSizeH |
| Yes| No| Yes| aippOutputW = cropSizeW + paddingSizeLeft + paddingSizeRight aippOutputH = cropSizeH + paddingSizeTop + paddingSizeBottom |
| No| No| Yes| aippOutputW = srcImageSizeW + paddingSizeLeft + paddingSizeRight aippOutputH = srcImageSizeH + paddingSizeTop + paddingSizeBottom |
| No| Yes| Yes| aippOutputW = scfOutputSizeW + paddingSizeLeft + paddingSizeRight aippOutputH = scfOutputSizeH + paddingSizeTop + paddingSizeBottom |
| No| Yes| No| aippOutputW = scfOutputSizeW aippOutputH = scfOutputSizeH |
| Yes| Yes| Yes| aippOutputW = scfOutputSizeW + paddingSizeLeft + paddingSizeRight aippOutputH = scfOutputSizeH + paddingSizeTop + paddingSizeBottom |
