# Function: load\_with\_config

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

Loads a model based on the given configuration.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlLoadWithConfig(const aclmdlConfigHandle *handle, uint32_t *modelId)
    ```

- **Python Function**

    ```python
    model_id, ret = acl.mdl.load_with_config(config_handle)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| config_handle | Int, configuration object for model loading. Call [acl.mdl.create_config_handle](function-create_config_handle.md) to create an object in advance, which must be consistent with `config_handle` output by the [acl.mdl.set_config_opt](function-set_config_opt.md) call.|

## Return Values

| Return Value| Description|
| --- | --- |
| model_id | Int, model ID generated after the model is loaded.|
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Constraints

Before loading the model file, check whether the memory space is sufficient based on the file size. If the memory space is insufficient, the application will be abnormal.

This API needs to work with the following APIs to load models:

1. Call [acl.mdl.create\_config\_handle](function-create_config_handle.md) to create a configuration object for loading a model.
2. Call [acl.mdl.set\_config\_opt](function-set_config_opt.md) multiple times to set the value of each attribute in the configuration object.
3. Call [acl.mdl.load\_with\_config](function-load_with_config.md) to specify the configuration information for model loading and load your model.
4. Call [acl.mdl.destroy\_config\_handle](function-destroy_config_handle.md) to destroy the configuration object after the model is successfully loaded.

## Reference

For [acl.mdl.set\_config\_opt](function-set_config_opt.md) and [acl.mdl.load\_with\_config](function-load_with_config.md), the caller needs to set the attributes in the configuration object passed to the API call to decide how the model will be loaded and who will manage the memory.

By choosing from the following APIs, you can directly determine whether to load a model from a file or from memory and whether the memory is managed by the system or the user.

- [acl.mdl.load\_from\_file](function-load_from_file.md)
- [acl.mdl.load\_from\_mem](function-load_from_mem.md)
- [acl.mdl.load\_from\_file\_with\_mem](function-load_from_file_with_mem.md)
- [acl.mdl.load\_from\_mem\_with\_mem](function-load_from_mem_with_mem.md)
