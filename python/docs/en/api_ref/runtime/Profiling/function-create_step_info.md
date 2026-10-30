# Function: create\_step\_info

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

Creates data of the `aclprofStepInfo` type as step information.

## Prototype

- **C Prototype**

    ```c
    aclprofStepInfo* aclprofCreateStepInfo(void)
    ```

- **Python Function**

    ```python
    info = acl.prof.create_step_info()
    ```

## Parameters

None

## Return Values

| Return Value| Description|
| --- | --- |
| info | Int, pointer address of the `aclprofStepInfo` type.<br>Success: `aclprofStepInfo` type<br>Failure: `None`|

## Constraints

- Use the acl.prof.destroy_step_info API to destroy data of the `aclprofStepInfo` type. If data is not destroyed, the memory cannot be freed.
- This API is used in pair with [acl.prof.destroy_step_info](function-destroy_step_info.md). Call `acl.prof.create_step_info` before `acl.prof.destroy_step_info`.
- The same tag can be configured only once for a single `aclprofStepInfo` object, to avoid profiling analysis errors.
