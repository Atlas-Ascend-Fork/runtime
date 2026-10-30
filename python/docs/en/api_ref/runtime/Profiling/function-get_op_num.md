# Function: get\_op\_num

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

Obtains the number of operators in the specified memory space.

As a best practice, the user can create a thread and call this API in the new thread. Otherwise, this API call will block the main thread.

## Prototype

- **C Prototype**

    ```c
    aclError aclprofGetOpNum(const void *opInfo, size_t opInfoLen, uint32_t *opNumber)
    ```

- **Python Function**

    ```python
    op_num, ret = acl.prof.get_op_num(op_info, op_info_len)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| op_info | Int, specified memory address.<br>After the size of the single-operator data structure is obtained by calling [acl.prof.get_op_desc_size](function-get_op_desc_size.md), you must allocate memory based on the value obtained by multiplying the size of the single-operator data structure by the integer coefficient. The memory is used to store operator data collected by profiling and is used as the input of this API.|
| op_info_len | Int, length of the operator information.|

## Return Values

| Return Value| Description|
| --- | --- |
| op_num | Int, number of operators.|
| ret | Int, error code.<br>`0`: success<br>Other values: failure|
