# Function: load\_from\_mem

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

Loads OM model file data from memory. The model workspace is managed by the system.

For details about how to obtain the OM model file, see "[--mode](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/devaids/atctool/docs/en/user_guides/atc_tools/CLI_options/--model.md)" in the [[Ascend Tensor Compiler (ATC)](https://hiascend.com/en/document/redirect/cannCommunityATC).

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlLoadFromMem(const void *model, size_t modelSize, uint32_t* modelId)
    ```

- **Python Function**

    ```python
    model_id, ret = acl.mdl.load_from_mem(model, model_size)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model | Int, pointer address of the memory address of the model data.|
| model_size | Int, size of the model data in the memory, in bytes.|

## Return Values

| Return Value| Description|
| --- | --- |
| model_id | Int, pointer address of the model ID generated after the system loads the model.|
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Constraints

<!-- npu="950,A3,910b,910,310p,310b" id7 -->
In Ascend EP form, allocate memory on the host for the model parameter.
<!-- end id7 -->

<!-- npu="310b" id8 -->
In Ascend RC form, allocate memory on the device for the model parameter.
<!-- end id8 -->

<!-- npu="310p" id9 -->
In Ctrl CPU form, allocate memory on the device for the model parameter.
<!-- end id9 -->

## Reference

The [acl.mdl.set\_config\_opt](function-set_config_opt.md) and [acl.mdl.load\_with\_config](function-load_with_config.md) APIs are also provided for model loading. The caller needs to set the attributes in the configuration object passed to the API call to decide how the model will be loaded and who will manage the memory.
