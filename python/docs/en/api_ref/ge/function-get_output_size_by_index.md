# Function: get\_output\_size\_by\_index

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

Obtains the output size in bytes based on data of the aclmdlDesc type.

## Prototype

- **C Prototype**

    ```c
    size_t aclmdlGetOutputSizeByIndex(aclmdlDesc *modelDesc, size_t index)
    ```

- **Python Function**

    ```python
    size = acl.mdl.get_output_size_by_index(model_desc, index)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_desc | Int, pointer address of the data of the `aclmdlDesc` type. Call the [acl.mdl.create_desc](function-create_desc.md) API to create data of the aclmdlDesc type in advance.|
| index | Int, sequence number of the output to obtain, indexed starting at 0|

## Return Values

| Return Value| Description|
| --- | --- |
| size | Int, size of the output, in bytes<br> If dynamic batch/image size (width and height) is enabled, the input size of the maximum profile is returned.<br> In other (static) cases, the size of the specified output is returned. The unit is byte.|

## Constraints

If the size obtained from this call is `0`, the possible cause is that the range of the output shape is unknown. Currently, the following two processing methods are available:

- **The system internally allocates output buffer of the corresponding index** to save the memory. However, after the buffer data is used, free it in a timely manner. In addition, memory copy is involved in allocation, which may cause performance loss.

 When calling `acl.create_data_buffer` to create the `aclDataBuffer` type for storing output data of the corresponding index, you can pass `0` to the `data` parameter to create an empty `aclDataBuffer` type. During model execution, the system automatically calculates and allocates the index output buffer.

- **Estimate the size of the output buffer and allocate it.** You can manage it by yourself. However, the buffer size may be insufficient or exceed the threshold. If the buffer size is insufficient, the system reports an error. If it exceeds the threshold, a waste is caused.

 You need to estimate a large output buffer as needed. During model execution, the system checks whether the specified output buffer size meets the requirement. If no, an error message is returned, with the size of the desired output buffer displayed. You can use either of the following methods to view the error message:

 - Obtain app logs and view errors at the ERROR level. For details about how to obtain logs, see *Log Reference*.
 - Call [Function: get\_recent\_err\_msg](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/API/runtimeapi/aclpythondevg_01_0010.html) API in the application to obtain the error message.
