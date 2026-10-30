# Function: get\_stream\_available\_num

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

Obtains the number of available streams on the current device.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtGetStreamAvailableNum(uint32_t *streamCount)
    ```

- **Python Function**

    ```python
    stream_count, ret = acl.rt.get_stream_available_num()
    ```

## Parameters

None

## Return Values

| Return Value| Description|
| --- | --- |
| stream_count | Int, number of available streams.|
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
