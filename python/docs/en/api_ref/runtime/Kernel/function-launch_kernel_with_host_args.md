# Function: launch\_kernel\_with\_host\_args

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

Passes kernel function input parameters based on the host memory and starts the compute task of an operator. This API is asynchronous.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtLaunchKernelWithHostArgs(aclrtFuncHandle funcHandle, uint32_t numBlocks, aclrtStream stream, aclrtLaunchKernelCfg *cfg, void *hostArgs, size_t argsSize, aclrtPlaceHolderInfo *placeHolderArray, size_t placeHolderNum)
    ```

- **Python Function**

    ```python
    ret = acl.rt.launch_kernel_with_host_args(func_handle, num_blocks, stream, cfg, host_args_ptr, host_args_size, place_holder_list, place_holder_num)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| func_handle | Int, kernel function handle.|
| num_blocks | Int, number of cores on which the kernel function will be executed.|
| stream | Int, stream for executing the task.|
| cfg | List, configuration to be delivered by the task. The data type of each element in the list is dictionary. For details, see [aclrtLaunchKernelCfg](../datatypes/aclrtLaunchKernelCfg.md). If no configuration is specified, an empty list is allowed.|
| host_args_ptr | Pointer to the host memory address that stores all input parameters of the kernel function.|
| host_args_size | Int, size of the `host_args` parameter, in bytes.|
| place_holder_list | List, placeholder parameter list. The data type of each element in the list is dictionary. For details, see [aclrtPlaceHolderInfo](../datatypes/aclrtPlaceHolderInfo.md).|
| place_holder_num | Int, size of the placeholder parameter list.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
