# Function: binary\_get\_function

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

Finds the corresponding kernel object based on `kernel\_name` and use `func\_handle` to express the object.

For the same `bin\_handle`, when acl.rt.binary\_get\_function is called for the first time, the operator binary data associated with `bin\_handle` is copied to the device corresponding to the current context by default.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtBinaryGetFunction(const aclrtBinHandle binHandle, const char *kernelName, aclrtFuncHandle *funcHandle)
    ```

- **Python Function**

    ```python
    func_handle, ret = acl.rt.binary_get_function(bin_handle, kernel_name)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| bin_handle | Int, handle pointing to the operator binary. Call [acl.rt.binary_load](function-binary_load.md) to obtain `binHandle`.|
| kernel_name | Str, kernel name.|

## Return Values

| Return Value| Description|
| --- | --- |
| func_handle | Int, pointer address of the func_handle expression of the specified kernel.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
