# Function: get\_cann\_attribute\_list

## Applicable Products

<!-- npu="950" id1 -->
- Ascend 950PR&950DT products: Supported
<!-- end id1 -->
<!-- npu="A3" id2 -->
- Atlas A3 products: supported
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

Queries the list of features supported by the CANN software and the corresponding chip in the operating environment.

## Prototype

- **C Prototype**

    ```c
    aclError aclGetCannAttributeList(const aclCannAttr **cannAttrList, size_t *num)
    ```

- **Python Function**

    ```python
    cann_attr_list, num, ret = acl.get_cann_attribute_list()
    ```

## Parameters

None

## Return Values

| Return Value| Description|
| --- | --- |
| cann_attr_list | List, used to save the features supported by the operating environment. For details, see [aclCannAttr](../datatypes/aclCannAttr.md).<br>Users do not need to allocate memory in advance. When an app process exits, the memory is automatically freed.|
| num | Int, the number of supported features. The value must be the same as the length of the `cann_attr_list` list.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
