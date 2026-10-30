# Function: create\_handle\_for\_s8gemv

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

Creates a handle to matrix-vector multiplication. The input data type is `int8_t`, and the output data type is `int32_t`.

After the handle is created, call [acl.op.execute\_with\_handle](function-execute_with_handle.md) to execute the operator.

## Prototype

- **C Prototype**

    ```c
    aclError aclblasCreateHandleForS8gemv(aclTransType transA,
    int m,
    int n,
    aclComputeType type,
    aclopHandle **handle)
    ```

- **Python Function**

    ```python
    handle, ret = acl.blas.create_handle_for_s8gemv(trans_a, m, n, type)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| trans_a | Int, whether matrix A is transposed.|
| m | Int, number of rows in matrix A (row-major first in data storing).|
| n | Int, number of columns in matrix A.|
| type | Int, computation precision.|

## Return Values

| Return Value| Description|
| --- | --- |
| handle | Int, pointer address of the handle data of the operator to be executed.|
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|
