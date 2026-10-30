# Function: s8gemv

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

Computes matrix-vector multiplication: y = αAx + βy. The input data type is `int8_t`, and the output data type is `int32_t`. This API is asynchronous.

## Prototype

- **C Prototype**

    ```c
    aclError aclblasS8gemv(aclTransType transA,
    int m,
    int n,
    const int32_t *alpha,
    const int8_t *a,
    int lda,
    const int8_t *x,
    int incx,
    const int32_t *beta,
    int32_t *y,
    int incy,
    aclComputeType type,
    aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret = acl.blas.s8gemv(trans_a, m, n, alpha, a, lda, x, incx, beta, y, incy, type, stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| trans_a | Int, whether matrix A is transposed.|
| m | Int, number of rows in matrix A (row-major first in data storing).|
| n | Int, number of columns in matrix A.|
| alpha | Int, data pointer address of scalar alpha used for executing the multiplication operation.|
| a | Int, data pointer address of matrix A.|
| lda | Int, leading dimension of matrix A. For row-major transpose, `lda` is the number of columns of matrix A. This parameter is reserved and can only be set to `–1`.|
| x | Int, data pointer address of vector `x`.|
| incx | Int, increment between successive `x` elements. This parameter is reserved and can only be set to `–1`.|
| beta | Int, data pointer address of scalar beta used for executing the multiplication operation.|
| y | Int, data pointer address of vector `y`.|
| incy | Int, increment between successive `y` elements. This parameter is reserved and can only be set to `–1`.|
| type | Int, computation precision.|
| stream | Int, stream where the operator is executed.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Reference

For the API calling process, see [API Calling Process](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/others/acldevg/aclpythondevg_0069.html).
