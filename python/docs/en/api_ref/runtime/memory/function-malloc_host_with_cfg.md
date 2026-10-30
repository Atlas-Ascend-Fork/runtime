# Function: malloc\_host\_with\_cfg

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

Allocates host memory (page-locked memory). The system ensures that the start address of the memory is 64-byte aligned. Compared with [acl.rt.malloc\_host](function-malloc_host.md), this API can also specify memory-related configuration when allocating memory.

<!-- npu="310p,310b" id7 -->
In Ascend RC mode and open Ctrl CPU mode, the host and device are integrated. Therefore, allocating host memory is equivalent to allocating device memory. In addition, memory is allocated based on normal pages. If the start address needs to be 64-byte aligned, you need to handle the alignment problem by yourself.
<!-- end id7 -->

## Prototype

- **C Prototype**

    ```c
    aclError aclrtMallocHostWithCfg(void **ptr, uint64_t size, aclrtMallocConfig *cfg)
    ```

- **Python Function**

    ```python
    host_ptr, ret = acl.rt.malloc_host_with_cfg(size, cfg)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| size | Int, allocated memory size, in bytes. Must not be `0`.|
| cfg | Dict, memory configuration. If no configuration is specified, an empty dictionary can be passed. For details, see [aclrtMallocConfig](../datatypes/aclrtMallocConfig.md).|

## Return Values

| Return Value| Description|
| --- | --- |
| host_ptr | Int, address of the pointer to the allocated host memory.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
