# Function: create_handle_for_cast

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

Creates a handle to data type casting.

After the handle is created, call [acl.op.execute\_with\_handle](function-execute_with_handle.md) to execute the operator.

## Prototype

- **C Prototype**

    ```c
    aclError aclopCreateHandleForCast(const aclTensorDesc *srcDesc, const aclTensorDesc *dstDesc, uint8_t truncate, aclopHandle **handle)
    ```

- **Python Function**

    ```python
    handle, ret = acl.op.create_handle_for_cast(src_desc, dst_desc, truncate)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| src_desc | Int, pointer address of the input tensor description.|
| dst_desc | Int, pointer address of the output tensor description.|
| truncate | Int, reserved.|

## Return Values

| Return Value| Description|
| --- | --- |
| handle | Int, pointer address of the output handle.|
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|
