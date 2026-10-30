# Function: set\_tensor\_storage\_format

**Note: This API will be deprecated in later versions. Use the [acl.set\_tensor\_format](function-set_tensor_format.md) API instead.**

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
- Atlas training products: Not supported
<!-- end id6 -->

## Function

Sets the actual format of the tensor after creating the tensor description by calling [acl.create\_tensor\_desc](function-create_tensor_desc.md). This API is mainly used in the PyTorch scenarios.

## Prototype

- **C Prototype**

    ```c
    aclError aclSetTensorStorageFormat(aclTensorDesc *desc, aclFormat format)
    ```

- **Python Function**

    ```python
    ret = acl.set_tensor_storage_format(desc, format)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| desc | Int, pointer address of the `aclTensorDesc` type. Call [acl.create_tensor_desc](function-create_tensor_desc.md) to create data of the `aclTensorDesc` type in advance.|
| format | Int, format of the specified tensor description.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|
