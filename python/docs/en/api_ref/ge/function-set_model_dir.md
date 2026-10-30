# Function: set\_model\_dir

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

Sets the directory for loading model files. The directory stores single-operator model files (*.om files).

## Prototype

- **C Prototype**

    ```c
    aclError aclopSetModelDir(const char *modelDir)
    ```

- **Python Function**

    ```python
    ret = acl.op.set_model_dir(model_dir)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_dir | Str, directory where the specified model file is stored. A multi-level directory is supported. However, the system reads the model up to three levels down from the last level. For the example, if `modelDir` is set to `dir0/dir1` and `dir1` contains `dir2/dir3/dir4`, the system looks up for the model file in `dir1`, `dir1/dir2` and `dir1/dir2/dir3` only.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Constraints

<!-- npu="950,A3,910b,310b,310p,910" id7 -->
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

For details about the API calling process and examples, see [Single-Operator Calling](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/others/acldevg/aclpythondevg_0067.html).
