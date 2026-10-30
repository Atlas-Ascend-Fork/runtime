# Function: set\_aipp\_src\_image\_size

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

Sets the source image size (height and width), required in the dynamic AIPP scenario.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlSetAIPPSrcImageSize(aclmdlAIPP *aippParmsSet, int32_t srcImageSizeW, int32_t srcImageSizeH)
    ```

- **Python Function**

    ```python
    ret = acl.mdl.set_aipp_src_image_size(aipp_parms_set, src_image_size_w, src_image_size_h)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| aipp_parms_set | Int, dynamic AIPP configuration object. The `aclmdlAIPP` data must be created by the [acl.mdl.create_aipp](function-create_aipp.md) call in advance.|
| src_image_size_w | Int, source image width. For the YUV420SP_U8 format, the value must be an even number. Value range: [2, 4096].|
| src_image_size_h | Int, source image height. For the YUV420SP_U8 format, the value must be an even number. Value range: [1, 4096].|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|
