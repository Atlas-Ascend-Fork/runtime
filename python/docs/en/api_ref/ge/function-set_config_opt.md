# Function: set\_config\_opt

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

Sets the value of an attribute in the configuration object for loading a model, including the model execution priority, model file directory or memory address, and memory size.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlSetConfigOpt(aclmdlConfigHandle *handle, aclmdlConfigAttr attr, const void *attrValue, size_t valueSize)
    ```

- **Python Function**

    ```python
    ret = acl.mdl.set_config_opt(config_handle, attr, attr_value)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| config_handle | Int, pointer address of the configuration object for loading a model. Call [acl.mdl.create_config_handle](function-create_config_handle.md) to create the pointer address in advance.|
| attr | Int, attribute to be set. For details about the value, see [aclmdlConfigAttr](aclmdlConfigAttr.md).|
| attr_value | Int/Str, attribute value. For details about the value, see [aclmdlConfigAttr](aclmdlConfigAttr.md).|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Constraints

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
