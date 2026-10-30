# Function: get\_op\_desc\_size

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

Obtains the size (in bytes) of the data structure of a single operator. In the current version, the size of each operator data structure is the same.

As a best practice, the user can create a thread and call this API in the new thread. Otherwise, this API call will block the main thread.

## Prototype

- **C Prototype**

    ```c
    aclError aclprofGetOpDescSize(size_t *opDescSize)
    ```

- **Python Function**

    ```python
    op_desc_size, ret = acl.prof.get_op_desc_size()
    ```

## Parameters

None

## Return Values

| Return Value| Description|
| --- | --- |
| op_desc_size | Int, size of the operator data structure.|
| ret | Int, error code.<br>`0`: success<br>If [other values](../datatypes/aclError.md) are returned, the operation fails.|
