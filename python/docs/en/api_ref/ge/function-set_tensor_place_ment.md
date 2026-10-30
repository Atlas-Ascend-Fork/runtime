# Function: set\_tensor\_place\_ment

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

Sets the placement attribute of a tensor description to identify whether the tensor memory is host memory or device memory.

## Prototype

- **C Prototype**

    ```c
    aclError aclSetTensorPlaceMent(aclTensorDesc *desc, aclMemType memType)
    ```

- **Python Function**

    ```python
    ret = acl.set_tensor_place_ment(desc, mem_type)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| desc | Int, pointer address of the tensor description. Call [acl.create_tensor_desc](function-create_tensor_desc.md) in advance to create the tensor description of an operator input or output as the input of this API.|
| mem_type | Int, placement attribute value. For details, see [aclMemType](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/API/runtimeapi/aclpythondevg_01_0940.html).|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|
