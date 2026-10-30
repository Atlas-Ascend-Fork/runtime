# Function: dump\_unreg\_callback

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

Deregisters the dump data callback function.

The [function: init_dump](function-init_dump.md), [function: dump_reg_callback](function-dump_reg_callback.md) (the callback function registered through this API needs to be implemented by the user. The implementation logic of the callback function includes obtaining the dump data and data length), [function: dump_unreg_callback](function-dump_unreg_callback.md), and [function: finalize_dump](function-finalize_dump.md) APIs are used together to obtain dump data through the callback function. The following are some example scenarios:

- Execute a model and obtain dump data through callback.

    [Function: init](../init/function-init.md) API --\> [Function: dump_reg_callback](function-dump_reg_callback.md) API --\> [Function: init_dump](function-init_dump.md) API --\> Model loading --\> Model execution --\> [Function: finalize_dump](function-finalize_dump.md) API --\> [Function: dump_unreg_callback](function-dump_unreg_callback.md) API --\> Model unloading --\> [Function: finalize](../init/function-finalize.md) API

- Execute two different models and obtain dump data through callback. In this context, as long as the callback function is not deregistered by calling [Function: dump_unreg_callback](function-dump_unreg_callback.md), you can obtain the dump data of both models through the callback function.

    [Function: init](../init/function-init.md) API --\> [Function: dump_reg_callback](function-dump_reg_callback.md) API --\> [Function: init_dump](function-init_dump.md) API --\> Model 1 loading --\> Model 1 execution --\>--\> Model 2 loading --\> Model 2 execution --\> [Function: finalize_dump](function-finalize_dump.md) API --\> Model unloading --\> [Function: dump_unreg_callback](function-dump_unreg_callback.md) API --\> [Function: finalize](../init/function-finalize.md) API

## Prototype

- **C Prototype**

    ```c
    void acldumpUnregCallback()
    ```

- **Python Function**

    ```python
    acl.mdl.dump_unreg_callback()
    ```

## Parameters

None

## Return Values

None

## Constraints

acl.mdl.dump\_unreg\_callback must be used together with acl.mdl.dump\_reg\_callback and is valid only after acl.mdl.dump\_reg\_callback is called.
