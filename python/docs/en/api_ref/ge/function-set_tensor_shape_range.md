# Function: set\_tensor\_shape\_range

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

Sets the shape range of each dimension of a tensor after a tensor description is created by the [acl.create\_tensor\_desc](function-create_tensor_desc.md) call.

Use case: For a dynamic-shape operator, a dynamic dimension is represented by `-1`. However, the value range of each dynamic dimension is different and needs to be set explicitly.

For example, if the tensor shape is [16, -1, 20, -1], the corresponding shape range can be [[16, 16], [1, 128], [20, 20], [1, 10]]. This indicates that the first dimension's shape size is fixed at 16, the second dimension's shape size ranges from 1 to 128, the third dimension's shape size is fixed at 20, and the fourth dimension's shape size ranges from 1 to 10.

## Prototype

- **C Prototype**

    ```c
    aclError aclSetTensorShapeRange(aclTensorDesc* desc, size_t dimsCount, int64_t dimsRange[][ACL_TENSOR_SHAPE_RANGE_NUM])
    ```

- **Python Function**

    ```python
    ret = acl.set_tensor_shape_range(desc, dims_range)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| desc | Int, pointer address of the tensor description data. Call [acl.create_tensor_desc](function-create_tensor_desc.md) to create data of the `aclTensorDesc` type in advance.|
| dims_range | List. A two-dimensional list is used to indicate the value range of each dimension.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|
