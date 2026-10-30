# Function: query\_size\_from\_mem

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

Obtains the weight memory size and workspace size required for model execution based on the model data in the memory.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlQuerySizeFromMem(const void *model, size_t modelSize, size_t *workSize, size_t *weightSize)
    ```

- **Python Function**

    ```python
    work_size, weight_size, ret = acl.mdl.query_size_from_mem(model, model_size)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model | Int, pointer address of the model data whose memory information needs to be obtained.|
| model_size | Int, model size in bytes.|

## Return Values

| Return Value| Description|
| --- | --- |
| work_size | Int, workspace size required for model execution, in bytes.|
| weight_size | Int, weight memory size required for model execution, in bytes.|
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Constraints

The workspace and weight memory are both device memory, which need to be allocated and freed by the user.
