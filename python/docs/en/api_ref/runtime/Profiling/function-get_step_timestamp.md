# Function: get\_step\_timestamp

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

Sets the start timestamp and end timestamp of an iteration when [single-operator loading and execution APIs](../Kernel/Kernel_loading_and_execution.md) are used for training, to display the profile data by iteration.

## Prototype

- **C Prototype**

    ```c
    aclError aclprofGetStepTimestamp(aclprofStepInfo* stepInfo, aclprofStepTag tag, aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret =acl.prof.get_step_timestamp(stepinfo, tag, stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| stepinfo | Int, step information. Call the [acl.prof.create_step_info](function-create_step_info.md) API to create data of the aclprofStepInfo type in advance.|
| tag | Int, step start timestamp and end timestamp. Pass the value `ACL_STEP_START` at the step start and the value `ACL_STEP_END` at the step end.|
| stream | Int, stream.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br>`0`: success<br>If [other values](../datatypes/aclError.md) are returned, the operation fails.|
