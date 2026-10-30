# Function: ipc\_mem\_close

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

Disables IPC-based memory sharing. Processes that call [acl.rt.ipc\_mem\_import\_by\_key](function-ipc_mem_import_by_key.md) or [acl.rt.ipc\_mem\_get\_export\_key](function-ipc_mem_get_export_key.md) also need to call this API. For the same shared memory key, the process that calls [acl.rt.ipc\_mem\_get\_export\_key](function-ipc_mem_get_export_key.md) can call [acl.rt.ipc\_mem\_close](function-ipc_mem_close.md) only after all processes that call [acl.rt.ipc\_mem\_import\_by\_key](function-ipc_mem_import_by_key.md) call [acl.rt.ipc\_mem\_close](function-ipc_mem_close.md). Otherwise, an exception may occur. This API must be used together with other APIs to implement memory sharing. For details about the process, see the description of [acl.rt.ipc_mem_get_export_key](function-ipc_mem_get_export_key.md).

## Prototype

- **C Prototype**

    ```c
    aclError aclrtIpcMemClose(const char *key)
    ```

- **Python Function**

    ```python
    ret = acl.rt.ipc_mem_close(key)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| key | Str, shared memory key, which is obtained by calling [acl.rt.ipc_mem_get_export_key](function-ipc_mem_get_export_key.md).|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
