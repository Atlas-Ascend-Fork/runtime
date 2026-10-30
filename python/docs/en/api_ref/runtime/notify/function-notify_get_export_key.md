# Function: notify\_get\_export\_key

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

Sets a specified Notify object in the current process as an inter-process communication (IPC) one, and returns the key (Notify share name) to synchronize tasks between processes on multiple devices. Before calling this API, call [acl.rt.device\_enable\_peer\_access](../device/function-device_enable_peer_access.md) to enable data exchange between two devices.

**This API must be used together with the key APIs described below.** The following uses process A on device 0 and process B on device 1 as an example to describe the API call sequence for synchronizing tasks between the two processes.

1. In process A:
    a. Call [acl.rt.create_notify](function-create_notify.md) to create a Notify object.
    b. Call [acl.rt.notify_get_export_key](function-notify_get_export_key.md) to export the key (that is, the Notify share name).
    c. Obtain the ID of process B and call [acl.rt.notify_set_import_pid](function-notify_set_import_pid.md) to add the ID of process B to the trustlist.
    d. Call [acl.rt.wait_and_reset_notify](function-wait_and_reset_notify.md) to deliver a waiting task.
    e. Call [acl.rt.destroy_notify](function-destroy_notify.md) to destroy the Notify object. All processes involving IPC Notify need to release Notify. The release occurs only when every involved process finishes its part of the operation.

2. In process B:
    a. Call [acl.rt.device_get_bare_tgid](../device/function-device_get_bare_tgid.md) to obtain the ID of process B. This API adapts to both PMs and VMs when obtaining the process ID. You only need to call this API to obtain the process ID and use the API with other APIs to share memory. If you obtain the process ID without calling this API, an exception may occur when you use the process ID.
    b. Call [acl.rt.notify\_import\_by\_key](function-notify_import_by_key.md) to obtain the key information and return the Notify pointer that can be used by the current process. Before calling [acl.rt.notify\_import\_by\_key](function-notify_import_by_key.md), ensure that the IPC Notify is not released in advance.
    c. Call [acl.rt.record\_notify](function-record_notify.md) to deliver a record task.
    d. Call [acl.rt.destroy_notify](function-destroy_notify.md) to destroy the Notify object.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtNotifyGetExportKey(aclrtNotify notify, char *key, size_t len, uint64_t flag)
    ```

- **Python Function**

    ```python
    key, ret = acl.rt.notify_get_export_key(notify, len, flags)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| notify | Int, pointer address of the Notify.|
| len | Int, length of the Notify share name. The minimum value is `65`.|
| flags | Int, whether to enable process trustlist verification. The options are as follows:<br>`0`: ACL_RT_NOTIFY_EXPORT_FLAG_DEFAULT (default value), indicating that the process trustlist verification is enabled.<br>If you set the parameter to this value, call the aclrtNotifySetImportPid API separately to add the ID of the process that uses the Notify share name to the trustlist.<br>`2`: ACL_RT_NOTIFY_EXPORT_FLAG_DISABLE_PID_VALIDATION, indicating that the process trustlist verification is disabled.<br>If you set the parameter to this value, you do not need to call the aclrtNotifySetImportPid API.|

## Return Values

| Return Value| Description|
| --- | --- |
| key | Str, Notify share name.|
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|

## Constraints

This operation is not supported in the Ascend virtual instance scenario.
