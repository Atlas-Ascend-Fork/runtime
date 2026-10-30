# Function: notify\_import\_by\_key

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

Obtains the key information in the current process and returns the Notify pointer address that can be used by this process.

This API must be used with other APIs to synchronize tasks between processes on multiple devices. For details, see [acl.rt.notify\_get\_export\_key](function-notify_get_export_key.md).

## Prototype

- **C Prototype**

    ```c
    aclError aclrtNotifyImportByKey(aclrtNotify *notify, const char *key, uint64_t flag)
    ```

- **Python Function**

    ```python
    notify, ret = acl.rt.notify_import_by_key(key, flags)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| key | Str, Notify share name.<br>You must call the [acl.rt.notify_get_export_key](function-notify_get_export_key.md) API to obtain the share name of the specified Notify, and then pass the share name as a parameter.|
| flags | Int, whether to enable data exchange between two devices.<br>The values are as follows:<br>`0x0`: ACL_RT_NOTIFY_IMPORT_FLAG_DEFAULT, default value, which means disabling data exchange between two devices.<br>If this value is used, call [acl.rt.device_enable_peer_access](../device/function-device_enable_peer_access.md) separately to enable data exchange between the two devices.<br>`0x02`: ACL_RT_NOTIFY_IMPORT_FLAG_ENABLE_PEER_ACCESS, which means enabling data exchange between two devices.<br>If this value is used, you do not need to call [acl.rt.device_enable_peer_access](../device/function-device_enable_peer_access.md).|

## Return Values

| Return Value| Description|
| --- | --- |
| notify | Int, Notify pointer.|
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|

## Constraints

This operation is not supported in the Ascend virtual instance scenario.
