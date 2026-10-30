# Function: get\_thread\_id\_from\_exception\_info

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

Obtains the thread ID associated with an exception. This API must be used in pair with [acl.rt.set\_exception\_info\_callback](function-set_exception_info_callback.md).

## Prototype

- **C Prototype**

    ```c
    uint32_t aclrtGetThreadIdFromExceptionInfo(const aclrtExceptionInfo *info)
    ```

- **Python Function**

    ```python
    thread_id = acl.rt.get_thread_id_from_exception_info(info)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| info | Int, pointer address of the exception information `aclrtExceptionInfo`.<br>If [acl.rt.set_exception_info_callback](function-set_exception_info_callback.md) is called before a task is executed, the system stores the abnormal task ID, stream ID, thread ID, and device ID in `aclExceptionInfo`.|

## Return Values

| Return Value| Description|
| --- | --- |
| thread_id | Int, thread ID in the exception information. `0xFFFFFFFF` (hexadecimal) indicates that the exception information is empty.|
