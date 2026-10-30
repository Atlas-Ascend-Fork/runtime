# Function: set\_tensor\_value\_range

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

Sets the value range of a tensor after a tensor description is created by the [acl.create\_tensor\_desc](function-create_tensor_desc.md) call.

Use case: For some operators, the input value is also the output shape. However, in the dynamic shape scenario, the shape has a value range. When executing an operator, you need to set the shape value range for the input (for example, [[16, 16], [1, 128], [20, 20], [1, 10]]). Only in this way can you properly execute operators.

## Prototype

- **C Prototype**

    ```c
    aclError aclSetTensorValueRange(aclTensorDesc* desc, size_t valueCount, int64_t valueRange[][ACL_TENSOR_VALUE_RANGE_NUM])
    ```

- **Python Function**

    ```python
    ret = acl.set_tensor_value_range(desc, value_range)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| desc | Int, pointer address of the `aclTensorDesc` type. Call [Function: create_tensor_desc](function-create_tensor_desc.md) to create data of the `aclTensorDesc` type in advance.|
| value_range | List. A two-dimensional list is used to indicate the range of each data value. ACL_TENSOR_VALUE_RANGE_NUM = 2 |

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|
