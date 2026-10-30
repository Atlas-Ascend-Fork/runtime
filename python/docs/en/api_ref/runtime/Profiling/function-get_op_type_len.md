# Function: get\_op\_type\_len

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

Obtains the string length of the operator type for memory allocation.

As a best practice, the user can create a thread and call this API in the new thread. Otherwise, this API call will block the main thread.

## Prototype

- **C Prototype**

    ```c
    aclError aclprofGetOpTypeLen(const void *opInfo, size_t opInfoLen, uint32_t index, size_t *opTypeLen)
    ```

- **Python Function**

    ```python
    opTypeLen, ret = acl.prof.get_op_type_len(opInfo, opInfoLen, index)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| opInfo | Int, address of the operator information.|
| opInfoLen | Int, length of the operator information.|
| index | Int, operator index.<br>The value range is [0, Operator count – 1]. Call [acl.prof.get_op_num](function-get_op_num.md) to obtain the operator count.|

## Return Values

| Return Value| Description|
| --- | --- |
| opTypeLen | Int, length of operator type.|
| ret | Int, error code.<br>`0`: success<br>If [other values](../datatypes/aclError.md) are returned, the operation fails.|
