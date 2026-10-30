# Function: ctx\_get\_sys\_param\_opt

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

Obtains system parameter values in the current context.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtCtxGetSysParamOpt(aclSysParamOpt opt, int64_t *value)
    ```

- **Python Function**

    ```python
    value, ret = acl.rt.ctx_get_sys_param_opt(opt)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| opt | Int, system parameter. For details, see [aclSysParamOpt](../datatypes/aclSysParamOpt.md).|
| value | Int, system parameter value.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

System parameters do not have default values. If you call this API to obtain system parameter values without calling [acl.rt.ctx_set_sys_param_opt](function-ctx_set_sys_param_opt.md) to set system parameter values, a failure message will be returned.
