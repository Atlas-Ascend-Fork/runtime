# Function: set\_tensor\_origin\_shape

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

Sets the original dimensions of a tensor after a tensor description is created by the [acl.create\_tensor\_desc](function-create_tensor_desc.md) call. This API is mainly used in the PyTorch scenarios.

For example, if the original operator is 4D with format NHWC or 5D with format NDHWC, the format is automatically converted to NC1HWC0 or NDC1HWC0 during model conversion or online network construction to facilitate memory access efficiency on the AI processors. Along the process, the operator shape is also inferred to facilitate internal computation.

## Prototype

- **C Prototype**

    ```c
    aclError aclSetTensorOriginShape(aclTensorDesc *desc, int numDims, const int64_t *dims)
    ```

- **Python Function**

    ```python
    ret = acl.set_tensor_origin_shape(desc, dims)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| desc | Int, pointer address of the tensor description data. Call [acl.create_tensor_desc](function-create_tensor_desc.md) to create data of the `aclTensorDesc` type in advance.|
| dims | List, dimensions to be set.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|
