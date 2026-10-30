# Function: mark\_ex

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

acl.prof.mark\_ex dotting API.

This API is used to deliver dotting tasks to a configured stream to identify the relationship between the dotting task on the host and that on the device.

## Prototype

- **C Prototype**

    ```c
    aclError aclprofMarkEx(const char *msg, size_t msgLen, aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret = acl.prof.mark_ex(msg, stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| msg | Str, dotting information string.|
| stream | Int, stream.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
