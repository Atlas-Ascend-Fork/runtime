# Function: get\_desc\_from\_mem

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

Obtains model description from memory.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlGetDescFromMem(aclmdlDesc *modelDesc, const void *model, size_t modelSize)
    ```

- **Python Function**

    ```python
    ret = acl.mdl.get_desc_from_mem(model_desc, model, model_size)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model | Int, pointer address of the memory for storing model data.|
| model_size | Int, size of the model data in the memory, in bytes.|
| model_desc | Int, pointer to data of the `aclmdlDesc` type. You need to call the [create_desc](function-create_desc.md) API to create data of the `aclmdlDesc` type in advance. After the call is successful, the content in the pointer address is updated.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, `0` on success; else, failure.|

## Constraints

The model description obtained using this API cannot be used for the [get\_op\_attr](function-get_op_attr.md) and [get\_cur\_output\_dims](function-get_cur_output_dims.md) APIs.

<!-- npu="950,A3,910b,910,310p,310b" id7 -->
In Ascend EP form, allocate memory on the host for the model parameter.
<!-- end id7 -->

<!-- npu="310b" id8 -->
In Ascend RC form, allocate memory on the device for the model parameter.
<!-- end id8 -->

<!-- npu="310p" id9 -->
In Ctrl CPU form, allocate memory on the device for the model parameter.
<!-- end id9 -->
