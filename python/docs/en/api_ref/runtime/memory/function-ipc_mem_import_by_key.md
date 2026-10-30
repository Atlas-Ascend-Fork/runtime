# Function: ipc\_mem\_import\_by\_key

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

Obtains key information in the current process and returns the device memory address pointer that can be used by this process. This API must work with other APIs to implement memory sharing. For details, see the description of [Function: ipc\_mem\_get\_export\_key](function-ipc_mem_get_export_key.md).

## Prototype

- **C Prototype**

    ```c
    aclError aclrtIpcMemImportByKey(void **devPtr, const char *key, uint64_t flag)
    ```

- **Python Function**

    ```python
    dev_ptr, ret = acl.rt.ipc_mem_import_by_key(key, flags)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| key | Str, shared memory key.|
| flags | Whether to enable data exchange between two devices.<br>The values are as follows:<br>`0x0: ACL_RT_IPC_MEM_IMPORT_FLAG_DEFAULT` (default value): disables data exchange between two devices. If this value is used, call [acl.rt.device_enable_peer_access](../device/function-device_enable_peer_access.md) separately to enable data exchange between the two devices.<br>`0x1: ACL_RT_IPC_MEM_IMPORT_FLAG_ENABLE_PEER_ACCESS`: enables data exchange between two devices. If this value is used, you do not need to call [acl.rt.device_enable_peer_access](../device/function-device_enable_peer_access.md).|

## Return Values

| Return Value| Description|
| --- | --- |
| dev_ptr | Int, pointer to the device memory address.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
