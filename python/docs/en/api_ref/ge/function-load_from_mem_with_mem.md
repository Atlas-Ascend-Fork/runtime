# Function: load\_from\_mem\_with\_mem

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

Loads OM model file data from memory. The model workspace is managed by the user.

For details about how to obtain the OM model file, see "[--mode](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/devaids/atctool/docs/en/user_guides/atc_tools/CLI_options/--model.md)" in the [[Ascend Tensor Compiler (ATC)](https://hiascend.com/en/document/redirect/cannCommunityATC).

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlLoadFromMemWithMem(const void *model, size_t modelSize, uint32_t *modelId, void *workPtr, size_t workSize, void *weightPtr, size_t weightSize)
    ```

- **Python Function**

    ```python
    model_id, ret = acl.mdl.load_from_mem_with_mem(model, model_size, work_ptr, work_size, weight_ptr, weight_size)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model | Int, memory address of the model.|
| model_size | Int, model size in bytes.|
| work_ptr | Int, pointer address of the workspace (for storing model input and output data) required by the model on the device. The memory is managed by the user and cannot be freed during model execution. If `0` is passed for this parameter, the system manages the memory. In the event where the memory is managed by the user, if multiple models are executed in serial, the models can share a workspace. However, you need to guarantee the serial execution sequence of the models and the workspace size (the same as the total size of the workspaces needed by all the models). Refer to the following description to ensure serial execution: Lock the model during execution to ensure that tasks are executed in serial.|
| work_size | Int, workspace size required for model execution, in bytes. This parameter is invalid when `work_ptr` is set to `0`.|
| weight_ptr | Int, pointer address of the model weight memory (for storing weight data) on the device. The memory is managed by the user and cannot be freed during model execution. If `0` is passed for `weight_ptr`, the system manages the memory. In the multithreaded scenario where the weight memory is managed by the user, if a model is loaded once in each thread, `weight_ptr` can be shared because the weight memory is read-only at inference time. Note that `weight_ptr` cannot be freed when the sharing is in progress.|
| weight_size | Int, weight memory size in bytes. This parameter is invalid when `weight_ptr` is set to `0`.|

## Return Values

| Return Value| Description|
| --- | --- |
| model_id | Int, model ID generated after the model is loaded.|
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
