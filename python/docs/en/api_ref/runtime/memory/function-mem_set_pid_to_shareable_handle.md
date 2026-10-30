# Function: mem\_set\_pid\_to\_shareable\_handle

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

Sets the trustlist of processes that can share memory.

In the process that calls the [acl.rt.mem\_export\_to\_shareable\_handle](function-mem_export_to_shareable_handle.md) API, call this API to set the process trustlist. This API must be used together with other APIs to implement memory sharing. For details, see the description of the [acl.rt.mem\_export\_to\_shareable\_handle](function-mem_export_to_shareable_handle.md) API.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtMemSetPidToShareableHandle(uint64_t shareableHandle, int32_t *pid, size_t pidNum)
    ```

- **Python Function**

    ```python
    ret = acl.rt.mem_set_pid_to_shareable_handle(shareable_handle, pid)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| shareable_handle | Int, shareable handle exported through [acl.rt.mem_export_to_shareable_handle](function-mem_export_to_shareable_handle.md).|
| pid | List, array for storing trustlisted process IDs.<br>You can call [acl.rt.device_get_bare_tgid](../device/function-device_get_bare_tgid.md) to obtain the process ID. In the Docker scenario, the process ID on the physical machine is obtained. In the non-Docker scenario, the process ID is obtained.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
