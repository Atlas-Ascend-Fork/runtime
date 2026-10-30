# Function: get\_stream\_overflow\_switch

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

Checks whether overflow detection is enabled for a specified stream.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtGetStreamOverflowSwitch(aclrtStream stream, uint32_t flag)
    ```

- **Python Function**

    ```python
    flag, ret = acl.rt.get_stream_overflow_switch(stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| stream | Int, pointer address of the stream to be operated. If `0` is passed, the default stream will be operated.|

## Return Values

| Return Value| Description|
| --- | --- |
| flag | Int, overflow detection switch. The options are as follows:<br>`0`: disabled<br>`1`: enabled|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
