# Function: get\_res\_in\_current\_thread

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

Obtains the device resources that can be used by the current thread.

The value is returned based on the following priorities: stream-level device resource limits (set by calling [acl.rt.set_stream_res_limit](function-set_stream_res_limit.md)) \> device resource limits of the current process (set by calling [acl.rt.set_device_res_limit](function-set_device_res_limit.md)) \>AI default resource limits of the processor hardware.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtGetResInCurrentThread(aclrtDevResLimitType type, uint32_t *value)
    ```

- **Python Function**

    ```python
    value, ret = acl.rt.get_res_in_current_thread(type)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| type | Int, resource type. Currently, Cube Core and Vector Core are supported. For details, see [aclrtDevResLimitType](../datatypes/aclrtDevResLimitType.md).|

## Return Values

| Return Value| Description|
| --- | --- |
| value | Int, resource limit of the current thread.|
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
