# Function: get\_dataset\_buffer

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

Obtains `aclDataBuffer` indexed `index` in `aclmdlDataset`.

## Prototype

- **C Prototype**

    ```c
    aclDataBuffer* aclmdlGetDatasetBuffer(const aclmdlDataset *dataset, size_t index)
    ```

- **Python Function**

    ```python
    data_buffer = acl.mdl.get_dataset_buffer(dataset, index)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| dataset | Int, pointer address of the `aclmdlDataset` data object. Call the [acl.mdl.create_dataset](function-create_dataset.md) API to create data of the `aclmdlDataset` type in advance.|
| index | Int, index of `aclDataBuffer` to obtain.|

## Return Values

| Return Value| Description|
| --- | --- |
| data_buffer | Int, pointer address of the `aclDataBuffer` data object.<br>Success: `aclDataBuffer` address<br>Failure: empty address|
