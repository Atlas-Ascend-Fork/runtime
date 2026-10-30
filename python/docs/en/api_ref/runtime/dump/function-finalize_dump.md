# Function: finalize\_dump

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

Deinitializes dump.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlFinalizeDump()
    ```

- **Python Function**

    ```python
    ret = acl.mdl.finalize_dump()
    ```

## Parameters

None

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- [acl.mdl.init_dump](function-init_dump.md) must be used in pair with [acl.mdl.set_dump](function-set_dump.md) and [acl.mdl.finalize_dump](function-finalize_dump.md) to dump data to files. These APIs can be called for multiple times in a single process to obtain dump data of different Dump configurations.
- Example scenario:
  - To execute the model twice, you need to set different dump configurations. The API call sequence is as follows: [acl.init](../init/function-init.md) --\> acl.mdl.init\_dump --\> [acl.mdl.set\_dump](function-set_dump.md) --\> Model Loading --\> Model Execution --\> [acl.mdl.finalize\_dump](function-finalize_dump.md) --\> Model Unloading --\> [acl.mdl.init\_dump](function-init_dump.md) --\> [acl.mdl.set\_dump](function-set_dump.md) --\> Model Loading --\> Model Execution --\> [acl.mdl.finalize\_dump](function-finalize_dump.md) --\> Model Unloading --\> Other tasks --\> [acl.finalize](../init/function-finalize.md)
  - If a model is executed twice, dump is required for the first execution and not required for the second execution. The API call sequence is as follows: [acl.init](../init/function-init.md) --\> acl.mdl.init\_dump --\> [acl.mdl.set\_dump](function-set_dump.md) --\> Model Loading --\> Model Execution --\> [acl.mdl.finalize\_dump](function-finalize_dump.md) --\> Model Unloading --\> Model Loading --\> Model Execution --\> Other tasks --\> [acl.finalize](../init/function-finalize.md)

## Reference

[acl.init](../init/function-init.md) is also available. During initialization, the dump configuration is passed through a JSON file to dump the data at runtime. In this mode, [acl.init](../init/function-init.md) can be called only once in a process. You can modify the dump configuration in the JSON file.
