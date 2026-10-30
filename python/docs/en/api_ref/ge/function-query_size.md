# Function: query\_size

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

Obtains the weight memory size and workspace size required for model execution based on the model file.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlQuerySize(const char *fileName, size_t *workSize, size_t *weightSize)
    ```

- **Python Function**

    ```python
    work_size, weight_size, ret = acl.mdl.query_size(file_name)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| file_name | Str, directory of the model file, including the file name. The user who runs the app must have the permission to access the path.|

## Return Values

| Return Value| Description|
| --- | --- |
| work_size | Int, workspace size required for model execution, in bytes.|
| weight_size | Int, weight memory size required for model execution, in bytes.|
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Constraints

If the memory is managed by the user, you need to call [acl.mdl.query\_size](function-query_size.md) to query the sizes of the workspace and weight memory required for model execution to avoid memory waste.

If the shape of the input data is uncertain, you cannot call [acl.mdl.query\_size](function-query_size.md) to query the memory size. As a result, you cannot manage the memory during model loading. Therefore, you need to call [acl.mdl.load\_from\_file](function-load_from_file.md) or [acl.mdl.load\_from\_mem](function-load_from_mem.md) to allow the system to manage the memory.

## Reference

For details about the API calling process, see [Model Loading](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/others/acldevg/aclpythondevg_0031.html).
