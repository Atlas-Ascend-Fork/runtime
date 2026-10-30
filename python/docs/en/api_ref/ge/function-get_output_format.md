# Function: get\_output\_format

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

Obtains the format of an output based on the model description.

## Prototype

- **C Prototype**

    ```c
    aclFormat aclmdlGetOutputFormat(const aclmdlDesc *modelDesc, size_t index)
    ```

- **Python Function**

    ```python
    format_info = acl.mdl.get_output_format(model_desc, index)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_desc | Int, pointer address of the data of the `aclmdlDesc` type. Call the [acl.mdl.create_desc](function-create_desc.md) API to create data of the aclmdlDesc type in advance.|
| index | Int, sequence number of the input to obtain, indexed starting at 0.|

## Return Values

| Return Value| Description|
| --- | --- |
| format_info | Int, format of the specified output. For details, see [aclFormat](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/API/runtimeapi/aclpythondevg_01_0914.html).|
