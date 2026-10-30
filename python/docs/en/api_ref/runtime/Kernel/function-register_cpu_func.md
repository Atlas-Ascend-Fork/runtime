# Function: register\_cpu\_func

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

If the [acl.rt.binary\_load\_from\_data](function-binary_load_from_data.md) API is used to load the binary data of an AI CPU operator, this API must be used to register the AI CPU operator information to obtain the corresponding func\_handle. This API applies only to AI CPU operators. For other operators, the error code ACL\_ERROR\_RT\_PARAM\_INVALID is returned.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtRegisterCpuFunc(const aclrtBinHandle handle, const char *funcName, const char *kernelName, aclrtFuncHandle *funcHandle)
    ```

- **Python Function**

    ```python
    func_handle, ret = acl.rt.register_cpu_func(bin_handle, func_name, kernel_name)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| bin_handle | Int, handle of the operator binary. Call [acl.rt.binary_load_from_data](function-binary_load_from_data.md) to obtain the binary handle of the operator, and then pass the handle to this API as an input parameter.|
| func_name | Str, entry point function for executing the AI CPU operator. It cannot be left blank.|
| kernel_name | Str, `opType` of the AI CPU operator. It cannot be left blank.|

## Return Values

| Return Value| Description|
| --- | --- |
| func_handle | Int, kernel function handle.|
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
