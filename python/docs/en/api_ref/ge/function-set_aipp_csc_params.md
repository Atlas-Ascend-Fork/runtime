# Function: set\_aipp\_csc\_params

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

Sets CSC parameters in dynamic AIPP scenarios. If the CSC switch is disabled, parameters set by calling this interface are invalid.

```python
YUV-to-BGR conversion:
| B |   | cscMatrixR0C0 cscMatrixR0C1 cscMatrixR0C2 | | Y - cscInputBiasR0 |
| G | = | cscMatrixR1C0 cscMatrixR1C1 cscMatrixR1C2 | | U - cscInputBiasR1 | >> 8
| R |   | cscMatrixR2C0 cscMatrixR2C1 cscMatrixR2C2 | | V - cscInputBiasR2 |
BGR-to-YUV conversion:
| Y |   | cscMatrixR0C0 cscMatrixR0C1 cscMatrixR0C2 | | B |        | cscOutputBiasR0 |
| U | = | cscMatrixR1C0 cscMatrixR1C1 cscMatrixR1C2 | | G | >> 8 + | cscOutputBiasR1 |
| V |   | cscMatrixR2C0 cscMatrixR2C1 cscMatrixR2C2 | | R |        | cscOutputBiasR2 |
```

CSC parameters are closely related to the formats of the source and destination images. You can refer to the CSC configuration description in [Ascend Tensor Compiler (ATC)](https://hiascend.com/en/document/redirect/cannCommunityATC) for CSC parameter settings. Configure CSC parameters as required if the listed image formats do not meet your requirements.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlSetAIPPCscParams(aclmdlAIPP *aippParmsSet, int8_t cscSwitch,
    int16_t cscMatrixR0C0, int16_t cscMatrixR0C1, int16_t cscMatrixR0C2,
    int16_t cscMatrixR1C0, int16_t cscMatrixR1C1,int16_t cscMatrixR1C2,
    int16_t cscMatrixR2C0, int16_t cscMatrixR2C1, int16_t cscMatrixR2C2,
    uint8_t cscOutputBiasR0, uint8_t cscOutputBiasR1, uint8_t cscOutputBiasR2,
    uint8_t cscInputBiasR0, uint8_t cscInputBiasR1, uint8_t cscInputBiasR2)
    ```

- **Python Function**

    ```python
    ret = acl.mdl.set_aipp_csc_params(aipp_parms_set, csc_switch, csc_matrix_R0C0, csc_matrix_R0C1, csc_matrix_R0C2,csc_matrix_R1C0, csc_matrix_R1C1, csc_matrix_R1C2, csc_matrix_R2C0, csc_matrix_R2C1, csc_matrix_R2C2, csc_output_bias_R0, csc_output_bias_R1, csc_output_bias_R2, csc_input_bias_R0, csc_input_bias_R1, csc_input_bias_R2)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| aipp_parms_set | Int, pointer address of the dynamic AIPP configuration object. The `aclmdlAIPP` data must be created by the [acl.mdl.create_aipp](function-create_aipp.md) call in advance.|
| csc_switch | int, CSC switch.<br>Value range:<br> `0` (default): disabled<br> `1`: enabled|
| csc_matrix_R0C0 | Int, CSC matrix parameter. Value range: [–32677, 32676].|
| csc_matrix_R0C1 | Int, CSC matrix parameter. Value range: [–32677, 32676].|
| csc_matrix_R0C2 | Int, CSC matrix parameter. Value range: [–32677, 32676].|
| csc_matrix_R1C0 | Int, CSC matrix parameter. Value range: [–32677, 32676].|
| csc_matrix_R1C1 | Int, CSC matrix parameter. Value range: [–32677, 32676].|
| csc_matrix_R1C2 | Int, CSC matrix parameter. Value range: [–32677, 32676].|
| csc_matrix_R2C0 | Int, CSC matrix parameter. Value range: [–32677, 32676].|
| csc_matrix_R2C1 | Int, CSC matrix parameter. Value range: [–32677, 32676].|
| csc_matrix_R2C2 | Int, CSC matrix parameter. Value range: [–32677, 32676].|
| csc_output_bias_R0 | Int, output bias during RGB2YUV conversion. The default value is `0`. Value range: [0, 255].|
| csc_output_bias_R1 | Int, output bias during RGB2YUV conversion. The default value is `0`. Value range: [0, 255].|
| csc_output_bias_R2 | Int, output bias during RGB2YUV conversion. The default value is `0`. Value range: [0, 255].|
| csc_input_bias_R0 | Int, input bias during YUV2RGB conversion. The default value is `0`. Value range: [0, 255].|
| csc_input_bias_R1 | Int, input bias during YUV2RGB conversion. The default value is `0`. Value range: [0, 255].|
| csc_input_bias_R2 | Int, input bias during YUV2RGB conversion. The default value is `0`. Value range: [0, 255].|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|

## Constraints

If the original image format is set to YUV400 by the [acl.mdl.set\_aipp\_input\_format](function-set_aipp_input_format.md) call, setting the CSC attributes by this API is not supported.
