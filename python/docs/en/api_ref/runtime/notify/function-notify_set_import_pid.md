# Function: notify\_set\_import\_pid

## Applicable Products

<!-- npu="950" id1 -->
- Ascend 950PR&950DT products: Not supported
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

Sets the process trustlist of the Notify shared memory. Only the processes in the trustlist can use the Notify shared name exported by calling [acl.rt.notify_get_export_key](function-notify_get_export_key.md).

## Prototype

- **C Prototype**

    ```c
    aclError aclrtNotifySetImportPid(aclrtNotify notify, int32_t *pid, size_t num)
    ```

- **Python Function**

    ```python
    ret = acl.rt.notify_set_import_pid(notify, pid)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| notify | Int, Notify pointer address, which must be the same as that of Notify in [acl.rt.notify_get_export_key](function-notify_get_export_key.md).|
| pid | List, which is used to store the trustlisted process IDs.<br>Definition: pid = [pid_1, pid_2,...]<br>You can call [acl.rt.device_get_bare_tgid](../device/function-device_get_bare_tgid.md) to obtain the process ID. In the Docker scenario, the process ID on the physical machine is obtained. In the non-Docker scenario, the process ID is obtained.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|

## Constraints

This operation is not supported in the Ascend virtual instance scenario.
