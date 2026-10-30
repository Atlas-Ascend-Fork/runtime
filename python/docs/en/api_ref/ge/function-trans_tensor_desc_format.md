# Function: trans\_tensor\_desc\_format

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

Converts the format of `srcDesc` (in the input source aclTensorDesc) based on the specified `dstFormat` to generate a new target aclTensorDesc. The format in the source aclTensorDesc remains unchanged. This API is not supported in the current version and is reserved.

## Prototype

- **C Prototype**

    ```c
    aclError aclTransTensorDescFormat(const aclTensorDesc *srcDesc, aclFormat dstFormat, aclTensorDesc **dstDesc)
    ```

- **Python Function**

    ```python
    dst_desc, ret = acl.trans_tensor_desc_format(src_desc, dst_format)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| src_desc | Int, pointer address of the input source `aclTensorDesc` data. Call [Function: create_tensor_desc](function-create_tensor_desc.md) to create data of the `aclTensorDesc` type in advance.|
| dst_format | Int, target format to be set. For details, see [aclFormat](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/API/runtimeapi/aclpythondevg_01_0914.html).|

## Return Values

| Return Value| Description|
| --- | --- |
| dst_desc | Int, pointer address of the output `aclTensorDesc`. Call [Function: create_tensor_desc](function-create_tensor_desc.md) to create data of the `aclTensorDesc` type in advance.|
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|
