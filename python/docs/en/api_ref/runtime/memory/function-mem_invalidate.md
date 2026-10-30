# Function: mem\_invalidate

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

Invalidates the cache.

In this version, you do not need to care about the cache coherence between the CPU and NPU and therefore this API is unused in this version.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtMemInvalidate(void *devPtr, size_t size)
    ```

- **Python Function**

    ```python
    ret = acl.rt.mem_invalidate(dev_ptr, size)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| devPtr | Int, invalid cache corresponding to the DDR memory.|
| size | Int, DDR memory size, in bytes. Must not be `0`.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
