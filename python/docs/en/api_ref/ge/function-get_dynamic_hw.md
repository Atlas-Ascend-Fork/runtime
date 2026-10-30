# Function: get\_dynamic\_hw

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

Obtains the dynamic image size information supported by a model based on the model description.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlGetDynamicHW(const aclmdlDesc *modelDesc, size_t index, aclmdlHW *hw)
    ```

- **Python Function**

    ```python
    hw_info, ret = acl.mdl.get_dynamic_hw(model_desc, index)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_desc | Int, pointer address of the data of the `aclmdlDesc` type. Call the [acl.mdl.create_desc](function-create_desc.md) API to create data of the aclmdlDesc type in advance.|
| index | Int, reserved. The value is fixed to<br> `1`.|

## Return Values

| Return Value| Description|
| --- | --- |
| hw_info | Dict, width and height (image size) supported by the obtained model.<br> The maximum number of HW is 128. hw_info = { "hwCount": int, # Number of width and height profiles supported by the model. "hw": [xx, xx,] # Specific profiles supported by the model. In each profile group, the array subscript 0 indicates the height, and the array subscript 1 indicates the width.} - If hwCount is 0, the profile information cannot be set and the profile in the model is used.|
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|
