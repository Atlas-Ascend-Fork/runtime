# Function: stop\_dump\_args

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
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas inference products: Not supported
<!-- end id5 -->
<!-- npu="910" id6 -->
- Atlas training products: Supported
<!-- end id6 -->

## Function

Disables the operator information statistics function. This API must be used together with the [Function: start_dump_args](function-start_dump_args.md) API to output the operator information file to the directory specified by the path parameter. One shape corresponds to one operator information file. The file contains information such as the operator type, operator attributes, and operator input and output formats, data types, and shapes.

**Application scenario**: For example, to collect statistics on the operators involved in the execution of a model, call the acl.op.start_dump_args API before model execution and call the acl.op.stop_dump_args API after model execution. After the APIs are successfully called, an operator information file for each operator shape is generated in the directory specified by the path parameter.

## Prototype

- **C Prototype**

    ```c
    aclError aclopStopDumpArgs(uint32_t dumpType)
    ```

- **Python Function**

    ```python
    ret = acl.op.stop_dump_args(dump_type)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| dumpType | Int, type of dump information.<br>Currently, only `ACL_OP_DUMP_OP_AICORE_ARGS` is supported, indicating that statistics on all operators are collected.<br>0x00000001: ACL_OP_DUMP_OP_AICORE_ARGS|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

This API can be used only in the single-operator API execution scenario. Otherwise, dump files cannot be generated.
