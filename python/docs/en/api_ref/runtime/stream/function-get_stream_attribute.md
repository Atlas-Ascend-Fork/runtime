# Function: get\_stream\_attribute

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

Obtains attribute values of a stream.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtGetStreamAttribute(aclrtStream stream, aclrtStreamAttr stmAttrType, aclrtStreamAttrValue *value)
    ```

- **Python Function**

    ```python
    value, ret = acl.rt.get_stream_attribute(stream, stm_attr_type)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| stream | Int, stream.|
| stm_attr_type | Int, attribute type. For details, see [aclrtStreamAttr](../datatypes/aclrtStreamAttr.md).|

## Return Values

| Return Value| Description|
| --- | --- |
| value | Dict, attribute value. For details, see [aclrtStreamAttrValue](../datatypes/aclrtStreamAttrValue.md).|
| ret | Int. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

<!-- npu="950,A3,910b" id7 -->
- For Ascend 950PR&950DT, Atlas A3, and Atlas A2 products, the default stream can be specified (that is, the stream parameter is set to 0).
<!-- end id7 -->
<!-- npu="910,310p,310b" id8 -->
- For Atlas 200I/500 A2 inference products, Atlas inference products, and Atlas training products, the default stream cannot be specified (that is, the stream parameter cannot be set to 0).
<!-- end id8 -->
