# Function: binary\_load

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

Parses and loads the operator binary file, outputs `binHandle` pointing to the operator binary file, and copies the operator binary file data to the device corresponding to the current context. Only Ascend C custom operators are supported.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtBinaryLoad(const aclrtBinary binary, aclrtBinHandle *binHandle)
    ```

- **Python Function**

    ```python
    bin_handle, ret = acl.rt.binary_load(binary)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| binary | Int, binary information of the operator. Call [acl.rt.create_binary](function-create_binary.md) to obtain the pointer to data of the acl.rt.binary type.|

## Return Values

| Return Value| Description|
| --- | --- |
| bin_handle | Int, pointer address of the binary handle.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
