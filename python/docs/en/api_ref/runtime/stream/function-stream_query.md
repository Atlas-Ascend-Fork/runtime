# Function: stream\_query

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

Queries the execution status of all tasks on a specified stream.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtStreamQuery(aclrtStream stream, aclrtStreamStatus *status)
    ```

- **Python Function**

    ```python
    status, ret = acl.rt.stream_query(stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| stream | Int, pointer address of the stream to be operated.|

## Return Values

| Return Value| Description|
| --- | --- |
| status | Task status on the stream. For details, see [aclrtStreamStatus](../datatypes/aclrtStreamStatus.md).|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

This API can be used to query the task execution status in the Ascend Virtual Instance (AVI) scenario.
