# Function: finalize

## Applicable Products

<!-- npu="950" id1 -->
- Ascend 950PR&950DT products: Supported
<!-- end id1 -->
<!-- npu="A3" id2 -->
- Atlas A3 products: supported
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

Performs deinitialization to destroy allocations.

By default, a 2000 ms delay (the actual maximum delay can reach 2000 ms) is added to this API call to return device service logs, ensuring that no ERROR- or EVENT-level logs are lost. You can set the `ASCEND\_LOG\_DEVICE\_FLUSH\_TIMEOUT` environment variable to 0 (example command: `export ASCEND\_LOG\_DEVICE\_FLUSH\_TIMEOUT=0`) to remove the default delay.

For details about the `ASCEND\_LOG\_DEVICE\_FLUSH\_TIMEOUT` environment variable, see "Logs \> ASCEND\_LOG\_DEVICE\_FLUSH\_TIMEOUT" in [Environment Variables](https://hiascend.com/en/document/redirect/CannCommunityEnvRef).

## Prototype

- **C Prototype**

    ```c
    aclError aclFinalize()
    ```

- **Python Function**

    ```python
    ret = acl.finalize()
    ```

## Parameters

None

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

Before the application process exits, explicitly call this API or [acl.finalize\_reference](function-finalize_reference.md) to deinitialize the application. Otherwise, an exception may occur. For example, an error is reported when the application process exits.

You are advised not to call acl.finalize or [acl.finalize\_reference](function-finalize_reference.md) in the destructor. Otherwise, the process may exit abnormally due to the unknown singleton destruction sequence.

## Reference

For details about API call examples, see "Initialization and Deinitialization" in "Application Development (Python)".
