# Function: get\_input\_size\_by\_index

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

Obtains the input size in bytes based on data of the `aclmdlDesc` type.

## Prototype

- **C Prototype**

    ```c
    size_t aclmdlGetInputSizeByIndex(aclmdlDesc *modelDesc, size_t index)
    ```

- **Python Function**

    ```python
    size = acl.mdl.get_input_size_by_index(model_desc, index)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_desc | Int, pointer address of the data of the `aclmdlDesc` type. Call the [acl.mdl.create_desc](function-create_desc.md) API to create data of the aclmdlDesc type in advance.|
| index | Int, sequence number of the input to be obtained, starting from 0.|

## Return Values

| Return Value| Description|
| --- | --- |
| size | Int, size of the input, in bytes<br> If dynamic batch/image size (width and height) is enabled, the input size of the maximum profile is returned.<br> In other (static) cases, the size of the specified input is returned. The unit is byte.|

## Constraints

If the shape input by the model is dynamic and the value of the dimension is `–1` (indicating that any value greater than or equal to 1 can be used for the dimension), the size obtained from this call is `0`. You need to allocate the memory based on the size of the memory occupied.
