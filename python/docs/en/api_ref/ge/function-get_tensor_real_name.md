# Function: get\_tensor\_real\_name

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

Obtains the real name of a tensor by tensor name.

Use `acl.mdl.get_tensor_real_name` with the following APIs:

- [acl.mdl.get\_input\_dims](function-get_input_dims.md)
- [acl.mdl.get\_input\_dims\_v2](function-get_input_dims_v2.md)
- [acl.mdl.get\_output\_dims](function-get_output_dims.md)
- [acl.mdl.get\_cur\_output\_dims](function-get_cur_output_dims.md)

## Prototype

- **C Prototype**

    ```c
    const char *aclmdlGetTensorRealName(const aclmdlDesc *modelDesc, const char *name)
    ```

- **Python Function**

    ```python
    real_name = acl.mdl.get_tensor_real_name(model_desc, name)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_desc | Int, pointer address of the `aclmdlDesc` type. Call the [acl.mdl.create_desc](function-create_desc.md) API to create data of the aclmdlDesc type in advance.|
| name | Str, tensor name.|

## Return Values

| Return Value| Description|
| --- | --- |
| real_name | Str, real name of a tensor. If `model_desc` or `name` is empty, `0` is returned.|
