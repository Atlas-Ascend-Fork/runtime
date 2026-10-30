# Function: malloc\_cached

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

Allocates cacheable device memory. Allocates linear memory of the specified size on the device and returns the pointer address of the allocated memory through `dev\_ptr`.

The memory allocated by calling [acl.rt.malloc\_cached](function-malloc_cached.md) is equivalent to that allocated by calling `acl.rt.malloc`. Both support cache. You do not need to handle the cache consistency between the CPU and NPU.

Before calling a media data processing API, call `acl.media.dvpp_malloc` to allocate memory on the device for storing the input or output data.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtMallocCached(void **devPtr, size_t size, aclrtMemMallocPolicy policy)
    ```

- **Python Function**

    ```python
    dev_ptr, ret = acl.rt.malloc_cached(size, policy)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| size | Int, allocated memory size, in bytes. Must not be `0`.|
| policy | Int, memory allocation policy.<br>If the configured memory allocation rule exceeds the value range in [aclrtMemMallocPolicy](../datatypes/aclrtMemMallocPolicy.md) and the size is greater than or equal to 2 MB, the huge page memory is allocated. Otherwise, common page memory is allocated.|

## Return Values

| Return Value| Description|
| --- | --- |
| dev_ptr | Int, address of the pointer to the allocated device memory.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

Other constraints are the same as those of [acl.rt.malloc](../memory/function-malloc.md).
