# Function: malloc\_for\_task\_scheduler

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

Allocates the memory that can be used by the task scheduler on the AI processor.

Some operators in graph mode need to use the memory of this type.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtMallocForTaskScheduler(void **devPtr, size_t size, aclrtMemMallocPolicy policy, aclrtMallocConfig *cfg)
    ```

- **Python Function**

    ```python
    dev_ptr, ret = acl.rt.malloc_for_task_scheduler(size, policy, cfg)
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
