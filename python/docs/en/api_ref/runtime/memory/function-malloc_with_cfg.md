# Function: malloc\_with\_cfg

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

Allocates linear memory of the specified size on the device and returns the pointer to the allocated memory through `dev\_ptr`.

Compared with [acl.rt.malloc](../memory/function-malloc.md), this API can also specify memory-related configuration when allocating memory.

The memory allocated by calling this API needs to be freed by calling [acl.rt.free](../memory/function-free.md).

## Prototype

- **C Prototype**

    ```c
    aclError aclrtMallocWithCfg(void **devPtr, size_t size, aclrtMemMallocPolicy policy, aclrtMallocConfig *cfg)
    ```

- **Python Function**

    ```python
    dev_ptr, ret = acl.rt.malloc_with_cfg(size, policy, cfg)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| size | Int, allocated memory size, in bytes. Must not be `0`.|
| policy | Int, memory allocation policy.<br>If the configured memory allocation rule exceeds the value range in [aclrtMemMallocPolicy](../datatypes/aclrtMemMallocPolicy.md) and the size is greater than or equal to 2 MB, the huge page memory is allocated. Otherwise, common page memory is allocated.|
| cfg | Dict, memory configuration. If no configuration is specified, an empty dictionary can be passed. For details, see [aclrtMallocConfig](../datatypes/aclrtMallocConfig.md).|

## Return Values

| Return Value| Description|
| --- | --- |
| devPtr | Int, address of the pointer to the allocated device memory.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

The value of `policy` can be a single enumeration item or multiple enumeration items combined with bitwise OR. In bitwise OR mode, the following three groups of enumeration items are supported, for example, ACL\_MEM\_TYPE\_HIGH\_BAND\_WIDTH | ACL\_MEM\_ACCESS\_USER\_SPACE\_READONLY | ACL\_MEM\_MALLOC\_HUGE\_FIRST:

- ACL_MEM_TYPE_LOW_BAND_WIDTH and ACL_MEM_TYPE_HIGH_BAND_WIDTH are used to distinguish between high and low bandwidth.
- ACL_MEM_ACCESS_USER_SPACE_READONLY specifies that the allocated memory is read-only in user mode.
- Other basic memory allocation rules includes ACL_MEM_MALLOC_HUGE_FIRST, ACL_MEM_MALLOC_HUGE_ONLY, and ACL_MEM_MALLOC_NORMAL_ONLY.
