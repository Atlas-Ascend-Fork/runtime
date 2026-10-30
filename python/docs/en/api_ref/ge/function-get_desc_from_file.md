# Function: get\_desc\_from\_file

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

Obtains model description based on the model file.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlGetDescFromFile(aclmdlDesc *modelDesc, const char *modelPath)
    ```

- **Python Function**

    ```python
    ret = acl.mdl.get_desc_from_file(model_desc, model_path)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_desc | Int, pointer to data of the `aclmdlDesc` type. You need to call the [create_desc](function-create_desc.md) API to create data of the `aclmdlDesc` type in advance. After the call is successful, the content in the pointer address is updated.|
| model_path | Str, directory of an offline model file, including the file name. The user who runs the app must have enough permission to access the directory. The offline model file is an offline model (.om file) adapted to the Ascend AI Processor.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, `0` on success; else, failure.|

## Constraints

The model description obtained using this API cannot be used for the [get\_op\_attr](function-get_op_attr.md) and [get\_cur\_output\_dims](function-get_cur_output_dims.md) APIs.
