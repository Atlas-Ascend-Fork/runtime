# Function: execute

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

Executes a specified operator. This is an asynchronous API.

>[!NOTE]NOTE
>This API will be deprecated in later versions. Use the [acl.op.execute\_v2](function-execute_v2-1.md) API instead.

## Prototype

- **C Prototype**

    ```c
    aclError aclopExecute(const char *opType, int numInputs, const aclTensorDesc *const inputDesc[], const aclDataBuffer *const inputs[], int numOutputs, const aclTensorDesc *const outputDesc[], aclDataBuffer *const outputs[], const aclopAttr *attr, aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret = acl.op.execute(op_type, input_desc, inputs, output_desc, outputs, attr,stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| op_type | Str, operator type.|
| input_desc | Int list, description of the operator input tensor. It contains multiple ACL tensor description address objects.|
| inputs | Int list, input tensor of the operator. It contains multiple `aclDataBuffer` data address objects.|
| output_desc | Int list, description of the operator output tensor. It contains multiple ACL tensor description address objects.|
| outputs | Int list, output tensor of the operator. It contains multiple `aclDataBuffer` data address objects.|
| attr | Int, attribute address object of the operator.|
| stream | Int, stream object to be loaded by the operator.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Constraints

- This API is asynchronous. A successful call indicates only that the task has been delivered, not that it has completed. After this API is called, call the synchronization API (for example, `acl.rt.synchronize_stream`) to ensure that the task is complete.
- In multi-thread scenarios, this API cannot be called to specify the same stream or the default stream. Otherwise, exceptions may occur in task execution.
- As the inputs, outputs, and attributes of each operator are different, the app needs to organize operators in strict accordance with their inputs, outputs, and attributes. When `acl.op.execute` is called, it searches for the corresponding task based on the operator type, input tensor description, output tensor description, and attribute information, and delivers the task for execution.
