# Function: get\_aipp\_type

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

Obtains the AIPP type (dynamic or static) supported by an input of a model, and the index of the input configured with dynamic AIPP.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlGetAippType(uint32_t modelId, size_t index, aclmdlInputAippType *type, size_t *dynamicAttachedDataIndex)
    ```

- **Python Function**

    ```python
    type, dynamic_attached_data_index, ret = acl.mdl.get_aipp_type(model_id, index)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_id | Int, model ID. After the model loading API (such as [acl.mdl.load_from_file](function-load_from_file.md) or [acl.mdl.load_from_mem](function-load_from_mem.md)) is successfully called, the model ID is returned. The ID is used as the input of this API.|
| index | Int, index of the model input.|

## Return Values

| Return Value| Description|
| --- | --- |
| type | Int, AIPP type of the specified model input. For details, see [aclmdlInputAippType](aclmdlInputAippType.md).|
| dynamic_attached_data_index | Int, returned information.<br> When `type` is not `ACL_DATA_WITH_DYNAMIC_AIPP`, `0xFFFFFFFF` is returned, indicating a failure.<br> When `type` is `ACL_DATA_WITH_DYNAMIC_AIPP`, the `index` of the input configured with dynamic AIPP is returned.|
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Reference

For the API call example, see [Dynamic AIPP (Multiple Dynamic AIPP Inputs)](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/others/acldevg/aclpythondevg_0040.html).
