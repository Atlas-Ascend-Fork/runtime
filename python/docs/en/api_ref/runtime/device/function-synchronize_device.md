# Function: synchronize\_device

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

Blocks app execution until the compute device has completed all preceding requested tasks.

If there are multiple devices, this API is called to wait for the device corresponding to the current context.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtSynchronizeDevice(void)
    ```

- **Python Function**

    ```python
    ret = acl.rt.synchronize_device()
    ```

## Parameters

None

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
