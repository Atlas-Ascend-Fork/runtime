# Function: get\_op\_name\_v2

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

Obtains the name of a specified operator.

As a best practice, the user can create a thread and call this API in the new thread. Otherwise, this API call will block the main thread.

[acl.prof.get_op_name_v2](function-get_op_name_v2.md) and [acl.prof.get_op_name](function-get_op_name.md) provide the same function. However, [acl.prof.get_op_name_v2](function-get_op_name_v2.md) obtains the length of the operator name and allocates the corresponding space. You do not need to pass a parameter to specify the space required by the operator name. You are advised to use [acl.prof.get_op_name_v2](function-get_op_name_v2.md) first.

## Prototype

- **C Prototype**

    ```c
    aclError aclprofGetOpName(const void *opInfo, size_t opInfoLen, uint32_t index, char *opName, size_t opNameLen)
    ```

- **Python Function**

    ```python
    op_name, ret = acl.prof.get_op_name_v2(op_info, op_info_len, index)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| op_info | Int, specified memory address.|
| op_info_len | Int, length of the operator information.|
| index | Int, operator index.<br>The value range is [0, Operator count – 1]. Call [acl.prof.get_op_num](function-get_op_num.md) to obtain the operator count.|

## Return Values

| Return Value| Description|
| --- | --- |
| op_name | Str, operator name.|
| ret | Int, error code.<br>`0`: success<br>If [other values](../datatypes/aclError.md) are returned, the operation fails.|
