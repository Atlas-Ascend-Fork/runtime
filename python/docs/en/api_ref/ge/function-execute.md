# Function: execute

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

Executes model inference until the result is returned.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlExecute(uint32_t modelId, const aclmdlDataset *input, aclmdlDataset *output)
    ```

- **Python Function**

    ```python
    ret = acl.mdl.execute(model_id, input, output)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_id | Int, ID of the model to be executed for inference After the model loading API (such as [acl.mdl.load_from_file](function-load_from_file.md) or [acl.mdl.load_from_mem](function-load_from_mem.md)) is successfully called, the model ID is returned. The ID is used as the input of this API.|
| input | Int, pointer address of the input data for model inference. For details, see [aclmdlDataset](aclmdlDataset.md).|
| output | Int, pointer address of the output data for model inference. For details, see [acl.mdl.load_from_file](function-load_from_file.md). When calling `acl.create_data_buffer` to create an ACL data buffer for storing the output data of the corresponding index, you can set `data` to `0` and set `size` to `0` to create an empty ACL data buffer. During model execution, the system calculates and allocates the memory for the index output. This method saves memory. However, you need to free the memory and reset the `aclDataBuffer` after using the data. In addition, memory copy is involved when the system allocates memory, which may cause performance loss.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Constraints

- If the same `model_id` is shared by multiple threads due to service requirements, locks must be added between user threads to ensure that operations of refreshing the input and output memory and executing inference are performed continuously. For example:

    ```python
    # API call sequence of thread A:
    lock(handle1) -> acl.rt.memcpy (Refresh the input and output memory.) - > acl.mdl.execute (Execute inference.) - > unlock(handle1)

    # API call sequence of thread B:
    lock(handle1) -> acl.rt.memcpy (Refresh the input and output memory.) - > acl.mdl.execute (Execute inference.) - > unlock(handle1)
    ```

- The operations of loading, executing, and unloading a model must be performed in the same context. For details about how to create a context, see `acl.rt.create_context`.
- You can call `acl.rt.malloc`, `acl.rt.malloc_host`, `acl.rt.malloc_cached`, `acl.media.dvpp_malloc`, or `acl.himpi.dvpp_malloc`, to allocate the memory for storing the model input and output data.

 Note that:

- For details about the usage scenarios and restrictions of the memory allocation APIs, see the related description.
- When the application calls `acl.rt.malloc_host` on the device to allocate memory, the device memory is allocated.
- `acl.media.dvpp_malloc` and `acl.himpi.dvpp_malloc` are dedicated memory allocation APIs for media data processing. To reduce copy, the output of media data processing is used as the input of model inference to implement memory overcommitment.
- The address space accessible by media data processing is limited. To ensure sufficient memory during media data processing, you are advised to call other APIs (such as `acl.rt.malloc`) to allocate memory for other functions (such as model loading).

## Sample Code

```python
data_buffer = acl.mdl.get_dataset_buffer(output, 0) # Obtain the corresponding data buffer based on the index.
data_addr = acl.get_data_buffer_addr(data_buffer) # Obtain the device pointer address of the data.
acl.rt.free(data_addr)                              # Release the device memory.
acl.update_data_buffer(data_buffer, 0, 0)           # Reset the data buffer for next inference.
```
