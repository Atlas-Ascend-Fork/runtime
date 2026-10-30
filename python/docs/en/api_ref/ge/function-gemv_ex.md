# Function: gemv\_ex

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

Computes matrix-vector multiplication: y = αAx + βy. The data types of the input and output data are set using arguments. This API is asynchronous.

## Prototype

- **C Prototype**

    ```c
    aclError aclblasGemvEx(aclTransType transA,
    int m,
    int n,
    const void *alpha,
    const void *a,
    int lda,
    aclDataType dataTypeA,
    const void *x,
    int incx,
    aclDataType dataTypeX,
    const void *beta,
    void *y,
    int incy,
    aclDataType dataTypeY,
    aclComputeType type,
    aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret = acl.blas.gemv_ex(trans_a, m, n, alpha, a, lda, data_type_a, x, incx, data_type_x, beta, y, incy, data_type_y, type, stream)
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
| data_type_a | Int, data type of matrix A.|
| x | Int, data pointer address of vector `x`.|
| incx | Int, increment between successive `x` elements. This parameter is reserved and can only be set to `–1`.|
| data_type_x | Int, data type of vector x.|
| beta | Int, data pointer address of scalar beta used for executing the multiplication operation.|
| y | Int, data pointer address of vector `y`.|
| incy | Int, increment between successive `y` elements. This parameter is reserved and can only be set to `–1`.|
| data_type_y | Int, data type of vector y.|
| type | Int, computation precision type (high precision by default).|
| stream | Int, stream where the operator is executed.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Constraints

`A`, `x`, and `y` support a limited combination of data types, where `α` and `β` have the same data types as `y`.

| Data Type of A| Data Type of x| Data Type of y|
| --- | --- | --- |
| aclFloat16 | aclFloat16 | aclFloat16 |
| aclFloat16 | aclFloat16 | float(float32) |
| int8_t | int8_t | float(float32) |
| int8_t | int8_t | int32_t |

## Reference

For the API calling process, see [API Calling Process](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/others/acldevg/aclpythondevg_0069.html).
