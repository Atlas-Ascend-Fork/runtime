# Function: hgemm

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

Computes matrix-matrix multiplication: C = αAB + βC. The inputs and outputs are all of data type `aclFloat16`. This API is asynchronous.

## Prototype

- **C Prototype**

    ```c
    aclError aclblasHgemm(aclTransType transA,
    aclTransType transB,
    aclTransType transC,
    int m,
    int n,
    int k,
    const aclFloat16 *alpha,
    const aclFloat16 *matrixA,
    int lda,
    const aclFloat16 *matrixB,
    int ldb,
    const aclFloat16 *beta,
    aclFloat16 *matrixC,
    int ldc,
    aclComputeType type,
    aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret = acl.blas.hgemm(trans_a, trans_b, trans_c,
    m, n, k,
    alpha, matrix_a, lda,
    matrix_b, ldb,
    beta, matrix_c, ldc,
    type, stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| trans_a | Int, whether matrix A is transposed.|
| trans_b | Int, whether matrix B is transposed.|
| trans_c | Int, whether matrix C is transposed. Currently, only `aclTrans_N` is supported.|
| m | Int, number of rows in matrix A and matrix C.|
| n | Int, number of columns in matrix B and matrix C.|
| k | Int, number of columns in matrix A and number of rows in matrix B.|
| alpha | Int, data pointer address of scalar alpha used for executing the multiplication operation.|
| matrix_a | Int, data pointer address of matrix A.|
| lda | Int, leading dimension of matrix A. For row-major transpose, `lda` is the number of columns of matrix A. This parameter is reserved and can only be set to `–1`.|
| matrix_b | Int, data pointer address of matrix B.|
| ldb | Int, leading dimension of matrix B. For row-major transpose, `ldb` is the number of columns of matrix B. This parameter is reserved and can only be set to `–1`.|
| beta | Int, data pointer address of scalar beta used for executing the multiplication operation.|
| matrix_c | Int, data pointer address of matrix C.|
| ldc | Int, leading dimension of matrix C. This parameter is reserved and can only be set to `–1`.|
| type | Int, computation precision.|
| stream | Int, stream where the operator is executed.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Reference

For the API calling process, see [API Calling Process](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/others/acldevg/aclpythondevg_0069.html).
