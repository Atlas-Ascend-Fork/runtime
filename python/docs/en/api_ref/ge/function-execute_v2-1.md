# Function: execute\_v2

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

As the inputs, outputs, and attributes of each operator are different, the app needs to organize operators in strict accordance with their inputs, outputs, and attributes. When `acl.op.execute_v2` is called, it searches for the corresponding task based on the operator type, input tensor description, output tensor description, and attribute information, and delivers the task for execution.

## Prototype

- **C Prototype**

    ```c
    aclError aclopExecuteV2(const char *opType, int numInputs, aclTensorDesc *inputDesc[], aclDataBuffer *inputs[], int numOutputs, aclTensorDesc *outputDesc[], aclDataBuffer *outputs[], aclopAttr *attr, aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret = acl.op.execute_v2(op_type, input_desc, inputs, output_desc, outputs, attr, stream)
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

- In multi-thread scenarios, this API cannot be called to specify the same stream or the default stream. Otherwise, exceptions may occur in task execution.

- For an operator that supports dynamic shape, if the output shape of the operator cannot be determined, call `acl.op.infer_shape` to obtain the output shape.
    - If the accurate output shape can be obtained, use the obtained accurate output shape to construct an `outputDesc`, as one of the arguments passed to the `acl.op.execute_v2` call. In this scenario, the `acl.op.execute_v2` API is an asynchronous API. For an asynchronous API, the API call delivers a task rather than executes a task. After this API is called, call the synchronization API (for example, `acl.rt.synchronize_stream`) to ensure that the task is complete.
    - If the accurate output shape cannot be obtained and only the shape range can be obtained, the maximum value within the range is used to construct an `outputDesc`, as one of the arguments passed to the `acl.op.execute_v2` call. In this scenario, after calling `acl.op.execute_v2` to execute the operator, the system calculates the accurate output shape, as the `outputDesc` output of `acl.op.execute_v2`. In this case, `acl.op.execute_v2` is a synchronous API.
    - (Reserved) If the accurate output shape and shape range cannot be obtained, you need to estimate a maximum shape to construct an `outputDesc` as one of the arguments passed to the `acl.op.execute_v2` call. In this scenario, after calling `acl.op.execute_v2` to execute the operator, the system calculates the accurate output shape, as the `outputDesc` output of `acl.op.execute_v2`. In this case, `acl.op.execute_v2` is a synchronous API.

- If an operator with an unused optional input is executed:
    - Create data of the `aclTensorDesc` type by using the [acl.create\_tensor\_desc](function-create_tensor_desc.md)`(ACL_DT_UNDEFINED, 0, [], ACL_FORMAT_UNDEFINED)` call, indicating that the data type is `ACL_DT_UNDEFINED`, the format is `ACL_FORMAT_UNDEFINED`, and the shape is `[]`.
    - Create data of the `aclDataBuffer` type by using the `acl.create_data_buffer([], 0)` call, where the `aclDataBuffer` data does not need to be freed.

- Before executing an operator with constant input, call [acl.set\_tensor\_const](function-set_tensor_const.md) to set the constant input.

    The constant input passed must be consistent with that in `aclopExecuteV2` calls.

    <!-- npu="950,A3,910b,910,310p,310b" id7 -->
    If an operator has a constant input but [acl.set\_tensor\_const](function-set_tensor_const.md) has not been called to set the constant input, call [acl.set\_tensor\_place\_ment](function-set_tensor_place_ment.md) to set the placement attribute of `TensorDesc` and set `memType` to the host memory.
    <!-- end id7 -->

<!-- npu="950,A3,910b,910,310p,310b" id8 -->   
- Typically, it is a best practice to store the input/output tensor data to feed for running a single-operator (for example, the add operator) in the device memory. Some operators, however, take not only tensor data in the device memory (such as the feature map and weights) but also tensor data in the host memory (such as tensor shape and learning rate). In this case, you do not need to manually transfer such tensor data from the host to the device. You only need to call [acl.set\_tensor\_place\_ment](function-set_tensor_place_ment.md) to set the placement attribute of the corresponding `TensorDesc` to the host memory to instruct it to transfer the tensor data from the host to the device at operator runtime.
<!-- end id8 -->

## Reference

For details about the API calling process and examples, see [Single-Operator Calling](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/others/acldevg/aclpythondevg_0067.html).
