# Function: binary\_unload

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

Deletes the operator binary data pointed to by binHandle and the operator binary data copied to the device by calling [acl.rt.binary\_load](function-binary_load.md). Only Ascend C custom operators are supported.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtBinaryUnLoad(aclrtBinHandle binHandle)
    ```

- **Python Function**

    ```python
    ret = acl.rt.binary_unload(bin_handle)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| bin_handle | Int, handle pointing to the operator binary. This handle is generated when the [acl.rt.binary_load](function-binary_load.md) API is called.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

When this API is called to delete the binary data of an operator, it must be in the same context as [acl.rt.binary\_load](function-binary_load.md). In this way, the binary data of the operator copied to the device by calling [acl.rt.binary\_load](function-binary_load.md) can be deleted at the same time. Otherwise, the binary data of the operator on the device may fail to be deleted.
