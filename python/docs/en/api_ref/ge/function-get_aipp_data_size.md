# Function: get\_aipp\_data\_size

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

Obtains the memory size required by the dynamic AIPP input data based on `batch_size`.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlGetAippDataSize(uint64_t batchSize, size_t *size)
    ```

- **Python Function**

    ```python
    mem_size, ret = acl.mdl.get_aipp_data_size(batch_size)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| batch_size | Int, batch size of the original model.|

## Return Values

| Return Value| Description|
| --- | --- |
| mem_size | Int, memory size, in bytes.|
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|
