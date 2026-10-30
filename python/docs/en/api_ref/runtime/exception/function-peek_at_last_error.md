# Function: peek\_at\_last\_error

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

Obtains (but does not clear) the Runtime error code of the current thread.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtPeekAtLastError(aclrtLastErrLevel level)
    ```

- **Python Function**

    ```python
    ret = acl.rt.peek_at_last_error(level)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| level | Int, level of the error code to be obtained. Currently, only the thread level is supported. See [aclrtLastErrLevel](../datatypes/aclrtLastErrLevel.md).|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
