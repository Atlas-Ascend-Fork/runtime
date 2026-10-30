# Function: gemm\_ex

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

Computes matrix-matrix multiplication: C = αAB + βC. The data types of the input and output data are set using arguments. This API is asynchronous.

## Prototype

- **C Prototype**

    ```c
    aclError aclblasGemmEx(aclTransType transA,
    aclTransType transB,
    aclTransType transC,
    int m,
    int n,
    int k,
    const void *alpha,
    const void *matrixA,
    int lda,
    aclDataType dataTypeA,
    const void *matrixB,
    int ldb,
    aclDataType dataTypeB,
    const void *beta,
    void *matrixC,
    int ldc,
    aclDataType dataTypeC,
    aclComputeType type,
    aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret = acl.blas.gemm_ex(trans_a, trans_b, trans_c,
    m, n, k,
    alpha, matrix_a, lda, data_type_a,
    matrix_b, ldb, data_type_b,
    beta, matrix_c, ldc, data_type_c,
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
| data_type_a | Int, data type of matrix A.|
| matrix_b | Int, data pointer address of matrix B.|
| ldb | Int, leading dimension of matrix B. For row-major transpose, `ldb` is the number of columns of matrix B. This parameter is reserved and can only be set to `–1`.|
| data_type_b | Int, data type of matrix B.|
| beta | Int, data pointer address of scalar beta used for executing the multiplication operation.|
| matrix_c | Int, data pointer address of matrix C.|
| ldc | Int, leading dimension of matrix C. This parameter is reserved and can only be set to `–1`.|
| data_type_c | Int, data type of matrix C.|
| type | Int, computation precision.|
| stream | Int, stream where the operator is executed.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Constraints

`A`, `B`, and `C` support a limited combination of data types. `α` and `β` have the same data types as `C`.

| Data Type of A| Data Type of x| Data Type of y|
| --- | --- | --- |
| aclFloat16 | aclFloat16 | aclFloat16 |
| aclFloat16 | aclFloat16 | float(float32) |
| int8_t | int8_t | float(float32) |
| int8_t | int8_t | int32_t |

## Reference

For the API calling process and examples, see [API Calling Process](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/others/acldevg/aclpythondevg_0069.html).
