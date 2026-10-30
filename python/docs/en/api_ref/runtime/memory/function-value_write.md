# Function: value\_write

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

Writes data to the specified memory.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtValueWrite(void* devAddr, uint64_t value, uint32_t flag, aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret = acl.rt.value_write(dev_addr, value, flag, stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| dev_addr | Int, device memory address.<br>You need to allocate device memory in advance (for example, by calling acl.rt.malloc). The value of `dev_addr` must be 8-byte aligned. The valid memory bit width is 64 bits.|
| value | Int, data to be written to the memory.|
| flag | Int, reserved; fixed at `0`.|
| stream | Int, stream. The value `0` indicates that the default stream is used.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
