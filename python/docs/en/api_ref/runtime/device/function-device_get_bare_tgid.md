# Function: device\_get\_bare\_tgid

## Applicable Products

<!-- npu="950" id1 -->
- Ascend 950PR&950DT products: Supported
<!-- end id1 -->
<!-- npu="A3" id2 -->
- Atlas A3 products: supported
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

Obtains the ID of the current process.

This API has been adapted to the physical machine and VM scenarios when obtaining the process ID. You only need to call it to obtain the process ID and then configure other APIs (see [acl.rt.mem\_export\_to\_shareable\_handle](../memory/function-mem_export_to_shareable_handle.md) for assisting processes) to share the physical memory. If you obtain the process ID without calling this API, an exception may occur when you use the process ID.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtDeviceGetBareTgid(int32_t *pid)
    ```

- **Python Function**

    ```python
    pid, ret = acl.rt.device_get_bare_tgid()
    ```

## Parameters

None

## Return Values

| Return Value| Description|
| --- | --- |
| pid | Int, process ID.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
