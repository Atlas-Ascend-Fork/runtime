# Function: infer\_shape

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

Infers the output shape of an operator based on the input shape and other necessary arguments.

## Prototype

- **C Prototype**

    ```c
    aclError aclopInferShape(const char *opType, int numInputs, aclTensorDesc *inputDesc[], aclDataBuffer *inputs[], int numOutputs, aclTensorDesc *outputDesc[], aclopAttr *attr)
    ```

- **Python Function**

    ```python
    ret = acl.op.infer_shape(op_type, in_desc_list, in_list, num_outputs, out_desc_list, attr)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| op_type | Int, operator type.|
| in_desc_list | List, input tensor description. Call [acl.create_tensor_desc](function-create_tensor_desc.md) to create data of the `aclTensorDesc` type in advance.|
| in_list | List, input tensors. Determine the allocation of memory for storing the input tensor data of the operator. If the app runs on the host, allocate host memory. If the app runs on the device, allocate device memory. For details about memory allocation APIs, see [Memory Management](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/API/runtimeapi/aclpythondevg_01_0109.html).|
| num_outputs | Int, number of operator output tensors.|
| out_desc_list | List, output tensor description. Call [acl.create_tensor_desc](function-create_tensor_desc.md) to create data of the `aclTensorDesc` type in advance. The number of elements in the `out_desc_list` list must be the same as the value of `num_outputs`.|
| attr | Int, attribute address object of the operator.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Constraints

- Consider the following possibilities:
    - If the accurate output shape of the operator can be inferred, the accurate output shape is returned.
    - If the accurate output shape of the operator cannot be inferred, but the range of the output shape can be obtained, the dynamic dimension in the tensor description is set to `–1` in the output parameter `out_desc_list`. In this scenario, you can call [get\_tensor\_desc\_dim\_range](function-get_tensor_desc_dim_range.md) to obtain the size range of the specified dimension from the tensor description.
    - (Reserved) If the accurate output shape and shape range cannot be obtained, the dynamic dimension in the tensor description is set to `–2` in the output parameter `out_desc_list`.

- Before this API is called to infer the output shape of a dynamic-input or dynamic-output operator, [set\_tensor\_desc\_name](function-set_tensor_desc_name.md) must be called to set the names of all input and output tensors as follows. For details about the input and output names defined in the operator IR prototypes, see "Ascend IR Operator Specifications" in the *Operator Specifications*.

    - For a required input, optional input, or required output, use the exact name defined in the operator IR prototypes.
    - For a dynamic input or dynamic output, use the exact name defined in the operator IR prototypes with a sequence number suffix. Dynamic inputs/outputs are indexed starting at 0.

    For example, if an operator has two inputs (the first one is required input `x`, the second one is dynamic input `y`, including two inputs) and one required output `z`, the code for calling the [set\_tensor\_desc\_name](function-set_tensor_desc_name.md) API is as follows.

    ```python
    acl.set_tensor_desc_name(input_tensor_desc[0], "x");
    acl.set_tensor_desc_name(input_tensor_desc[1], "y0");
    acl.set_tensor_desc_name(input_tensor_desc[2], "y1");
    acl.set_tensor_desc_name(output_tensor_desc[0], "z");
    ```
