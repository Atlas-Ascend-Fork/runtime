# Function: get\_recent\_err\_msg

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

Obtains and clears the error messages returned by other failed pyacl API calls in the calling thread.

The err_msg_mode configuration item in the [acl.init](../init/function-init.md) API determines whether to obtain the process- or thread-level error description. The thread-level error description is obtained by default.

## Prototype

- **C Prototype**

    ```c
    const char *aclGetRecentErrMsg()
    ```

- **Python Function**

    ```python
    msg = acl.get_recent_err_msg()
    ```

## Parameters

None

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- You are advised to call the acl.get\_recent\_err\_msg API each time the pyacl API fails to be called to obtain the error description for fault locating.
- If the acl.get\_recent\_err\_msg API is called multiple times in the same thread, only the error description string returned by the last call is valid. The error description strings returned by the previous calls cannot be used. Otherwise, illegal memory access may occur.
- If the acl.get\_recent\_err\_msg API is not called each time the pyacl API fails to be called, error information may be accumulated or lost.
