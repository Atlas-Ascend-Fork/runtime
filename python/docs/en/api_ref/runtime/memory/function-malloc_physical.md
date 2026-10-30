# Function: malloc\_physical

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

Allocates physical host or device memory. A physical memory handle will be returned.

This API can be used together with [acl.rt.reserve\_mem\_address](function-reserve_mem_address.md) (for allocating virtual memory) and [acl.rt.map\_mem](function-map_mem.md) (for establishing the mapping between the virtual memory and the physical memory) to allocate virtual memory with consecutive addresses and maximize the use of physical memory addresses.

This API can be used together with [acl.rt.mem\_export\_to\_shareable\_handle](function-mem_export_to_shareable_handle.md) (for exporting the physical memory handle) and [acl.rt.mem\_import\_from\_shareable\_handle](function-mem_import_from_shareable_handle.md) (for importing the shared handle) to implement physical memory sharing among multiple processes. In addition, the virtual memory can be used when the physical memory is shared. For details, see the description of [acl.rt.mem\_export\_to\_shareable\_handle](function-mem_export_to_shareable_handle.md).

## Prototype

- **C Prototype**

    ```c
    aclError aclrtMallocPhysical(aclrtDrvMemHandle *handle, size_t size, const aclrtPhysicalMemProp *prop, uint64_t flags)
    ```

- **Python Function**

    ```python
    handle, ret = acl.rt.malloc_physical(size, prop, flags)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| size | Int, size of the physical address space, in bytes.<br>Call [acl.rt.mem_get_allocation_granularity](function-mem_get_allocation_granularity.md) to obtain the memory allocation granularity, and then call this API to allocate physical memory. The size is aligned based on the obtained memory allocation granularity to save memory.|
| prop | Dict, physical memory attributes. For details, see [aclrtPhysicalMemProp](../datatypes/aclrtPhysicalMemProp.md).|
| flags | Int, reserved. Currently, this parameter can only be set to **0**.|

## Return Values

| Return Value| Description|
| --- | --- |
| handle | Int, handle for storing physical memory information.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

<!-- npu="310b" id7 -->
- On Atlas 200I/500 A2 inference products, this API cannot be called in Ascend RC mode.
<!-- end id7 -->

<!-- npu="A3" id8 -->
- On Atlas A3 SuperPoD products, when the memory location `prop["location"]["type"]` is `ACL_MEM_LOCATION_TYPE_HOST_NUMA` and the memory attribute type `prop["memAttr"]` is P2P (for example, `ACL_MEM_P2P_HUGE`), the maximum memory size that can be allocated varies depending on the server model and BIOS version. You are advised to call the `acl.rt.malloc_physical` API to allocate memory based on the memory plan to check whether the memory is sufficient.
<!-- end id8 -->
- `prop["memAttr"]` supports only the following memory attribute types:
  - `ACL_MEM_NORMAL`: normal memory.
  - `ACL\_MEM\_HUGE`: 2 MB huge page.
  - `ACL\_MEM\_HUGE1G`: 1 GB huge page, which is supported only by devices.

    <!-- npu="A3,910b" id9 -->
    Only Atlas A3 and Atlas A2 products support this type.
    <!-- end id9 -->

    Other models do not support this type.

  - `ACL\_MEM\_P2P\_NORMAL`: Normal page memory for inter-device memory copy.
  - `ACL\_MEM\_P2P\_HUGE`: Huge page memory for inter-device memory copy. The memory allocation granularity is 2 MB.
  - `ACL\_MEM\_P2P\_HUGE1G`: Huge page memory for inter-device memory copy. The memory allocation granularity is 1 GB, which is supported only by the device.

    <!-- npu="A3" id10 -->
    Only certain Atlas A3 interconnect products support this type. The actual return result of the API is used.
    <!-- end id10 -->

    Other models do not support this type.

  - `ACL\_HBM\_MEM\_HUGE`: 2 MB huge page.
  - `ACL\_HBM\_MEM\_HUGE1G`: 1 GB huge page, which is supported only by devices.

    <!-- npu="950,A3,910b" id11 -->
    Ascend 950PR&950DT, Atlas A3, and Atlas A2 products support this type.
    <!-- end id11 -->

    Other models do not support this type.

  - `ACL\_HBM\_MEM\_NORMAL`: normal memory. The API allocates huge page memory based on the `ACL\_HBM\_MEM\_HUGE` type.
  - `ACL\_DDR\_MEM\_HUGE`: huge page memory, which is supported only by the host.
  - `ACL\_DDR\_MEM\_NORMAL`: normal memory, which is supported only by the host.
  - `ACL\_DDR\_MEM\_P2P\_HUGE`: huge page memory used for data replication between devices, which is supported only by the host.
  - `ACL\_DDR\_MEM\_P2P\_NORMAL`: normal memory used for data replication between devices, which is supported only by the host.
