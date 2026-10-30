# Function: set\_stream\_attribute

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

Sets attributes of a stream.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtSetStreamAttribute(aclrtStream stream, aclrtStreamAttr stmAttrType, aclrtStreamAttrValue *value)
    ```

- **Python Function**

    ```python
    ret = acl.rt.set_stream_attribute(stream, stm_attr_type, value)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| stream | Int, stream.|
| stm_attr_type | Int, attribute type. For details, see [aclrtStreamAttr](../datatypes/aclrtStreamAttr.md).|
| value | Dict, attribute value. For details, see [aclrtStreamAttrValue](../datatypes/aclrtStreamAttrValue.md).|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|

## Constraints

- Overflow detection attribute: The setting takes effect only for tasks created after this API call.
- For Ascend 950PR&950DT, Atlas A3, and Atlas A2 products, the default stream can be specified (that is, the stream parameter is set to 0).
- For Atlas 200I/500 A2 inference products, Atlas inference products, and Atlas training products, the default stream cannot be specified (that is, the stream parameter cannot be set to 0).
- Failure mode: The failure mode cannot be set for the default stream of a context.
<!-- npu="A3,910b,910,310p,310b" id7 -->
- When `stm_attr_type` is set to `ACL_STREAM_ATTR_FAILURE_MODE`, the following product models are supported:
  <!-- npu="310p" id8 -->
  - Atlas inference products
  <!-- end id8 -->
  <!-- npu="310b" id9 -->
  - Atlas 200I/500 A2 inference products
  <!-- end id9 -->
  <!-- npu="910" id10 -->
  - Atlas training products
  <!-- end id10 -->
  <!-- npu="910b" id11 -->
  - Atlas A2 products
  <!-- end id11 -->
  <!-- npu="A3" id12 -->
  - Atlas A3 products
  <!-- end id12 -->
<!-- end id7 -->

<!-- npu="A3,910b" id13 -->
- When `stm_attr_type` is set to `ACL_STREAM_ATTR_FLOAT_OVERFLOW_CHECK` or `ACL_STREAM_ATTR_USER_CUSTOM_TAG`, the following product models are supported:
  <!-- npu="910b" id14 -->
  - Atlas A2 products
  <!-- end id14 -->
  <!-- npu="A3" id15 -->
  - Atlas A3 products
  <!-- end id15 -->
<!-- end id13 -->
