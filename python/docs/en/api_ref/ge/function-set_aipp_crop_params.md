# Function: set\_aipp\_crop\_params

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

Sets scaling parameters in the dynamic AIPP scenario.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlSetAIPPCropParams(aclmdlAIPP *aippParmsSet, int8_t cropSwitch, int32_t cropStartPosW, int32_t cropStartPosH, int32_t cropSizeW, int32_t cropSizeH,uint64_t batchIndex)
    ```

- **Python Function**

    ```python
    ret = acl.mdl.set_aipp_crop_params(aipp_parms_set, crop_switch, crop_start_pos_w, crop_start_pos_h, crop_size_w, crop_size_h, batch_index)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| aipp_parms_set | Int, pointer address of the dynamic AIPP configuration object. The `aclmdlAIPP` data must be created by the [acl.mdl.create_aipp](function-create_aipp.md) call in advance.|
| crop_switch | Int, whether to crop an image.<br> Value range:<br> 0: The image is not cropped. When `cropSwitch` is set to `0`, `cropStartPosW`, `cropStartPosH`, `cropSizeW`, and `cropSizeH` are invalid.<br> `1`: The image is cropped.|
| crop_start_pos_w | Int, horizontal coordinate of the crop start. For the YUV420SP_U8 format, the value must be an even number. The value range is [0, 4095].|
| crop_start_pos_h | Int, vertical coordinate of the crop start. For the YUV420SP_U8 format, the value must be an even number. The value range is [0, 4095].|
| crop_size_w | Int, width of the crop ROI. Value range: [1, 4096]|
| crop_size_h | Int, height of the crop ROI. Value range: [1, 4096]|
| batch_index | Int, index of the batch for image cropping. The default value is `0`. The value range is [0, batch_size). `batch_size` is set when [acl.mdl.create_aipp](function-create_aipp.md) is called to create data of the `aclmdlAIPP` type.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|

## Constraints

If the cropping function is enabled, the following conditions must be met for the arguments passed to the [acl.mdl.set\_aipp\_src\_image\_size](function-set_aipp_src_image_size.md) call and `acl.mdl.set_aipp_crop_params` call:

- srcImageSizeW ≥ cropSizeW + cropStartPosW
- srcImageSizeH ≥ cropSizeH + cropStartPosH
