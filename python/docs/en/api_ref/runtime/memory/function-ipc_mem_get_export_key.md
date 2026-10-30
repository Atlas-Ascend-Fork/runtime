# Function: ipc\_mem\_get\_export\_key

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
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas inference products: Supported
<!-- end id5 -->
<!-- npu="910" id6 -->
- Atlas training products: Supported
<!-- end id6 -->

## Function

Sets the specified device memory to IPC shared memory in the current process and returns the shared memory key, so that the memory can be shared with other processes. This API must be used together with the following key APIs to implement memory sharing. The following uses processes A and B as an example to describe the process of calling the memory sharing API between two processes.

1. In process A:

    a. If two processes on different devices share memory, call [acl.rt.device\_enable\_peer\_access](../device/function-device_enable_peer_access.md) to enable P2P.

    b. Call [acl.rt.malloc](../memory/function-malloc.md) to allocate P2P memory (configured by the policy parameter of the API).

    c. Call [acl.rt.ipc\_mem\_get\_export\_key](function-ipc_mem_get_export_key.md) to export the key of the shared memory.

    d. Obtain the ID of process B and call [acl.rt.ipc\_mem\_set\_import\_pid](function-ipc_mem_set_import_pid.md) to add the ID of process B to the trustlist.

    e. Call [acl.rt.ipc\_mem\_close](function-ipc_mem_close.md) to close the IPC shared memory. After process B calls [acl.rt.ipc\_mem\_close](function-ipc_mem_close.md) to close the IPC shared memory, process A closes the IPC shared memory. Otherwise, an exception may occur.

    f. Call [acl.rt.free](../memory/function-free.md) to free the memory.

2. In process B:

    a. If two processes on different devices share memory, call [acl.rt.device\_enable\_peer\_access](../device/function-device_enable_peer_access.md) to enable P2P.

    b. Call [acl.rt.device_get_bare_tgid](../device/function-device_get_bare_tgid.md) to obtain the ID of process B.

    This API adapts to both PMs and VMs when obtaining the process ID. You only need to call this API to obtain the process ID and use the API with other APIs to share memory. If you obtain the process ID without calling this API, an exception may occur when you use the process ID.

    c. Call aclrtIpcMemImportByKey to obtain the key information and return the device memory address pointer that can be used by the current process.

    Before calling [acl.rt.ipc\_mem\_import\_by\_key](function-ipc_mem_import_by_key.md), ensure that the memory to be shared exists and cannot be released in advance.

    d. Call [acl.rt.ipc\_mem\_close](function-ipc_mem_close.md) to close the IPC shared memory.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtIpcMemGetExportKey(void *devPtr, size_t size, char *key, size_t len, uint64_t flag)
    ```

- **Python Function**

    ```python
    key, ret = acl.rt.ipc_mem_get_export_key(dev_ptr, size, len, flags)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| dev_ptr | Int, device memory address.|
| size | Int, memory size, in bytes.|
| len | Int, length of the key. The value is fixed at `65`.|
| flags | Int, whether to enable process trustlist verification.<br>The options are as follows:<br>`0x0: ACL_RT_IPC_MEM_EXPORT_FLAG_DEFAULT` (default value): process trustlist verification is enabled. If this value is used, call [acl.rt.ipc_mem_set_import_pid](function-ipc_mem_get_export_key.md) separately to add the ID of the process that uses the shared memory key to the trustlist.<br>`0x1: ACL_RT_IPC_MEM_EXPORT_FLAG_DISABLE_PID_VALIDATION`: process trustlist verification is disabled. If this value is used, you do not need to call [acl.rt.ipc_mem_set_import_pid](function-ipc_mem_set_import_pid.md).|

## Return Values

| Return Value| Description|
| --- | --- |
| key | Str, shared memory key.|
| ret | Int. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

When two processes on different devices share memory through IPC, as shown in the figure below, process A on device 0 shares the memory with process B on device 1 through IPC. When the shared memory address is used in process B:

- [acl.rt.device\_enable\_peer\_access](../device/function-device_enable_peer_access.md) must be called to enable communication between the two devices.
- On Atlas inference products, when [aclrtMalloc](function-malloc.md) is called to allocate device memory, the policy must be set to the P2P type, for example, ACL\_MEM\_MALLOC\_HUGE\_FIRST\_P2P.
- The direction of memory copy cannot be automatically determined based on the source and destination memory address pointers. Synchronous and asynchronous memory copies between host and device are not supported. Only asynchronous copies are permitted on the same device.
- Cross-chip access of Cube and Vector units is supported.

![](../figures/IPC_shared_memory_diagram.png)

The preceding restrictions do not apply when two processes on the same device share memory through IPC.
