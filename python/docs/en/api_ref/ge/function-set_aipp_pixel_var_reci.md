# Function: set\_aipp\_pixel\_var\_reci

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

Sets the variance of each channel in the dynamic AIPP scenario.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlSetAIPPPixelVarReci(aclmdlAIPP *aippParmsSet, float dtcPixelVarReciChn0, float dtcPixelVarReciChn1, float dtcPixelVarReciChn2, float dtcPixelVarReciChn3, uint64_t batchIndex)
    ```

- **Python Function**

    ```python
    ret = acl.mdl.set_aipp_pixel_var_reci(aipp_parms_set, dtc_pixel_var_reci_chn0, dtc_pixel_var_reci_chn1, dtc_pixel_var_reci_chn2, dtc_pixel_var_reci_chn3, batch_index)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| aipp_parms_set | Int, pointer address of the dynamic AIPP configuration object. The `aclmdlAIPP` data must be created by the [acl.mdl.create_aipp](function-create_aipp.md) call in advance.|
| dtc_pixel_var_reci_chn0 | Float, variance of channel 0. Defaults to `1.0`. The value range is [-65504, 65504].|
| dtc_pixel_var_reci_chn1 | Float, variance of channel 1. Defaults to `1.0`. The value range is [-65504, 65504].|
| dtc_pixel_var_reci_chn2 | Float, variance of channel 2. Defaults to `1.0`. The value range is [-65504, 65504].|
| dtc_pixel_var_reci_chn3 | Float, variance of channel 3. If there are only three channels, the default value `1.0` is used. The value range is [-65504, 65504].|
| batch_index | Int, index of the batch for setting the mean value of each image channel. The default value is `0`. The value range is [0, batch_size). `batch_size` is set when `acl.mdl.create_aipp` is called to create data of the `aclmdlAIPP` type.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|
