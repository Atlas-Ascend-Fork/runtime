# Function: set\_op\_execute\_time\_out

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

Sets the timeout interval (in seconds) for operator execution. If this API is called multiple times in a process, the last configured interval is used. If a timeout interval is carried during operator delivery, the timeout interval takes precedence over the timeout interval set by this API.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtSetOpExecuteTimeOut(uint32_t timeout)
    ```

- **Python Function**

    ```python
    ret = acl.rt.set_op_execute_time_out(timeout)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| timeout | Int, timeout interval, in seconds. `0` means to use the maximum timeout interval.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- If this API is not called, the default timeout interval of AI Core and AI CPU operators varies depending on the product model.
  <!-- npu="950" id7 -->
  - For Ascend 950PR&950DT products, the default timeout interval of AI Core operators is 1091s, and that of AI CPU operators is 28s.
  <!-- end id7 -->
  <!-- npu="A3" id8 -->
  - For Atlas A3 products, the default timeout interval of AI Core operators is 1091s, and that of AI CPU operators is 60s.
  <!-- end id8 -->
  <!-- npu="910b" id9 -->
  - For Atlas A2 products, the default timeout interval of AI Core operators is 1091s, and that of AI CPU operators is 28s.
  <!-- end id9 -->
  <!-- npu="310b" id10 -->
  - For Atlas 200I/500 A2 inference products, the default timeout interval of AI Core operators is 1091s, and that of AI CPU operators is 28s.
  <!-- end id10 -->
  <!-- npu="310p" id11 -->
  - For Atlas inference products, the default timeout interval of AI Core operators is 547s, and that of AI CPU operators is 28s.
  <!-- end id11 -->
  <!-- npu="910" id12 -->
  - For Atlas training products, the default timeout interval of AI Core operators is 68s, and that of AI CPU operators is 28s.
  <!-- end id12 -->

<!-- npu="950,A3,910b,910,310p,310b" id13 -->
- The maximum timeout interval of AI Core and AI CPU operators varies depending on the architecture of the product model.
  <!-- npu="950,910b,A3" id14 -->
  - For the following product models, the maximum timeout interval is interval x 254, in microseconds. The value of interval can be obtained by calling [acl.rt.get_op_timeout_interval](function-get_op_timeout_interval.md).
  Ascend 950PR&950DT products
  Atlas A3 products
  Atlas A2 products
  <!-- end id14 -->
  <!-- npu="310b" id18 -->
  - For Atlas 200I/500 A2 inference products, the maximum timeout interval is 1091 seconds.
  <!-- end id18 -->
  <!-- npu="910" id15 -->
  - For Atlas training products, the maximum timeout interval is 2176 seconds.
  <!-- end id15 -->
  <!-- npu="310p" id16 -->
  - For Atlas inference products, the maximum timeout interval of AI Core operators is 547 seconds, and the maximum timeout interval of AI CPU operators cannot be set.
  <!-- end id16 -->
<!-- end id13 -->
