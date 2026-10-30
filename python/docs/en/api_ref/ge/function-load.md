# Function: load

## Applicable Products

<!-- npu="950" id1 -->
- Ascend 950PR&950DT products: Not supported
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

Loads the single-operator model data from the memory. The memory is managed by the user.

## Prototype

- **C Prototype**

    ```c
    aclError aclopLoad(const void *model, size_t modelSize)
    ```

- **Python Function**

    ```python
    ret = acl.op.load(model, model_size)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model | Int, address object of the single-operator model data.|
| model_size | Int, length of the model data in the memory, in bytes.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Constraints

<!-- npu="950,A3,910b,910,310p,310b" id7 -->
Before loading, check whether the memory space is sufficient based on the size of the single-operator OM file. If the memory space is insufficient, the application will be abnormal. The maximum number of operators being executed in a process varies depending on the product model.
<!-- end id7 -->

<!-- npu="950,A3,910b" id8 -->
- For Ascend 950PR&950DT, Atlas A3, and Atlas A2 products, the maximum number is 2,000,000.
<!-- end id8 -->
<!-- npu="910,310b" id9 -->
- For Atlas 200I/500 A2 inference products and Atlas training products, the maximum number is 40,000,000.
<!-- end id9 -->
<!-- npu="310p" id10 -->
- For Atlas inference products, the upper limit is 40,000,000 in Ascend EP form and 2,000,000 in open Ctrl CPU from.
<!-- end id10 -->

## Reference

For details about the API calling process, see [Single-Operator Calling](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/others/acldevg/aclpythondevg_0067.html).
