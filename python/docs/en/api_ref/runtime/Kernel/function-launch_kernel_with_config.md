# Function: launch\_kernel\_with\_config

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

Configures the compute task of an operator and starts the task. This API is asynchronous.

If you use this API to deliver a computation task of an AI Core operator, you need to use [acl.rt.binary\_load\_from\_file](function-binary_load_from_file.md) to load and parse the operator binary file.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtLaunchKernelWithConfig(aclrtFuncHandle funcHandle, uint32_t numBlocks, aclrtStream stream, aclrtLaunchKernelCfg *cfg, aclrtArgsHandle argsHandle, void *reserve)
    ```

- **Python Function**

    ```python
    ret = acl.rt.launch_kernel_with_config(func_handle, num_blocks, stream, cfg, args_handle, reserve)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| func_handle | Int, kernel function handle.|
| num_blocks | Int, number of cores on which the kernel function will be executed.|
| stream | Int, stream for executing the task.|
| cfg | List, configuration to be delivered by the task. If no configuration is specified, an empty list is allowed. The data type of each element in the list is dictionary. For details, see [aclrtLaunchKernelCfg](../datatypes/aclrtLaunchKernelCfg.md).|
| args_handle | Int, handle of the parameter list.|
| reserve | Int, reserved parameter. Currently, the value is fixed at `0`.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
