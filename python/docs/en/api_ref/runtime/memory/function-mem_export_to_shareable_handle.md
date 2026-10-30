# Function: mem\_export\_to\_shareable\_handle

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

Export the physical device memory handle obtained by the current process through [acl.rt.malloc\_physical](function-malloc_physical.md) so that the physical device memory can be shared with other processes.

**This API must be used together with the following APIs to implement memory sharing.** The following uses processes A and B as an example to describe the process of calling the physical memory sharing API between two processes.

1. In process A:
    a. Call [acl.rt.malloc\_physical](function-malloc_physical.md) to allocate physical memory.

    Call [acl.rt.mem_get_allocation_granularity](function-mem_get_allocation_granularity.md) to obtain the memory allocation granularity, and then call [acl.rt.malloc_physical](function-malloc_physical.md) to allocate physical memory. The size is aligned based on the obtained memory allocation granularity to save memory.

    To allocate contiguous virtual memory and maximize the utilization of physical memory addresses, you can use APIs such as [acl.rt.reserve_mem_address](function-reserve_mem_address.md) and [acl.rt.map_mem](function-map_mem.md) to allocate virtual memory and establish the mapping between virtual and physical memory. For details, see the description of the corresponding APIs.

    b. Call [acl.rt.mem\_export\_to\_shareable\_handle](function-mem_export_to_shareable_handle.md) to export the handle of the physical memory and output shareable\_handle.

    When calling [acl.rt.mem\_export\_to\_shareable\_handle](function-mem_export_to_shareable_handle.md), you can specify whether to enable process trustlist verification. If the verification is enabled, call [acl.rt.mem\_set\_pid\_to\_shareable\_handle](function-mem_set_pid_to_shareable_handle.md) separately to add the ID of process B to the trustlist. If the verification is disabled, there is no need to call [acl.rt.mem\_set\_pid\_to\_shareable\_handle](function-mem_set_pid_to_shareable_handle.md).

    c. Call [acl.rt.free\_physical](function-free_physical.md) to free the physical memory.

    After the memory is used, call [acl.rt.free\_physical](function-free_physical.md) to free the physical memory and destroy shareableHandle. If any process is still using the shareable handle, wait until the shareable handle completes before executing the destruction task.

        All processes involving shared memory must free their physical memory. The physical memory is completely freed only after all processes have freed it. After the physical memory is freed, the allocated memory is returned to the OS. Any subsequent use of the handle will cause undefined behavior.

2. In process B:
    a. Call [acl.rt.device_get_bare_tgid](../device/function-device_get_bare_tgid.md) to obtain the ID of process B.

    This API has been adapted to the physical machine and VM scenarios when obtaining the process ID. You only need to call it to obtain the process ID and then configure other APIs to share the physical memory. If you do not call this API to obtain the process ID, an exception may occur when you use the process ID.

    b. Call [acl.rt.mem\_import\_from\_shareable\_handle](function-mem_import_from_shareable_handle.md) to obtain the information in shareable_handle and return the handle in the current process. (Before calling [acl.rt.mem\_import\_from\_shareable\_handle](function-mem_import_from_shareable_handle.md), ensure that the physical memory to be shared exists and cannot be released in advance.)

    To allocate contiguous virtual memory and maximize the utilization of physical memory addresses, you can use APIs such as [acl.rt.reserve_mem_address](function-reserve_mem_address.md) and [acl.rt.map_mem](function-map_mem.md) to allocate virtual memory and establish the mapping between virtual and physical memory. For details, see the description of the corresponding APIs.

    c. Call [acl.rt.free\_physical](function-free_physical.md) to free the physical memory.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtMemExportToShareableHandle(aclrtDrvMemHandle handle, aclrtMemHandleType handleType, uint64_t flags, uint64_t *shareableHandle)
    ```

- **Python Function**

    ```python
    shareable_handle, ret = acl.rt.mem_export_to_shareable_handle(handle, handle_type, flags)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| handle | Int, handle for storing physical memory information.<br>You need to call [acl.rt.malloc_physical](function-malloc_physical.md) in this process to allocate physical memory. If this API is successfully called, a handle is returned.<br>There is a one-to-one mapping between handles and shareable handles. In the same process, one-to-many or many-to-one mapping is not allowed. Otherwise, an error is reported. For example, if this API is repeatedly called to export data, an error is reported.|
| handle_type | Int, reserved parameter. The value is fixed at `0` (ACL_MEM_HANDLE_TYPE_NONE).|
| flags | Int, whether to enable process trustlist verification.<br>The values are as follows:<br>`0x0`: ACL_RT_VMM_EXPORT_FLAG_DEFAULT (default value), indicating that process trustlist verification is enabled.<br>If this macro is used, call [acl.rt.mem_set_pid_to_shareable_handle](function-mem_set_pid_to_shareable_handle.md) separately to add the ID of the process that uses the shareable handle to the trustlist.<br>`0x1`: ACL_RT_IPC_MEM_EXPORT_FLAG_DISABLE_PID_VALIDATION, indicating that process trustlist verification is disabled.<br>If this macro is used, you do not need to call [acl.rt.mem_set_pid_to_shareable_handle](function-mem_set_pid_to_shareable_handle.md).|

## Return Values

| Return Value| Description|
| --- | --- |
| shareable_handle | Int, shareable handle shared with other processes.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

<!-- npu="310b" id7 -->
- On Atlas 200I/500 A2 inference products, this API cannot be called in Ascend RC mode.
<!-- end id7 -->

- The following product models support inter-process physical memory sharing within an AI server. If inter-device sharing is required, call [acl.rt.device\_enable\_peer\_access](../device/function-device_enable_peer_access.md). AI server is an umbrella term for servers consisting of multiple NPUs.
- Ascend virtualization instances are not supported.
