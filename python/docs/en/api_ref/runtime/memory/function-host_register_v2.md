# Function: host\_register\_v2

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

Registers a host memory address.

To unregister the memory, call [acl.rt.host\_unregister](function-host_unregister.md).

## Prototype

- **C Prototype**

    ```c
    aclError aclrtHostRegisterV2(void *ptr, uint64_t size, uint32_t flag)
    ```

- **Python Function**

    ```python
    ret = acl.rt.host_register_v2(ptr, size, flag)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| ptr | Host memory address.<br>The host memory address must be 4 KB page-aligned.<br>If the OS kernel version is 5.10 or earlier, using non-page-locked memory will cause exceptions. Therefore, you must call aclrtMallocHost to allocate page-locked host memory.<br>If the OS kernel version is later than 5.10, non-page-locked host memory can be used. Therefore, you can either call aclrtMallocHost to allocate page-locked host memory or call malloc to allocate non-page-locked host memory.|
| size | Buffer size in bytes.|
| flag | Memory registration type.<br>`0x2: ACL_HOST_REG_MAPPED`: Map and register the host memory as a memory address that can be accessed by the device, and then call [acl.rt.host_get_device_pointer](function-host_get_device_pointer.md) to obtain the mapped device memory address.<br>`0x4: ACL_HOST_REG_IOMEMORY`: Maps and registers the I/O space (registers and caches) of a third-party PCIe device on the host as accessible to the device, including read and write. When this value is used, pinned memory is not supported. Therefore, this value cannot be used together with `ACL_HOST_REG_PINNED`. Reserved. Not supported yet.<br>`0x8: ACL_HOST_REG_READONLY`: Maps and registers the host memory as read-only to the device. Reserved. Not supported yet.<br>`0x10000000: ACL_HOST_REG_PINNED`: Registers the host non-pinned memory as pinned memory.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

<!-- npu="A3" id7 -->
## Constraints

<!-- npu="A3" id8 -->
For Atlas A3 series products, if flag is set to ACL_HOST_REG_IOMEMORY, only the x86 architecture is supported. The Arm architecture is not supported.
<!-- end id8 -->
<!-- end id7 -->
