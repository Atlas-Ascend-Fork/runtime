# Function: get\_cann\_attribute

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

Queries whether the operating environment supports the specified CANN feature.

## Prototype

- **C Prototype**

    ```c
    aclError aclGetCannAttribute(aclCannAttr cannAttr, int32_t *value)
    ```

- **Python Function**

    ```python
    value, ret = acl.get_cann_attribute(cann_attr)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| cann_attr | Int, enumerated value of the feature list. You can specify one item for a query. For details, see [aclCannAttr](../datatypes/aclCannAttr.md).|

## Return Values

| Return Value| Description|
| --- | --- |
| value | Int, whether the function is supported.<br>`1`: yes<br>`0`: no|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
