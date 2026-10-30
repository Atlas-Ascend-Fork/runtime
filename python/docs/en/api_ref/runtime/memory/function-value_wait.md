# Function: value\_wait

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
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas inference products: Not supported
<!-- end id5 -->
<!-- npu="910" id6 -->
- Atlas training products: Not supported
<!-- end id6 -->

## Function

Unblocks the data in the specified memory when the data meets certain conditions.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtValueWait(void* devAddr, uint64_t value, uint32_t flag, aclrtStream stream) 
    ```

- **Python Function**

    ```python
    ret = acl.rt.value_wait(devAddr, value, flag, stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| devAddr | Int, device memory address.<br>The valid memory bit width of `dev_addr` is 64 bits.|
| value | Int, value to be compared with the data in the memory.|
| flag | Int, comparison mode. The data will be unblocked after the conditions are met.<br>The options are as follows:<br>0x0: ACL_STREAM_WAIT_VALUE_GEQ<br>0x1: ACL_STREAM_WAIT_VALUE_EQ<br>0x2: ACL_STREAM_WAIT_VALUE_AND<br>0x3: ACL_STREAM_WAIT_VALUE_NOR|
| stream | Int, stream. The value `0` indicates that the default stream is used.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
