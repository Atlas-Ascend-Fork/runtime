# Function: host\_get\_device\_pointer

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
- Atlas inference products: Not supported
<!-- end id5 -->
<!-- npu="910" id6 -->
- Atlas training products: Not supported
<!-- end id6 -->

## Function

Obtains the device memory address mapped and registered by calling [acl.rt.host\_register](function-host_register.md) or [acl.rt.host\_register\_v2](function-host_register_v2.md). This address cannot be used for memory operations, such as memory copy.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtHostGetDevicePointer(void *pHost, void **pDevice, uint32_t flag)
    ```

- **Python Function**

    ```python
    ptr_device, ret =acl.rt.host_get_device_pointer (ptr_host, flag)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| ptr_host | Host memory address mapped and registered by calling [acl.rt.host_register](function-host_register.md) or [acl.rt.host_register_v2](function-host_register_v2.md).|
| flag | Reserved. The value is fixed at `0`.|

## Return Values

| Return Value| Description|
| --- | --- |
| ptr_device | Int, device memory address.|
| ret | Int. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
