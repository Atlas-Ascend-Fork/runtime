# Function: set\_aipp\_padding\_params

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

Sets padding parameters in the dynamic AIPP scenario.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlSetAIPPPaddingParams(aclmdlAIPP *aippParmsSet, int8_t paddingSwitch, int32_t paddingSizeTop, int32_t paddingSizeBottom, int32_t paddingSizeLeft, int32_t paddingSizeRight, uint64_t batchIndex)
    ```

- **Python Function**

    ```python
    ret = acl.mdl.set_aipp_padding_params(aipp_parms_set, padding_switch, padding_size_top, padding_size_bottom, padding_size_left, padding_size_right, batch_index)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| aipp_parms_set | Int, pointer address of the dynamic AIPP configuration object. The `aclmdlAIPP` data must be created by the [acl.mdl.create_aipp](function-create_aipp.md) call in advance.|
| padding_switch | Int, whether to enable image padding. Value range: `0`: Edge padding is not performed. The default value is 0. In this case, setting `padding_size_top`, `padding_size_bottom`, `padding_size_left`, and `padding_size_right` is invalid.<br> `1`: enabled|
| padding_size_top | Int, top padding size. Value range: [0, 32].|
| padding_size_bottom | Int, bottom padding size. Value range: [0, 32].|
| padding_size_left | Int, left padding size. Value range: [0, 32].|
| padding_size_right | Int, right padding size. Value range: [0, 32].|
| batch_index | Int, index of the batch for image padding. The default value is `0`. The value range is [0, batch_size). `batch_size` is set when [acl.mdl.create_aipp](function-create_aipp.md) is called to create data of the `aclmdlAIPP` type.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|

## Constraints

The padded width must be less than or equal to 1080 pixels.
