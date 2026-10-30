# Function: cast

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

Casts the data type of a tensor. This API is asynchronous.

## Prototype

- **C Prototype**

    ```c
    aclError aclopCast(const aclTensorDesc *srcDesc, const aclDataBuffer *srcBuffer, const aclTensorDesc *dstDesc, aclDataBuffer *dstBuffer, uint8_t truncate, aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret = acl.op.cast(src_desc, src_buffer, dst_desc, dst_buffer,truncate, stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| src_desc | Int, pointer address of the input tensor description.|
| src_buffer | Int, input tensor, the `aclDataBuffer` pointer address created by calling `acl.create_data_buffer`.|
| dst_desc | Int, pointer address of the output tensor description.|
| dst_buffer | Int, output tensor, the `aclDataBuffer` pointer address created by calling `acl.create_data_buffer`.|
| truncate | Int, reserved.|
| stream | Int, stream where the operator is executed, stream address object.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Reference

For the API call example, see [API Calling Process](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/others/acldevg/aclpythondevg_0069.html).
