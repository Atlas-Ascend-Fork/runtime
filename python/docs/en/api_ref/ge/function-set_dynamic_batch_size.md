# Function: set\_dynamic\_batch\_size

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

Sets the batch size for dynamic-shape model inference before the model is executed.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlSetDynamicBatchSize(uint32_t modelId, aclmdlDataset *dataset, size_t index, uint64_t batchSize)
    ```

- **Python Function**

    ```python
    ret = acl.mdl.set_dynamic_batch_size(model_id, dataset, index, batch_size)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_id | Int, model ID. After the model loading API (such as [acl.mdl.load_from_file](function-load_from_file.md) or [acl.mdl.load_from_mem](function-load_from_mem.md)) is successfully called, the model ID is returned. The ID is used as the input of this API.|
| dataset | Int, pointer address of the input data of a model. Data of type `aclmdlDataset` describes the input data for model inference, while data of type `aclDataBuffer` describes the input buffer size and address. For details, see [acl.mdl.load_from_file](function-load_from_file.md).|
| index | Int, index of the input dynamic batch, obtained by calling [acl.mdl.get_input_index_by_name](function-get_input_index_by_name.md). For dynamic batch and image size, the input name is fixed at `ascend_mbatch_shape_data`. For dynamic AIPP, the input name is fixed at `ascend_dynamic_aipp_data`.|
| batch_size | Int, batch size for model inference. The configured `batch size` must be among the batch size profiles set during model building. You can also call [acl.mdl.get_dynamic_batch](function-get_dynamic_batch.md) to obtain the number of batch profiles supported by a specified model and the number of batches in each profile.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Reference

For the API calling process and example, see [Dynamic Batch/Dynamic Image Size/Dynamic Dimension (Setting Multi-Dimension Profiles)](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/others/acldevg/aclpythondevg_0046.html).
