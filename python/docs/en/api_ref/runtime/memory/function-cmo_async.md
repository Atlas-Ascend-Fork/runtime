# Function: cmo\_async

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

Implements cache memory operations on the device.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtCmoAsync(void *src, size_t size, aclrtCmoType cmoType, aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret = acl.rt.cmo_async(src, size, cmo_type, stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| src | Int, address of the device memory to be operated.|
| size | Int, size of the device memory to be operated, in bytes.|
| cmoType | Int, cache memory operation type. See [aclrtCmoType](../datatypes/aclrtCmoType.md).<br>Currently, only `ACL_RT_CMO_TYPE_PREFETCH` (memory prefetch) is supported.|
| stream | Int, stream.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
