# Function: create\_desc

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

Creates data of the `aclmdlDesc` type as a model description.

To destroy data of the `aclmdlDesc` type, see [acl.mdl.destroy\_desc](function-destroy_desc.md).

## Prototype

- **C Prototype**

    ```c
    aclmdlDesc* aclmdlCreateDesc()
    ```

- **Python Function**

    ```python
    desc = acl.mdl.create_desc()
    ```

## Parameters

None

## Return Values

| Return Value| Description|
| --- | --- |
| desc | Int, address of an object of the `aclmdlDesc` type.|
