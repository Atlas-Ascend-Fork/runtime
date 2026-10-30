# Function: get\_op\_execute\_timeout

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

Obtains the timeout interval of AI Core operator execution.

If the AI Core operator never times out, the output value of the `time\_out\_ms` parameter is the maximum value of `uint32\_t`.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtGetOpExecuteTimeout(uint32_t *const timeoutMs)
    ```

- **Python Function**

    ```python
    time_out_ms, ret = acl.rt.get_op_execute_timeout()
    ```

## Parameters

None

## Return Values

| Parameter| Description|
| --- | --- |
| time_out_ms | Int, timeout interval, in milliseconds.<br>If the timeout interval has been set by calling a set API (for example, acl.rt.set_op_execute_time_out), the actual timeout interval of the hardware is returned. Otherwise, the default timeout interval of AI Core is returned.|
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
