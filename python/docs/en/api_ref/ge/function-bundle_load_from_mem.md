# Function: bundle\_load\_from\_mem

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

Loads offline model data from memory if variables need to be dynamically updated during model execution. The model workspace is managed by the system.

This API needs to be used with other APIs to dynamically update variables. For details, see [acl.mdl.bundle\_load\_from\_file](function-bundle_load_from_file.md).

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlBundleLoadFromMem(const void *model, size_t modelSize, uint32_t *bundleId)
    ```

- **Python Function**

    ```python
    bundle_id, ret = acl.mdl.bundle_load_from_mem(model, model_size)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model | Int, pointer address for storing model data. The model file is built in graph mode. Call `aclgrphBundleBuildModel` to compile the model, call `aclgrphBundleSaveModel` to save the model, and then read the saved the .om model file to the memory. For details about the graph APIs, see *Graph Development*.|
| model_size | Int, size of the model data in the memory, in bytes.|

## Return Values

| Return Value| Description|
| --- | --- |
| bundle_id | Int. After the system successfully loads the model, `bundle_id` is returned as the flag for identifying the model in subsequent operations.|
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
