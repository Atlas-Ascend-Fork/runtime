# Function: get\_event\_avail\_num

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

Queries the number of available events on the current device.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtGetEventAvailNum(uint32_t *eventCount)
    ```

- **Python Function**

    ```python
    event_count, ret = acl.rt.get_event_avail_num()
    ```

## Parameters

None

## Return Values

| Return Value| Description|
| --- | --- |
| event_count | Int, number of events.|
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
