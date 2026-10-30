# Function: create\_aipp

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

Creates data of the `aclmdlAIPP` type as a dynamic AIPP configuration based on the batch size supported by the model.

To destroy data of the aclmdlAIPP type, see [Function: destroy\_aipp](function-destroy_aipp.md).

## Prototype

- **C Prototype**

    ```c
    aclmdlAIPP *aclmdlCreateAIPP(uint64_t batchSize)
    ```

- **Python Function**

    ```python
    aipp_ptr = acl.mdl.create_aipp(batch_size)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| batch_size | Int, batch size of the model.|

## Return Values

| Return Value| Description|
| --- | --- |
| aipp_ptr | Int, object address of data of the `aclmdlAIPP` type.|
