# Function: create_and_get_op_desc

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

Obtains the description of an operator, including the operator name, input tensor description, and output tensor description. If the specified operator cannot be found, an error is returned. This API does not support the dynamic shape scenario.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlCreateAndGetOpDesc(uint32_t deviceId, uint32_t streamId, uint32_t taskId, char *opName, size_t opNameLen, aclTensorDesc **inputDesc, size_t *numInputs, aclTensorDesc **outputDesc, size_t *numOutputs)
    ```

- **Python Function**

    ```python
    op_name, input_desc, num_inputs, output_desc, num_outputs, ret = acl.mdl.create_and_get_op_desc(device_id, stream_id, task_id, op_name_len)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| device_id | Int, device ID. Call `acl.rt.get_device_id_from_exception_info` to obtain the device ID in the exception information.|
| stream_id | Int, stream ID. Call `acl.rt.get_stream_id_from_exception_info` to obtain the stream ID in the exception information.|
| task_id | Int, task ID. Call `acl.rt.get_task_id_from_exception_info` to obtain the task ID in the exception information.|
| op_name_len | Int, length of the operator name string. If the specified length is shorter than the actual length of the operator name, an error is returned.|

## Return Values

| Return Value| Description|
| --- | --- |
| op_name | String, operator name string.|
| input_desc | Int, description of all input tensors of the operator, pointing to the start address of a contiguous memory space.|
| num_inputs | Int, number of inputs.|
| output_desc | Int, description of all output tensors of the operator, pointing to the start address of a contiguous memory space.|
| num_outputs | Int, number of outputs.|
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Constraints

Application scenario: For example, if an AI Core error is reported during network inference (dynamic shape scenarios unsupported), you can call this API to obtain the description of the error operator and then perform further troubleshooting.

The recommended API call sequence is as follows:

1. Define and implement the exception callback function `fn(aclrtExceptionInfoCallback type)`. For details about the callback function prototype, see `acl.rt.set_exception_info_callback`.

    The key steps for implementing the callback function are as follows:

    1. Call the `acl.rt.get_device_id_from_exception_info`, `acl.rt.get_stream_id_from_exception_info`, and `acl.rt.get_task_id_from_exception_info` APIs in the exception callback function `fn` to obtain the device ID, stream ID, and task ID, respectively.
    2. Call [acl.mdl.create\_and\_get\_op\_desc](function-create_and_get_op_desc.md) in the exception callback function `fn` to obtain the operator description.
    3. Call [acl.get\_tensor\_desc\_by\_index](function-get_tensor_desc_by_index.md) in the exception callback function `fn` to obtain the input/output tensor description of the operator.
    4. In `fn`, obtain the tensor description for further analysis.

        For example, call [acl.get\_tensor\_desc\_address](function-get_tensor_desc_address.md) to obtain the memory address of the tensor data (you can obtain the tensor data from the memory address), call [acl.get\_tensor\_desc\_type](function-get_tensor_desc_type.md) to obtain the data type in the tensor description, call [acl.get\_tensor\_desc\_format](function-get_tensor_desc_format.md) to obtain the format in the tensor description, call [acl.get\_tensor\_desc\_num\_dims](function-get_tensor_desc_num_dims.md) to obtain the number of shape dimensions in the tensor description, and call [acl.get\_tensor\_desc\_dim\_v2](function-get_tensor_desc_dim_v2.md) to obtain the size of a specified dimension in the shape.

2. Call `acl.rt.set_exception_info_callback` to set the exception callback function.
3. Perform model inference.

 If an AI Core error is reported, `fn` is triggered to obtain the operator information for further troubleshooting.
