# Function: get\_function\_addr

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

Obtains the start address of an operator on a device based on a kernel function handle. For operators that involve matrix and vector compute, an operator has two start addresses, which are executed on the Cube and Vector compute units, respectively. This API can be used to obtain the start addresses of operators on the Cube and Vector compute units. If the value of `aivAddr` obtained by calling this API is empty, the operator is executed only on the Cube Unit.

The AI data processing core unit varies with products.

<!-- npu="910,310p" id7 -->
- For the following products, the start address of an operator on the AI Core is returned through the `aic_addr` parameter.

    <!-- npu="910" id8 -->
    Atlas training products
    <!-- end id8 -->

    <!-- npu="310p" id9 -->
    Atlas inference products
    <!-- end id9 -->
<!-- end id7 -->

<!-- npu="950,A3,910b,310b" id10 -->
- For the following products, the start address of an operator on the Cube Core is returned through the `aic_addr` parameter.

    <!-- npu="950" id11 -->
    Ascend 950PR&950DT products
    <!-- end id11 -->

    <!-- npu="A3" id12 -->
    Atlas A3 products
    <!-- end id12 -->

    <!-- npu="910b" id13 -->
    Atlas A2 products
    <!-- end id13 -->

    <!-- npu="310b" id14 -->
    Atlas 200I/500 A2 inference products
    <!-- end id14 -->
<!-- end id10 -->

## Prototype

- **C Prototype**

    ```c
    aclError aclrtGetFunctionAddr(aclrtFuncHandle funcHandle, void **aicAddr, void **aivAddr)
    ```

- **Python Function**

    ```python
    aic_addr, aiv_addr, ret = acl.rt.get_function_addr(func_handle)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| func_handle | Int, kernel function handle.|

## Return Values

| Return Value| Description|
| --- | --- |
| aic_addr | Int, start address of an operator on the AI Core or Cube Core.|
| aiv_addr | Int, start address of an operator on the Vector Core.<br>If the value of `aivAddr` obtained by calling this API is empty, the operator is not executed on the Vector Core.|
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
