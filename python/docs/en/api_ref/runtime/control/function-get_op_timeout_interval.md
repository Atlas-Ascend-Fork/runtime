# Function: get\_op\_timeout\_interval

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

Obtains the minimum interval (in microseconds) supported by the hardware for operator timeout configuration.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtGetOpTimeoutInterval(uint64_t *interval)
    ```

- **Python Function**

    ```python
    interval, ret = acl.rt.get_op_timeout_interval()
    ```

## Parameters

None

## Return Values

| Parameter| Description|
| --- | --- |
| interval | Int, minimum interval, in microseconds.<br>The timeout that can be configured and applied is `interval × *N*`. *N* is an integer of [1, 254]. If the configured timeout is not equal to `interval × *N*`, the timeout is rounded up to `interval × *N*`. For example, if `interval` is 100 microseconds and the configured timeout is 50 microseconds, the actual timeout is 100 microseconds (100 × 1). If the user-defined timeout is 30,000 microseconds, the actual timeout is 25,400 microseconds (100 × 254).|
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
