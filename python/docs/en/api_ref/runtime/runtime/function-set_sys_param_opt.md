# Function: set\_sys\_param\_opt

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

Sets the value of a runtime parameter in the current process. After calling this API to set runtime parameters, call [acl.rt.get_sys_param_opt](function-get_sys_param_opt.md) to obtain the parameter values.

The difference between this API and [acl.rt.ctx\_set\_sys\_param\_opt](../context/function-ctx_set_sys_param_opt.md) is that this API functions as a process while **acl.rt.ctx\_set\_sys\_param\_opt** functions as a context.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtSetSysParamOpt(aclrtSysParamOpt opt, int64_t value)
    ```

- **Python Function**

    ```python
    ret = acl.rt.set_sys_param_opt(opt, value)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| opt | int, runtime system parameter. For details, see [aclSysParamOpt](../datatypes/aclSysParamOpt.md).|
| value | Int, runtime parameter value.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

If this API is called for multiple times, the last setting is used.
