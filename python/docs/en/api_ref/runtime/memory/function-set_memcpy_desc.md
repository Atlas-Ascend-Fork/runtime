# Function: set\_memcpy\_desc

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

Sets the memory copy descriptor. After this API is called, the source address, destination address, and memory copy length are recorded in the memory copy descriptor.

This API must be used together with other key APIs to implement memory copy. For details, see [acl.rt.memcpy\_async\_with\_desc](function-memcpy_async_with_desc.md).

## Prototype

- **C Prototype**

    ```c
    aclError aclrtSetMemcpyDesc(void *desc, aclrtMemcpyKind kind, void *srcAddr, void *dstAddr, size_t count, void *config)
    ```

- **Python Function**

    ```python
    desc, ret = acl.rt.set_memcpy_desc(desc, kind, src_addr, dst_addr, count, config)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| desc | Int, pointer to the memory copy descriptor.<br>Call [acl.rt.get_memcpy_desc_size](function-get_memcpy_desc_size.md) to obtain the memory size required by the memory descriptor, allocate device memory (for example, by calling [acl.rt.malloc](../memory/function-malloc.md)), and pass the device memory address as an input.|
| kind | Int, memory copy type. Currently, only `ACL_MEMCPY_INNER_DEVICE_TO_DEVICE` is supported, indicating memory copy within a device.|
| src_addr | Int, pointer to the source memory address. The memory is allocated and managed by users.|
| dst_addr | Int, pointer to the destination memory address. The memory is allocated and managed by users.|
| count | Int, size in bytes to copy.|
| config | Int, reserved; fixed at `0`.|

## Return Values

| Return Value| Description|
| --- | --- |
| desc | Int, pointer to the memory copy descriptor.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
