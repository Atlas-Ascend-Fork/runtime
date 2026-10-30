# Function: execute\_async

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

Executes model inference. It is an asynchronous interface.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlExecuteAsync(uint32_t modelId, const aclmdlDataset *input, aclmdlDataset *output, aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret = acl.mdl.execute_async(model_id, input, output, stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_id | Int, ID of the model to be executed for inference After the model loading API (such as [acl.mdl.load_from_file](function-load_from_file.md) or [acl.mdl.load_from_mem](function-load_from_mem.md)) is successfully called, the model ID is returned. The ID is used as the input of this API.|
| input | Int, pointer address of the input data for model inference. For details, see [acl.mdl.load_from_file](function-load_from_file.md).|
| output | Int, pointer address of the output data for model inference. For details, see [acl.mdl.load_from_file](function-load_from_file.md).|
| stream | Int, pointer address of the created stream. To specify a new stream, you can create and obtain the pointer address of the stream by calling `acl.rt.create_stream`.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Constraints

- This API is asynchronous. A successful call indicates only that the task has been delivered, not that it has completed. After this API is called, call the synchronization API (for example, `acl.rt.synchronize_stream`) to ensure that the task is complete.
- For models with the same `model_id`, `acl.mdl.execute_async` cannot be called to perform model inference in the multi-stream concurrency scenario.
- If the same `model_id` needs to be shared by multiple threads, locks must be added between user threads to ensure that operations of refreshing the input and output memory and executing inference are performed continuously. For example:

    ```python
    # API call sequence of thread A:
    lock(handle1) -> acl.rt.memcpy_async(stream1) (Refresh the input and output memory) - > acl.mdl.execute_async(modelId1,stream1) (Execute inference) - > unlock(handle1)

    # API call sequence of thread B:
    lock(handle1) -> acl.rt.memcpy_async(stream1) (Refresh the input and output memory) - > acl.mdl.execute_async(modelId1,stream1) (Execute inference) - > unlock(handle1)
    ```

- The operations of loading, executing, and unloading a model must be performed in the same context. For details about how to create a context, see `acl.rt.create_context`.
- You can call `acl.rt.malloc`, `acl.rt.malloc_host`, `acl.rt.malloc_cached`, `acl.media.dvpp_malloc`, or `acl.himpi.dvpp_malloc`, to allocate the memory for storing the model input and output data.

 `acl.media.dvpp_malloc` and `acl.himpi.dvpp_malloc` are dedicated memory allocation APIs for media data processing. To reduce copy, the output of media data processing is used as the input of model inference to implement memory overcommitment.

- The address space accessible by media data processing is limited. To ensure sufficient memory during media data processing, you are advised to call other APIs (such as `acl.rt.malloc`) to allocate memory for other functions (such as model loading).

## Reference

- For the API calling process, see [API Calling Process](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/others/acldevg/aclpythondevg_0037.html).
- For the API call example, see [Sample Code](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/others/acldevg/aclpythondevg_0038.html).
- For stream creation and management, see [Stream Management](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/others/acldevg/aclpythondevg_0017.html).
