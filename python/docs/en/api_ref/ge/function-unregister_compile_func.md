# Function: unregister\_compile\_func

## Applicable Products

<!-- npu="950" id1 -->
- Ascend 950PR&950DT products: Not supported
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

Deregisters the operator selector in dynamic shape scenarios.

## Prototype

- **C Prototype**

    ```c
    aclError aclopUnregisterCompileFunc(const char *opType)
    ```

- **Python Function**

    ```python
    ret = acl.op.unregister_compile_func(op_type)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| op_type | Str, operator type.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|
