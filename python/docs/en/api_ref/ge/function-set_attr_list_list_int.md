# Function: set\_attr\_list\_list\_int

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

Sets the values (lists of `int64_t` lists) of an attribute.

## Prototype

- **C Prototype**

    ```c
    aclError aclopSetAttrListListInt(aclopAttr *attr, const char *attrName, int numLists, const int *numValues, const int64_t *const values[])
    ```

- **Python Function**

    ```python
    ret = acl.op.set_attr_list_list_int(attr, attr_name, values)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| attr | Int, pointer address of the data of the `aclopAttr` type. Call [acl.op.create_attr](function-create_attr.md) to create data of the `aclopAttr` type in advance.|
| attr_name | Str, attribute name.|
| values | List, which consists of multiple lists (each element in the lists is int type) or a one-dimensional array NumPy object (int64 type).|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|

## Constraints

- You are advised to use the list data type for `attr_value` because NumPy will not be supported as the input in future releases.
- To use NumPy for `attr_value`, ensure that the operating environment is Python 3.8 or later and NumPy 1.22.0 or later.
