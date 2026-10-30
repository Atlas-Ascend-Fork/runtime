# Function: create\_attr

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

Creates data of the `aclopAttr` type to store operator attributes.

To destroy data of the `aclopAttr` type, see [acl.op.destroy\_attr](function-destroy_attr.md).

## Prototype

- **C Prototype**

    ```c
    aclopAttr *aclopCreateAttr()
    ```

- **Python Function**

    ```python
    attr = acl.op.create_attr()
    ```

## Parameters

None

## Return Values

| Return Value| Description|
| --- | --- |
| attr | Int, pointer address of `aclopAttr` type data.|
