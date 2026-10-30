# Function: set\_aipp\_dtc\_pixel\_mean

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

Sets the mean value of each channel in the dynamic AIPP scenario.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlSetAIPPDtcPixelMean(aclmdlAIPP *aippParmsSet, int16_t dtcPixelMeanChn0, int16_t dtcPixelMeanChn1, int16_t dtcPixelMeanChn2, int16_t dtcPixelMeanChn3, uint64_t batchIndex)
    ```

- **Python Function**

    ```python
    ret = acl.mdl.set_aipp_dtc_pixel_mean(aipp_parms_set, dtc_pixel_mean_chn0, dtc_pixel_mean_chn1, dtc_pixel_mean_chn2, dtc_pixel_mean_chn3, batch_index)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| aipp_parms_set | Int, pointer address of the dynamic AIPP configuration object. The `aclmdlAIPP` data must be created by the [acl.mdl.create_aipp](function-create_aipp.md) call in advance.|
| dtc_pixel_mean_chn0 | Int, mean value of channel 0. The value range is [0, 255].|
| dtc_pixel_mean_chn1 | Int, mean value of channel 1. The value range is [0, 255].|
| dtc_pixel_mean_chn2 | Int, mean value of channel 2. The value range is [0, 255].|
| dtc_pixel_mean_chn3 | Int, mean value of channel 3. If there are only three channels, the default value `0` is used. The value range is [0, 255].|
| batch_index | Int, index of the batch for setting the mean value of each image channel. The default value is `0`. The value range is [0, batch_size). `batch_size` is set when `acl.mdl.create_aipp` is called to create data of the `aclmdlAIPP` type.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|
