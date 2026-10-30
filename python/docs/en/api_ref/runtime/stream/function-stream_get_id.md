# Function: stream\_get\_id

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

Obtains the ID of a specified stream.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtStreamGetId(aclrtStream stream, int32_t *streamId)
    ```

- **Python Function**

    ```python
    stream_id, ret = acl.rt.stream_get_id(stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| stream | Int, pointer address of the stream to be queried. If the value is 0, the default stream is used.|

## Return Values

| Return Value| Description|
| --- | --- |
| stream_id | Int, stream ID.|
| ret | Int. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
