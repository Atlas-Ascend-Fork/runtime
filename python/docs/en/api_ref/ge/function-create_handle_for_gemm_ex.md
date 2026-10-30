# Function: create_handle_for_gemm_ex

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

Creates a handle to matrix-matrix multiplication. The data types of the input and output data are set using arguments.

After the handle is created, call [acl.op.execute\_with\_handle](function-execute_with_handle.md) to execute the operator.

## Prototype

- **C Prototype**

    ```c
    aclError aclblasCreateHandleForGemmEx(aclTransType transA,
    aclTransType transB,
    aclTransType transC,
    int m,
    int n,
    int k,
    aclDataType dataTypeA,
    aclDataType dataTypeB,
    aclDataType dataTypeC,
    aclComputeType type,
    aclopHandle **handle)
    ```

- **Python Function**

    ```python
    handle, ret = acl.blas.create_handle_for_gemm_ex(trans_a, trans_b, trans_c, m, n, k, data_type_a, data_type_b, data_type_c,type)
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
| data_type_a | Int, data type of matrix A.|
| data_type_b | Int, data type of matrix B.|
| data_type_c | Int, data type of matrix C.|
| type | Int, computation precision.|

## Return Values

| Return Value| Description|
| --- | --- |
| handle | Int, pointer address of the handle data of the operator to be executed.|
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Constraints

`A`, `B`, and `C` support a limited combination of data types.

| Data Type of A| Data Type of B| Data Type of C|
| --- | --- | --- |
| aclFloat16 | aclFloat16 | aclFloat16 |
| aclFloat16 | aclFloat16 | float(float32) |
| int8_t | int8_t | float(float32) |
| int8_t | int8_t | int32_t |
