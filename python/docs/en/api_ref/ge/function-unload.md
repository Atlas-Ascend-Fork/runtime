# Function: unload

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

Uninstalls the model and releases resources after the model inference is complete.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlUnload(uint32_t modelId)
    ```

- **Python Function**

    ```python
    ret = acl.mdl.unload(model_id)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_id | Int, ID of the model to unload.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Constraints

- When calling `acl.mdl.unload` to unload a specified model, ensure that the model is not used by other APIs.
- The operations of loading, executing, and unloading a model must be performed in the same context. For details about how to create a context, see `acl.rt.set_device` and `acl.rt.create_context`.

## Reference

For the API calling process, see [API Calling Process](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/others/acldevg/aclpythondevg_0005.html).
