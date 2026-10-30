# Function: set\_op\_execute\_timeout\_v2

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

Sets the timeout interval (in microseconds) for operator execution. If a timeout interval is carried during operator delivery, the timeout interval takes precedence over the timeout interval set by this API.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtSetOpExecuteTimeOutV2(uint64_t timeout,  uint64_t *actualTimeout)
    ```

- **Python Function**

    ```python
    actual_time_out, ret = acl.rt.set_op_execute_timeout_v2(timeout)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| timeout | Int, timeout interval, in microseconds. `0` means to use the maximum timeout interval.|

## Return Values

| Return Value| Description|
| --- | --- |
| actual_time_out | Int, actual timeout, in microseconds.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

<!-- npu="950,A3,910b" id7 -->
- For the following product models, if the interval obtained by calling acl.rt.get_op_timeout_interval is less than 100000 microseconds and the timeout parameter is set to 0, the AI Core operator will never time out. In this case, the value of the `actual\_time\_out` parameter is the maximum value of `uint64_t`.

    <!-- npu="950" id8 -->
    Ascend 950PR&950DT products
    <!-- end id8 -->

    <!-- npu="A3" id9 -->
    Atlas A3 products
    <!-- end id9 -->

    <!-- npu="910b" id10 -->
    Atlas A2 products
    <!-- end id10 -->
<!-- end id7 -->

<!-- npu="910,310p,310b" id11 -->
- For the following product models, only the timeout interval for AI Core operator execution can be set by calling this API:

    <!-- npu="310b" id12 -->
    Atlas 200I/500 A2 inference products
    <!-- end id12 -->

    <!-- npu="310p" id13 -->
    Atlas inference products
    <!-- end id13 -->

    <!-- npu="910" id14 -->
    Atlas training products
    <!-- end id14 -->
<!-- end id11 -->
