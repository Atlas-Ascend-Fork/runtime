# Function: malloc\_align32

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

Allocates linear memory of the specified size on the device and returns the pointer to the allocated memory through `dev\_ptr`. The allocation size is the input size rounded up to the nearest multiple of 32 bytes. The memory allocated by calling this API needs to be freed by calling [acl.rt.free](../memory/function-free.md).

<!-- npu="950" id7 -->
For Ascend 950PR&950DT products, this API has the same function as the aclrtMalloc API.
<!-- end id7 -->

<!-- npu="A3,910b,910,310p,310b" id8 -->
For the product models below, compared with the aclrtMalloc API, this API only rounds the input size up to the nearest multiple of 32 bytes, but does not add an extra 32 bytes.

<!-- npu="A3" id9 -->
- Atlas A3 products
<!-- end id9 -->
<!-- npu="910b" id10 -->
- Atlas A2 products
<!-- end id10 -->
<!-- npu="310b" id11 -->
- Atlas 200I/500 A2 inference products
<!-- end id11 -->
<!-- npu="310p" id12 -->
- Atlas inference products
<!-- end id12 -->
<!-- npu="910" id13 -->
- Atlas training products
<!-- end id13 -->

<!-- end id8 -->
## Prototype

- **C Prototype**

    ```c
    aclError aclrtMallocAlign32(void **devPtr, size_t size, aclrtMemMallocPolicy policy)
    ```

- **Python Function**

    ```python
    dev_ptr, ret = acl.rt.malloc_align32(size, policy)
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

- Media data processing has higher requirements on the memory for storing the input and output data (for example, the start address of the memory must be 128-byte aligned). Therefore, the following dedicated memory allocation APIs are required:
  - When calling [Media Data Processing V1](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/acce/dvpp/aclpythondevg_01_0220.html) APIs to crop or resize images, call the [acl.media.dvpp\_malloc](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/acce/dvpp/aclpythondevg_01_0223.html) API to allocate memory.
  - When calling [Media Data Processing V2](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/acce/dvpp/aclpythondevg_01_0411.html) APIs to crop or resize images, call the [acl.himpi.dvpp\_malloc](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/acce/dvpp/aclpythondevg_01_0416.html) API to allocate memory.

- The memory allocated by this API does not initialize the content.

- This API does not perform implicit device synchronization or stream synchronization. The memory allocation result, either success or failure, is returned immediately.
- The value of `policy` can only be a single enumeration item and cannot be multiple enumeration items combined with bitwise OR.
- For the ACL\_MEM\_MALLOC\_HUGE\_FIRST\_P2P and ACL\_MEM\_MALLOC\_HUGE\_ONLY\_P2P memory allocation rules, you are advised to use the [acl.rt.malloc\_with\_cfg](function-malloc_with_cfg.md) API. Otherwise, performance issues may occur or memory may fail to be allocated.
- The memory allocated by calling acl.rt.malloc\_align32 needs to be freed by calling [acl.rt.free](../memory/function-free.md).
- Performance deterioration will be caused by the frequent calling of acl.rt.malloc\_align32 to allocate memory and [acl.rt.free](../memory/function-free.md) to free memory. You are advised to allocate or manage memory in advance to avoid frequent memory allocation and deallocation.
- If you use this API to allocate a large memory block, and divide and manage the memory, each memory segment must meet the following requirements:

  - The memory size is rounded up to the nearest multiple of 32 plus 32 bytes (m = ALIGN\_UP[len, 32] + 32 bytes).
  - The memory start address must be 64-byte aligned (ALIGN\_UP\[m,64\]).

    >[!NOTE]
    >`len` indicates the size of a memory segment. `ALIGN\_UP\[len,k\]` indicates rounding up to the nearest multiple of k bytes: \(\(len-1\)/k+1\) x k.
