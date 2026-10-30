# Function: set\_exception\_info\_callback

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

Sets the exception callback function.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtSetExceptionInfoCallback(aclrtExceptionInfoCallback callback)
    ```

- **Python Function**

    ```python
    ret = acl.rt.set_exception_info_callback(fn)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| callback | Function, callback function on the Python side. The format is as follows:<br>def exception_callback(exception_info)<br>"""<br>:exception_info: pointer address of aclrtExceptionInfo.<br>:return:<br>""" |

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- Callback functions involve shared resources (such as locks). Exercise caution when using callback functions. Do not call APIs for resource application & release, stream synchronization, device synchronization, task delivery, and task termination in callback functions. Otherwise, errors or deadlocks may occur.
- Before executing an asynchronous task, you need to set the exception callback function. When an exception occurs during task execution on the device, the system passes the pointer address of aclrtExceptionInfo that contains the task ID, stream ID, thread ID, device ID, and error code to the exception callback function and executes the callback function. You can call the [acl.rt.get\_task\_id\_from\_exception\_info](function-get_task_id_from_exception_info.md), [acl.rt.get\_stream\_id\_from\_exception\_info](function-get_stream_id_from_exception_info.md), [acl.rt.get\_thread\_id\_from\_exception\_info](function-get_thread_id_from_exception_info.md), [acl.rt.get\_device\_id\_from\_exception\_info](function-get_device_id_from_exception_info.md) and [acl.rt.get\_error\_code\_from\_exception\_info](function-get_error_code_from_exception_info.md) APIs to obtain the ID of the task where the exception occurs, stream ID, thread ID, device ID, and error code for fault locating.

    **Application scenario example**: Before calling the acl.op.execute_v2 API, call the acl.rt.set\_exception\_info\_callback API to set the exception callback function. When an exception occurs during operator execution on the device, the system passes a pointer address of aclrtExceptionInfo that contains the task ID, stream ID, thread ID, device ID, and error code to the exception callback function, and executes the callback function.

- If the exception callback function is set repeatedly, the most recent setting applies.
- To clear the callback function, call acl.rt.set\_exception\_info\_callback again to reset it (pass None or no parameter).

## API Call Sequence

Application scenario: For example, if an AI Core error is reported during network inference (dynamic shape scenarios unsupported), you can call this API to obtain the description of the error operator and then perform further troubleshooting.

The recommended API call sequence is as follows:

1. Define and implement the exception callback function `fn\(aclrtExceptionInfoCallback type\)`. For details about the callback function prototype, see [acl.rt.set\_exception\_info\_callback](function-set_exception_info_callback.md).

    The key steps for implementing the callback function are as follows:

    a. Call the [acl.rt.get\_device\_id\_from\_exception\_info](function-get_device_id_from_exception_info.md), [acl.rt.get\_stream\_id\_from\_exception\_info](function-get_stream_id_from_exception_info.md) and [acl.rt.get\_task\_id\_from\_exception\_info](function-get_task_id_from_exception_info.md) APIs in the exception callback function `fn` to obtain the device ID, stream ID, and task ID, respectively.
    b. Call acl.mdl.create_and_get_op_desc in the exception callback function `fn` to obtain the operator description.
    c. Call acl.get_tensor_desc_by_index in the exception callback function `fn` to obtain the input/output tensor description of the operator.
    d. In `fn`, obtain the tensor description for further analysis.

    For example, call acl.get_tensor_desc_address to obtain the tensor data address, call acl.get_tensor_desc_type to obtain the data type in the tensor description, call acl.get_tensor_desc_format to obtain the tensor format, call acl.get_tensor_desc_num_dims to obtain the tensor dimension count, and call acl.get_tensor_desc_dim_v2 to obtain the size of a specified dimension.

2. Call acl.rt.set_exception_info_callback to set the exception callback function.
3. Perform model inference.

    If an AI Core error is reported, `fn` is triggered to obtain the operator information for further troubleshooting.

## Sample Code

Add exception handling branches following the API calls. The sample code of key steps is as follows, which is for reference only. Do not directly copy and run the code.

For details about how to allocate and deallocate runtime resources, see "Application Development (Python) > Runtime Resource Allocation and Deallocation". For details about the API call sequence for model loading, see "Application Development (Python) > Model Management > API Call Sequence". For details about the API call sequence for model inference and API call sequence for preparing the input and output data for model inference, see "Application Development (Python) > Model Management > Model Execution > Preparing Input/Output Data Structure for Model Execution".

```python
import acl
import numpy as np
# ......

# 1. Allocate runtime resources.
# ......

# 2. Load a model. After the model is successfully loaded, `model_id` that identifies the model is returned.
# ......

# 3. Create data of type `aclmdlDataset` to describe the inputs and outputs of the model.
# ......

# 4. Implement the exception callback function.
def exception_callback(info):
    stream_id = acl.rt.get_stream_id_from_exception_info(info)
    device_id = acl.rt.get_device_id_from_exception_info(info)
    task_id = acl.rt.get_task_id_from_exception_info(info)
    # You can write the obtained operator information to a file, or start another thread to listen to the exception callback. When an error occurs, the thread handling function is triggered, and the operator information is printed to the screen.
    op_name, input_desc, num_inputs, output_desc, num_outputs, ret = \
        acl.mdl.create_and_get_op_desc(device_id, stream_id, task_id, 256)

    # You can call related tensor APIs provided by acl to obtain the operator information as required.
    for i in range(num_inputs):
        desc = acl.get_tensor_desc_by_index(input_desc, i)
        address = acl.get_tensor_desc_address(desc)
        num_dims = acl.get_tensor_desc_num_dims(desc)
        dim_0, ret = acl.get_tensor_desc_dim_v2(desc, 0)

    for i in range(num_outputs):
        desc = acl.get_tensor_desc_by_index(output_desc, i)
        address = acl.get_tensor_desc_address(desc)
        num_dims = acl.get_tensor_desc_num_dims(desc)
        dim_0, ret = acl.get_tensor_desc_dim_v2(desc, 0)

    acl.destroy_tensor_desc(input_desc)
    acl.destroy_tensor_desc(output_desc)

# 5. Set the exception callback function.
ret = acl.rt.set_exception_info_callback(exception_callback)

# 6. Execute the model.
ret = acl.mdl.execute(model_id, input, output)

# 7. Process the model inference result.
# ......

# 8. Destroy allocations such as the model inputs and outputs, free memory, and unload the model.
# ......

# 9. Deallocate runtime resources.
# ......
```
