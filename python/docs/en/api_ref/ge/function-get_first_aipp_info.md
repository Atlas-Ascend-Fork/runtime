# Function: get\_first\_aipp\_info

## Applicable Products

<!-- npu="950" id1 -->
- Ascend 950PR&950DT products: Not supported
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

Obtains the AIPP (static or dynamic) configuration of a model.

AIPP provides the following functions and they are executed in the exact sequence: Cropping \-> CSC \-> Mean subtraction/normalization \-> Padding.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlGetFirstAippInfo(uint32_t modelId, size_t index, aclAippInfo *aippInfo)
    ```

- **Python Function**

    ```python
    aipp_info, ret = acl.mdl.get_first_aipp_info(model_id, index)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_id | Int, model ID. You can obtain the model ID after the model is successfully loaded by calling the following APIs:<br> [acl.mdl.load_from_file](function-load_from_file.md)<br> [acl.mdl.load_from_mem](function-load_from_mem.md)<br> [acl.mdl.load_from_file_with_mem](function-load_from_file_with_mem.md)<br> [acl.mdl.load_from_mem_with_mem](function-load_from_mem_with_mem.md) |
| index | Int, the sequence number of the specified input image of the model|

## Return Values

| Return Value| Description|
| --- | --- |
| aipp_info | Dict, static AIPP configuration of the specified input. For details, see [aclAippInfo](aclAippInfo.md). For details about detailed description and paramter explanation, see [Ascend Tensor Compiler (ATC)](https://hiascend.com/en/document/redirect/cannCommunityATC).|
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|

## Constraints

To obtain the dynamic AIPP configuration, this API call returns the values of only the following parameters in `aipp_info`: `srcFormat`, `srcDatatype`, `srcDimNum`, `shapeCount`, and `outDims`.
