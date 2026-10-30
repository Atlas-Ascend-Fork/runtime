# Function: set\_attr\_list\_data\_type

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

Sets the data type of a specified attribute list.

## Prototype

- **C Prototype**

    ```c
    aclError aclopSetAttrListDataType(aclopAttr *attr, const char *attrName, int numValues, const aclDataType values[])
    ```

- **Python Function**

    ```python
    attr, ret = acl.op.set_attr_list_data_type(attr, attr_name, values)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| attr | Int, pointer address of the data of the `aclopAttr` type. Call [acl.op.create_attr](function-create_attr.md) to create data of the `aclopAttr` type in advance.|
| attr_name | Str, attribute name.|
| values | List of attribute values.|

## Return Values

| Return Value| Description|
| --- | --- |
| attr | Int, pointer address of the `aclopAttr` type. Call [create_attr](function-create_attr.md) to create data of the aclopAttr type in advance.|
