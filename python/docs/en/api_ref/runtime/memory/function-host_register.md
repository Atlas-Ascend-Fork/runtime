# Function: host\_register

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

Maps and registers host memory as the memory address that can be accessed by devices, and obtains the mapped device memory address. This address can only be accessed on devices, for example, as a parameter of a kernel function for the device AI Core to access. If host memory processing is involved, use the original host memory address.

To unregister the memory, call [acl.rt.host\_unregister](function-host_unregister.md).

## Prototype

- **C Prototype**

    ```c
    aclError aclrtHostRegister(void *ptr, uint64_t size, aclrtHostRegisterType type, void **devPtr)
    ```

- **Python Function**

    ```python
    dev_ptr, ret = acl.rt.host_register(ptr, size, type)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| ptr | Int, host memory address. The host memory address must be 4KB page-aligned. If the OS kernel version is 5.10 or earlier, using non-pinned memory will cause exceptions. Therefore, the [acl.rt.malloc_host](function-malloc_host.md) API must be called to allocate host memory. If the OS kernel version is later than 5.10, non-pinned host memory can be used. Therefore, the [acl.rt.malloc_host](function-malloc_host.md) API does not need to be called to allocate host memory.|
| size | Int, memory size, in bytes.|
| type | Int, memory registration type. For details about the type definition, see [aclrtHostRegisterType](../datatypes/aclrtHostRegisterType.md).|

## Return Values

| Return Value| Description|
| --- | --- |
| dev_ptr | Int, memory address mapped from the host and accessible to the device.|
| ret | Int. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
