# Function: load\_from\_file

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

Loads an offline model from a file. The memory is managed by the system.

The file specified by `modelPath` is an offline model in the format of *.om. For details about how to obtain the OM model file, see "[--mode](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/devaids/atctool/docs/en/user_guides/atc_tools/CLI_options/--model.md)" in the [Ascend Tensor Compiler (ATC)](https://hiascend.com/en/document/redirect/cannCommunityATC).

If the size of the OM model file is limited, this API can also load an external weight file. You need to save the weight in a separate file during model building. For example, when you use ATC to generate an .om file, set `--external_weight` to `1`, indicating that the weight of the Const/Constant node on the original network is saved in a separate file in the `weight` directory. Ensure that the `weight` directory is at the same level as the .om file so that the API can automatically search for the weight file in the `weight` directory when you call this API to load the .om file. Otherwise, the weight file may fail to be loaded.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlLoadFromFile(const char *modelPath, uint32_t *modelId)
    ```

- **Python Function**

    ```python
    model_id, ret = acl.mdl.load_from_file(model_path)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_path | Str, directory of an offline model file, including the file name. The user who runs the app must have enough permission to access the directory.|

## Return Values

| Return Value| Description|
| --- | --- |
| model_id | Int, pointer address of the model ID generated after the system loads the model.|
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Reference

The [acl.mdl.set\_config\_opt](function-set_config_opt.md) and [acl.mdl.load\_with\_config](function-load_with_config.md) APIs are also provided for model loading. The caller needs to set the attributes in the configuration object passed to the API call to decide how the model will be loaded and who will manage the memory.
