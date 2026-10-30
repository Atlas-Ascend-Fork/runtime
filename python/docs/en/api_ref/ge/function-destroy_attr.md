# Function: destroy\_attr

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

Destroys data of the `aclopAttr` type created by the [acl.op.create\_attr](function-create_attr.md) call.

## Prototype

- **C Prototype**

    ```c
    void aclopDestroyAttr(const aclopAttr *attr)
    ```

- **Python Function**

    ```python
    acl.op.destroy_attr(attr)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| attr | Int, pointer address of the `aclopAttr` type data to be destroyed. This object is created by calling [acl.op.create_attr](function-create_attr.md).|

## Return Values

None
