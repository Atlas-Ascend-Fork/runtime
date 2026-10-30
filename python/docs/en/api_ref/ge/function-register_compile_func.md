# Function: register\_compile\_func

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

Registers an operator selector for a dynamic-shape operator. The selection of the tiling policy depends on the operator's input shape.

An operator can register with only one operator selector. To change the operator selector, call `acl.op.unregister_compile_func` to unregister and then call `acl.op.register_compile_func` to register again.

## Prototype

- **C Prototype**

    ```c
    aclError aclopRegisterCompileFunc(const char *opType, aclopCompileFunc func)
    ```

- **Python Function**

    ```python
    ret = acl.op.register_compile_func(op_type, func)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| op_type | Str, operator type.|
| func | Python function object, callback function of the operator selector.<br>Function definition: def call_back_func(num_inputs, input_desc, num_outputs, output_desc, op_attr, aclop_kernel_desc): pass|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|

## Reference

For details about the API calling process and examples, see [Single-Operator Calling](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/others/acldevg/aclpythondevg_0067.html).
