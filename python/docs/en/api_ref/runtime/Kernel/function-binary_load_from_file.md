# Function: binary\_load\_from\_file

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

Loads and parses the operator binary file from a file and outputs the binHandle that points to the operator binary file.

For AI Core operators, if this API is used to load and parse the operator binary file, the [acl.rt.launch\_kernel\_with\_config](function-launch_kernel_with_config.md) API must be used to deliver the compute task.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtBinaryLoadFromFile(const char* binPath, aclrtBinaryLoadOptions *options, aclrtBinHandle *binHandle)
    ```

- **Python Function**

    ```python
    bin_handle, ret = acl.rt.binary_load_from_file(bin_path, options)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| bin_path | Str, path of the operator binary file (.o file). The path must be an absolute path. For AI CPU operators, this parameter can be set to an operator library file (.json).|
| options | List, optional parameters for loading the operator binary file. For details about the structure, see [aclrtBinaryLoadOptions](../datatypes/aclrtBinaryLoadOptions.md). If the parameter is left blank, set options to [].|

## Return Values

| Return Value| Description|
| --- | --- |
| bin_handle | Int, handle of the operator binary file.|
| ret | int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|

## Constraints

Operator binaries must be executed on the same hardware model for which they are compiled.
