# Function: set\_aipp\_by\_input\_index

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

Sets the AIPP attributes for model inference based on the index of the model input in the dynamic AIPP scenario.

Dynamic AIPP provides the following functions and they are executed in the exact sequence: Cropping -> CSC -> Mean subtraction/normalization -> Padding.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlSetAIPPByInputIndex(uint32_t modelId, aclmdlDataset *dataset, size_t index, const aclmdlAIPP *aippParmsSet)
    ```

- **Python Function**

    ```python
    ret = acl.mdl.set_aipp_by_input_index(model_id, dataset_in, index, aipp)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_id | Int, model ID. After the model loading API (such as [acl.mdl.load_from_file](function-load_from_file.md) or [acl.mdl.load_from_mem](function-load_from_mem.md)) is successfully called, the model ID is returned. The ID is used as the input of this API.|
| dataset_in | Int, pointer address of the input data for model inference. Data of type `aclmdlDataset` describes the input data for model inference, while data of type `aclDataBuffer` describes the input buffer size and address. For details, see [acl.mdl.load_from_file](function-load_from_file.md).|
| index | Int, index of the dynamic AIPP input. If the input is not associated with a dynamic AIPP input, an error is reported. Call [acl.mdl.get_aipp_type](function-get_aipp_type.md) to query whether a specified model input has an associated dynamic AIPP input. If yes, the `index` argument passed to this API call is the same as that of [acl.mdl.get_aipp_type](function-get_aipp_type.md). If no, you do not need to set dynamic AIPP attributes.|
| aipp | Int, pointer address of the dynamic AIPP parameter object. Call the [acl.mdl.create_aipp](function-create_aipp.md) API to create data of the `aclmdlAIPP` type in advance.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Constraints

- The image size after dynamic AIPP processing must be the same as that defined by the input shape required by the original model.

- In batched inference scenarios, the image size after dynamic AIPP is calculated based on the configuration of each batch. After dynamic AIPP, the output image size must be consistent across batches. Table 1 describes the formulas for calculating the result image size.

- After image cropping, resizing, or padding, the width and height of the image are verified as follows. `aippOutputW` and `aippOutputH` indicate the width and height of the output image, respectively. Other parameters are the input parameters of the `acl.mdl.set_aipp_srcImage_size`, `acl.mdl.set_aipp_scf_params`, `acl.mdl.set_aipp_crop_params` and `acl.mdl.set_aipp_padding_params` APIs. For details, see Table 1.

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

## Reference

For the API call example, see [API Calling Process](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/others/acldevg/aclpythondevg_0069.html).
