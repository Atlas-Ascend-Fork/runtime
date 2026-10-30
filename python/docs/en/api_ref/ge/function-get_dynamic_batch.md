# Function: get\_dynamic\_batch

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

Obtains the dynamic batch size information supported by a model based on the model description.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlGetDynamicBatch(const aclmdlDesc *modelDesc, aclmdlBatch *batch)
    ```

- **Python Function**

    ```python
    batch, ret = acl.mdl.get_dynamic_batch(model_desc)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_desc | Int, pointer address of the data of the `aclmdlDesc` type. Call the [acl.mdl.create_desc](function-create_desc.md) API to create data of the aclmdlDesc type in advance.|

## Return Values

| Return Value| Description|
| --- | --- |
| batch | Dict, dynamic batch information supported by the obtained model.<br> The maximum number of batches supported by the model is 128. batch = { "batchCount": int, # Number of batch size profiles supported by the model. "batch": [xx, xx,] # Specific batch size profiles supported by the model.} - If batchCount is 0, the batch size profile information cannot be set and the batch size profile in the model is used.|
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|
