# Function: set\_ts\_device

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

Sets the task schedule required for the computation.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtSetTsDevice(aclrtTsId tsId)
    ```

- **Python Function**

    ```python
    ret = acl.rt.set_ts_device(ts_id)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| ts_Id | Int, task schedule required for the computation. If the Ascend AI software stack contains only the AICORE Task Schedule, this parameter is invalid and the AICORE Task Schedule is used by default.<br>`0`: ACL_TS_ID_AICORE. Use the AICORE task schedule.<br>`1`: ACL_TS_ID_AIVECTOR. Use the AIVECTOR Task Schedule.<br>`2`: ACL_TS_ID_RESERVED.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
