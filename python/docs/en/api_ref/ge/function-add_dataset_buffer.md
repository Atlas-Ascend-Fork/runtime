# Function: add\_dataset\_buffer

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

Adds `aclDataBuffer` to `aclmdlDataset`.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlAddDatasetBuffer(aclmdlDataset *dataset, aclDataBuffer *dataBuffer)
    ```

- **Python Function**

    ```python
    dataset, ret = acl.mdl.add_dataset_buffer(dataset, data_buffer)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| dataset | Int, `aclmdlDataset` pointer address where `aclDataBuffer` is to be added. Call the [acl.mdl.create_dataset](function-create_dataset.md) API to create data of the `aclmdlDataset` type in advance.|
| data_buffer | Int, `aclDataBuffer` pointer address to be added. Call `acl.create_data_buffer` to create data of the `aclDataBuffer` type in advance.|

## Return Values

| Return Value| Description|
| --- | --- |
| dataset | Int, `aclmdlDataset` pointer address where `aclDataBuffer` is to be added.|
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|
