# Function: execute\_v2

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

Performs model inference based on the attributes configured by the [acl.mdl.set\_exec\_config\_opt](function-set_exec_config_opt.md) API until the inference result is returned. This API is enhanced based on [acl.mdl.execute](function-execute.md). It can control the timeout interval of stream tasks and event tasks during model inference.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlExecuteV2(uint32_t modelId, const aclmdlDataset*input, aclmdlDataset *output, aclrtStream stream, const aclmdlExecConfigHandle *handle)
    ```

- **Python Function**

    ```python
    ret = acl.mdl.execute_v2(model_id, input, output, stream, handle)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_id | Int, ID of the model to be executed for inference After the model loading API (such as [acl.mdl.load_from_file](function-load_from_file.md) or [acl.mdl.load_from_mem](function-load_from_mem.md)) is successfully called, the model ID is returned. The ID is used as the input of this API.|
| input | Int, pointer address of the input data for model inference. For details, see [acl.mdl.load_from_file](function-load_from_file.md).|
| output | Int, pointer address of the output data for model inference. For details, see [acl.mdl.load_from_file](function-load_from_file.md). When calling `acl.create_data_buffer` to create an ACL data buffer for storing the output data of the corresponding index, you can set `data` to `0` and set `size` to `0` to create an empty ACL data buffer. During model execution, the system calculates and allocates the memory for the index output. This method saves memory. However, you need to free the memory and reset the `aclDataBuffer` after using the data. In addition, memory copy is involved when the system allocates memory, which may cause performance loss. The sample code for releasing the memory and resetting aclDataBuffer is as follows: data_buffer = acl.mdl.get_dataset_buffer(output, 0) # Obtain the data buffer based on the index. data_addr = acl.get_data_buffer_addr(data_buffer) # Obtain the device pointer address of the data. acl.rt.free(data_addr) # Free the device memory. acl.update_data_buffer(data_buffer, 0, 0) # Reset the data buffer for the next inference.|
| stream | Int, pointer address of the created stream. To specify a new stream, you can create and obtain the pointer address of the stream by calling `acl.rt.create_stream`.|
| handle | Int, pointer address of the configuration object executed by the model. The value must be the same as that of handle in [acl.mdl.set_exec_config_opt](function-set_exec_config_opt.md).|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Constraints

- This API must be used together with other APIs to implement model execution. The API call sequence is as follows:
    1. Call [acl.mdl.create\_exec\_config\_handle](function-create_exec_config_handle.md) to create the pointer address of the configuration object executed by the model.
    2. Call [acl.mdl.set\_exec\_config\_opt](function-set_exec_config_opt.md) multiple times to set the value of each attribute in the configuration object.
    3. Call `acl.mdl.execute_v2` to specify the configuration information required for model execution and execute the model.
    4. Call [acl.mdl.destroy\_exec\_config\_handle](function-destroy_exec_config_handle.md) to destroy the configuration object after the model is successfully loaded.

- Other restrictions are the same as those of [acl.mdl.execute](function-execute.md).

## Reference

- For details about the API call sequence and sample code, see [Model Execution](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/others/acldevg/aclpythondevg_0032.html).
- For stream creation and management, see [Stream Management](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/others/acldevg/aclpythondevg_0017.html).
