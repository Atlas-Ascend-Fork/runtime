# Function: binary\_load\_from\_data

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

Loads and parses the AI CPU operator binary data from the memory and outputs the binHandle that points to the operator binary data.

When this API is called to load AI CPU operator information (`option\_type` in `aclrtBinaryLoadOptions` contains `ACL\_RT\_BINARY\_LOAD\_OPT\_CPU\_KERNEL\_MODE`), the [acl.rt.register\_cpu\_func](function-register_cpu_func.md) API must be used to register the AI CPU operator information.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtBinaryLoadFromData(const void *data, size_t length, const aclrtBinaryLoadOptions *options, aclrtBinHandle *binHandle)
    ```

- **Python Function**

    ```python
    bin_handle, ret = acl.rt.binary_load_from_data(mem_addr, length, options)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| mem_addr | Int, address of the host memory for storing the operator binary data. The value cannot be null.|
| length | Int, memory size of the operator binary data, in bytes. The value must be greater than 0.|
| options | List, optional parameters for loading the operator binary file. For details about the structure, see [aclrtBinaryLoadOptions](../datatypes/aclrtBinaryLoadOptions.md). If the parameter is left blank, set options to [].|

## Return Values

| Return Value| Description|
| --- | --- |
| bin_handle | Int, handle of the operator binary file.|
| ret | int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
