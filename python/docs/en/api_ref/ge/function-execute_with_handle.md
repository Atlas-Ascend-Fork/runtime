# Function: execute\_with\_handle

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

Calls an operator in handle mode. Dynamic-shape operators are not supported. To call dynamic-shape operators, use [acl.op.execute\_v2](function-execute_v2-1.md) instead. This is an asynchronous API.

## Prototype

- **C Prototype**

    ```c
    aclError aclopExecWithHandle(aclopHandle *handle, int numInputs, const aclDataBuffer *const inputs[], int numOutputs, aclDataBuffer *const outputs[], aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret = acl.op.execute_with_handle(handle, inputs, outputs, stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| handle | Int, handle of the operator to be executed. It is a pointer address. Call the [acl.op.create_handle](function-create_handle.md) API to create data of the aclopHandle type in advance.|
| inputs | Int list, input tensor of the operator. It contains multiple `aclDataBuffer` data address objects. Call `acl.create_data_buffer` to create data of the `aclDataBuffer` type in advance.|
| outputs | Int list, output tensor of the operator. It contains multiple `aclDataBuffer` data address objects. Call `acl.create_data_buffer` to create data of the `aclDataBuffer` type in advance.|
| stream | Int, stream where the operator is executed, stream address object.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Constraints

- This API is asynchronous. A successful call indicates only that the task has been delivered, not that it has completed. After this API is called, call the synchronization API (for example, `acl.rt.synchronize_stream`) to ensure that the task is complete.

- In multi-thread scenarios, this API cannot be called to specify the same stream or the default stream. Otherwise, exceptions may occur in task execution.
- When executing an operator with optional input, if the optional input is not used, create data of the `aclDataBuffer` type as follows:

    ```python
    acl.create_data_buffer(nullptr, 0)
    ```

 In addition, the data in aclDataBuffer does not need to be released because it is an empty data type.
