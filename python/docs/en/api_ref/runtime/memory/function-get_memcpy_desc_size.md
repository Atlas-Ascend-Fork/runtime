# Function: get\_memcpy\_desc\_size

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
- Atlas inference products: Not supported
<!-- end id5 -->
<!-- npu="910" id6 -->
- Atlas training products: Not supported
<!-- end id6 -->

## Function

Obtains the memory size used by the memory copy descriptor of the current device.

This API must be used together with other key APIs to implement memory copy. For details, see [acl.rt.memcpy\_async\_with\_desc](function-memcpy_async_with_desc.md).

## Prototype

- **C Prototype**

    ```c
    aclError aclrtGetMemcpyDescSize(aclrtMemcpyKind kind, size_t *descSize)
    ```

- **Python Function**

    ```python
    desc_size, ret = acl.rt.get_memcpy_desc_size(kind)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| kind | Int, memory copy type.<br>Currently, only `ACL_MEMCPY_INNER_DEVICE_TO_DEVICE` is supported, indicating memory copy within a device.|

## Return Values

| Return Value| Description|
| --- | --- |
| desc_size | Int, memory size, in bytes.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
