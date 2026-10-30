# Function: get\_sys\_param\_opt

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

Obtains the value of a runtime parameter of the current process.

If you do not call [acl.rt.set\_sys\_param\_opt](function-set_sys_param_opt.md) to set the runtime parameter values, you can directly call this API to obtain the default value 0 of each parameter, indicating that deterministic computation or out-of-bounds memory access detection is disabled. After calling [acl.rt.set\_sys\_param\_opt](function-set_sys_param_opt.md) to set the runtime parameter values, call [acl.rt.get\_sys\_param\_opt](function-get_sys_param_opt.md) to obtain the parameter values.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtGetSysParamOpt(aclrtSysParamOpt opt, int64_t *value)
    ```

- **Python Function**

    ```python
    value, ret = acl.rt.get_sys_param_opt(opt)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| opt | Int, runtime system parameter. For details, see [aclSysParamOpt](../datatypes/aclSysParamOpt.md).|

## Return Values

| Return Value| Description|
| --- | --- |
| value | Int, runtime parameter value.|
| ret | Int. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
