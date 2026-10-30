# Function: set\_stream\_overflow\_switch

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
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas inference products: Not supported
<!-- end id5 -->
<!-- npu="910" id6 -->
- Atlas training products: Not supported
<!-- end id6 -->

## Function

Enables or disables overflow detection for a specified stream when the upper-layer training framework (such as PyTorch) is connected. If disabled, you cannot use the overflow detection operator to check whether a task overflows.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtSetStreamOverflowSwitch(aclrtStream stream, uint32_t flag)
    ```

- **Python Function**

    ```python
    ret = acl.rt.set_stream_overflow_switch(stream, flag)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| stream | Int, pointer address of the specified stream. If `0` is passed, the default stream will be operated.|
| flag | Int, overflow detection switch. The options are as follows:<br>`0`: disabled<br>`1`: enabled|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

The setting takes effect only for tasks created after this API call.
