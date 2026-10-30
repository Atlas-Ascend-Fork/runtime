# Function: set\_tensor\_dynamic\_input

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

Sets the name of a dynamic input after a tensor description is created by the [acl.create\_tensor\_desc](function-create_tensor_desc.md) call.

## Prototype

- **C Prototype**

    ```c
    aclError aclSetTensorDynamicInput(aclTensorDesc *desc, const char *dynamicInputName)
    ```

- **Python Function**

    ```python
    ret = acl.set_tensor_dynamic_input(desc, dynamic_input_name)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| desc | Int, pointer address of the tensor description data. Call [acl.create_tensor_desc](function-create_tensor_desc.md) to create data of the `aclTensorDesc` type in advance.|
| dynamic_input_name | Str, name of the dynamic input in `desc`.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|
