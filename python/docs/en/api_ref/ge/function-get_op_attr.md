# Function: get\_op\_attr

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

Obtains the attribute value of an operator in a model on the network.

## Prototype

- **C Prototype**

    ```c
    const char *aclmdlGetOpAttr(aclmdlDesc *modelDesc, const char *opName, const char *attr)
    ```

- **Python Function**

    ```python
    attr_value = acl.mdl.get_op_attr(model_desc, op_name, attr)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_desc | Int, pointer address of the `aclmdlDesc` type. Call [acl.mdl.create_desc](function-create_desc.md) to create data of the `aclmdlDesc` type in advance, and then call [acl.mdl.get_desc](function-get_desc.md) to obtain the data of the `aclmdlDesc` type based on the model ID.|
| op_name | Str, operator name.|
| attr | Str, operator attribute. Currently, only the `_datadump_original_op_names` attribute is supported, which records the base operators before fusion. The API return is formatted as `[opName1_len]opName1...[opNameN_len]opNameN, where opNameN_len` indicates the length of the operator name string. In the following example of the `_datadump_original_op_names` attribute, the base operators are scale2c_branch2c, bn2c_branch2c, res2c_branch2c, res2c, and res2c_relu and the lengths of the operator name strings are 16, 13, 14, 5, and 10: `[16]scale2c_branch2c[13]bn2c_branch2c[14]res2c_branch2c[5]res2c[10]res2c_relu`|

## Return Values

| Return Value| Description|
| --- | --- |
| attr_value | Str, attribute value. If the `opName` or `attr` attribute does not exist, or the `attr` attribute value is empty, an empty string is returned. If this API call fails, `None` is returned.|
