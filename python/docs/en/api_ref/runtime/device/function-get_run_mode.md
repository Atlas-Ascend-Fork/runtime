# Function: get\_run\_mode

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

Obtains the current run mode of Ascend AI Software Stack.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtGetRunMode(aclrtRunMode *runMode)
    ```

- **Python Function**

    ```python
    run_mode, ret = acl.rt.get_run_mode()
    ```

## Parameters

None.

## Return Values

| Return Value| Description|
| --- | --- |
| run_mode | Int, running mode. For details about the type definition, see [aclrtRunMode](../datatypes/aclrtRunMode.md).|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Reference

For details about the API call process and example, see "Runtime Resource Allocation and Deallocation" in "Application Development (Python)".
