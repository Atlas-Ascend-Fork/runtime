# Function: get\_function\_name

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

Obtains a kernel function name based on the kernel function handle.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtGetFunctionName(aclrtFuncHandle funcHandle, uint32_t maxLen, char *name)
    ```

- **Python Function**

    ```python
    func_name, ret = acl.rt.get_function_name(func_handle, max_len)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| func_handle | Int, kernel function handle.|
| max_len | Int, maximum memory size (in bytes) for storing the kernel function name. The value range is [0, 1024).|

## Return Values

| Return Value| Description|
| --- | --- |
| func_name | Str, kernel function name.|
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
