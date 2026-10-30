# Function: get\_thread\_last\_task\_id

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

Obtains the ID of the last task delivered by the current thread.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtGetThreadLastTaskId(uint32_t *taskId)
    ```

- **Python Function**

    ```python
    task_id, ret = acl.rt.get_thread_last_task_id()
    ```

## Parameters

None

## Return Values

| Return Value| Description|
| --- | --- |
| taskId | Unsigned int, task ID. ID of the last task delivered by the current thread. The task here indicates the one delivered by the stream explicitly created by the user.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
