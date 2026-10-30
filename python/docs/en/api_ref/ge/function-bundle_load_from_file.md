# Function: bundle\_load\_from\_file

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

If variables need to be dynamically updated during model execution, this API can be called to load offline model data (AI processor-adapted offline model) from a file. The memory is managed by the system.

This API must be used with other APIs to dynamically update variables. The process of calling the key APIs is as follows:

1. Build and save the model based on graph build methods. The model contains multiple graphs, such as the inference graph, variable initialization graph, and variable update graph.

    In this section, `aclgrphBundleBuildModel` is called to build the model, and `aclgrphBundleSaveModel` is called to save the model. For details about the APIs, see *Graph Development*.

2. Call [acl.mdl.bundle\_load\_from\_file](function-bundle_load_from_file.md) or [acl.mdl.bundle\_load\_from\_mem](function-bundle_load_from_mem.md) to load the model.
3. Call [acl.mdl.bundle\_get\_model\_id](function-bundle_get_model_id.md) to obtain the IDs of multiple graphs.
4. Call the model execution APIs (for example, [acl.mdl.execute](function-execute.md)) to execute each graph based on the IDs of those graphs.

    If variable update is involved, call [acl.mdl.set\_dataset\_tensor\_desc](function-set_dataset_tensor_desc.md) to set the tensor description of the graph before updating the variable update graph. After you have executed the variable update graph, execute the inference graph again.

5. After the inference is complete, call [acl.mdl.bundle\_unload](function-bundle_unload.md) to unload the model.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlBundleLoadFromFile(const char *modelPath, uint32_t *bundleId)
    ```

- **Python Function**

    ```python
    bundle_id, ret = acl.mdl.bundle_load_from_file(model_path)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_path | Str, character string of the model file path. The path contains the file name. The user who runs the app must have the permission to access the storage path. The model file is built in graph mode. Call `aclgrphBundleBuildModel` to compile the model, and call `aclgrphBundleSaveModel` to save the model. For details about the APIs, see *Graph Development*.|

## Return Values

| Return Value| Description|
| --- | --- |
| bundle_id | Int. After the system successfully loads the model, `bundle_id` is returned as the flag for identifying the model in subsequent operations.|
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Reference

For details about the API call sequence and sample code, see [Weight Update](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/others/acldevg/aclpythondevg_0158.html).
