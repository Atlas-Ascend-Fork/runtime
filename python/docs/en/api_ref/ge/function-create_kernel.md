# Function: create\_kernel

## Applicable Products

<!-- npu="950" id1 -->
- Ascend 950PR&950DT products: Not supported
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

Creates the kernel function of a dynamic-shape operator for operator execution.

## Prototype

- **C Prototype**

    ```c
    aclError aclopCreateKernel(const char *opType,
    const char *kernelId,
    const char *kernelName,
    void *binData,
    int binSize,
    aclopEngineType enginetype,
    aclDataDeallocator deallocator)
    ```

- **Python Function**

    ```python
    ret = acl.op.create_kernel(op_type, kernel_id, kernel_name, bin_data, bin_size, enginetype, deallocator)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| op_type | Str, operator type.|
| kernel_id | Str, kernel ID.|
| kernel_name | Str, operator kernel name, which must be the same as the `kernelName` argument in the operator binary file.|
| bin_data | Int, memory address of the operator kernel file.|
| bin_size | Int, memory size (in bytes) of the operator kernel file.|
| enginetype | Int, operator execution engine. This parameter is valid only when `compile_flag` of `acl.op.update.params` is set to `ACL_COMPILE_SYS`.<br> 0: ACL_ENGINE_SYS, set when the execution target is not concerned.<br> 1: ACL_ENGINE_AICORE, compiles the operator into an AI Core operator.<br> 2: ACL_ENGINE_VECTOR, compiles the operator into a Vector Core operator.|
| deallocator | Int, whether to automatically release the `bin_data` memory.<br> 0: Data is not automatically released. The caller compiles the code to release the data.<br> 1: The `bin_data` memory is automatically released. A callback function is set internally to release the `bin_data` memory.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|
