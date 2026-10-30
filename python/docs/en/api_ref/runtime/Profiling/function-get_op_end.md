# Function: get\_op\_end

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

Obtains the operator execution end time (ns).

As a best practice, the user can create a thread and call this API in the new thread. Otherwise, this API call will block the main thread.

## Prototype

- **C Prototype**

    ```c
    uint64_t aclprofGetOpEnd(const void *opInfo, size_t opInfoLen, uint32_t index)
    ```

- **Python Function**

    ```python
    op_end = acl.prof.get_op_end(op_info, op_info_len, index)
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
| op_end | Int, execution end time of the operator.|
