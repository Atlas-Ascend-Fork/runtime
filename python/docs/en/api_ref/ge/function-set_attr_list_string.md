# Function: set\_attr\_list\_string

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

Sets the values (a list of strings) of an attribute.

## Prototype

- **C Prototype**

    ```c
    aclError aclopSetAttrListString(aclopAttr *attr, const char *attrName, int numValues, const char **attrValue)
    ```

- **Python Function**

    ```python
    ret = acl.op.set_attr_list_string(attr, attr_name, attr_value)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| attr | Int, pointer address of the data of the `aclopAttr` type. Call [acl.op.create_attr](function-create_attr.md) to create data of the `aclopAttr` type in advance.|
| attr_name | Str, attribute name.|
| attr_value | Two data types are supported:<br> List, which consists of elements of the float type.<br> NumPy object, one-dimensional array. The type is float32.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|
