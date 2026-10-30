# Function: set\_kernel\_workspace\_sizes

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

Sets the workspace parameters of an operator in dynamic shape scenarios.

## Prototype

- **C Prototype**

    ```c
    aclError aclopSetKernelWorkspaceSizes(aclopKernelDesc *kernelDesc, int numWorkspaces, size_t *workspaceSizes)
    ```

- **Python Function**

    ```python
    ret = acl.op.set_kernel_workspace_sizes(kernel_desc, num_workspaces, workspace_sizes)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| kernel_desc | Int, kernel description buffer, pointer address of the `aclopKernelDesc` type.|
| num_workspaces | Int, number of workspaces.|
| workspace_sizes | Int, address of the array of workspace sizes.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Constraints

This is an optional interface and can be selected as required.
