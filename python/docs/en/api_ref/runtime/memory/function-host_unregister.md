# Function: host\_unregister

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

Unregisters host memory. This API must be used in pair with [acl.rt.host\_register](function-host_register.md).

## Prototype

- **C Prototype**

    ```c
    aclError aclrtHostUnregister(void *ptr)
    ```

- **Python Function**

    ```python
    ret = acl.rt.host_unregister(ptr)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| ptr | Int, host memory address.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
