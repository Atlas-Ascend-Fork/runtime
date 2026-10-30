# Function: create\_handle

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

Creates a handle to an operator.

To destroy a handle, call [acl.op.destroy\_handle](function-destroy_handle.md).

## Prototype

- **C Prototype**

    ```c
    aclError aclopCreateHandle(const char *opType, int numInputs, const aclTensorDesc *const inputDesc[], int numOutputs, const aclTensorDesc *const outputDesc[], const aclopAttr *opAttr, aclopHandle **handle)
    ```

- **Python Function**

    ```python
    handle, ret = acl.op.create_handle(op_type, input_desc, output_desc, op_attr)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| op_type | Str, operator type name.|
| input_desc | Int list, description of the operator input tensor.|
| output_desc | Int list, description of the operator output tensor.|
| op_attr | Int, pointer address of an operator attribute. This object is created by calling [acl.op.create_attr](function-create_attr.md).|

## Return Values

| Return Value| Description|
| --- | --- |
| handle | Int, operator handle address object.|
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|

## Constraints

If an operator has a constant input but [acl.set\_tensor\_const](function-set_tensor_const.md) has not been called to set the constant input, call [acl.set\_tensor\_place\_ment](function-set_tensor_place_ment.md) to set the placement attribute of `TensorDesc` and set `memType` to the host memory.
