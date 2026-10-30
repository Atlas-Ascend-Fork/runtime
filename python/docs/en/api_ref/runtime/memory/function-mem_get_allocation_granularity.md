# Function: mem\_get\_allocation\_granularity

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

Queries the memory allocation granularity. The system internally calculates the minimum granularity or recommended granularity for a given allocation specification and returns the granularity using the `granularity` parameter. This granularity can be used as a multiple of alignment, address size, or address mapping.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtMemGetAllocationGranularity(aclrtPhysicalMemProp *prop, aclrtMemGranularityOptions option, size_t *granularity)
    ```

- **Python Function**

    ```python
    granularity, ret = acl.rt.mem_get_allocation_granularity(prop, option)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| prop | Dict, physical memory attributes. For details, see [aclrtPhysicalMemProp](../datatypes/aclrtPhysicalMemProp.md).|
| option | Int, minimum granularity or recommended granularity. For details, see [aclrtMemGranularityOptions](../datatypes/aclrtMemGranularityOptions.md).|

## Return Values

| Return Value| Description|
| --- | --- |
| granularity | Int, memory allocation granularity, in bytes. Currently, only 2 MB is supported.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

<!-- npu="310b" id7 -->
## Constraints

<!-- npu="310b" id8 -->
On Atlas 200I/500 A2 inference products, this API cannot be called in Ascend RC mode.
<!-- end id8 -->
<!-- end id7 -->
