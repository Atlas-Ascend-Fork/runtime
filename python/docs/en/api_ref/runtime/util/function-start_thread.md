# Function: start\_thread

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

Creates a thread and executes the Python function in the thread.

## Prototype

```python
thr_id, ret = acl.util.start_thread(thr_func, args_list)
```

## Parameters

| Parameter| Description|
| --- | --- |
| thr_func | Python function object, indicating the user-defined Python function.<br>An example is as follows.<br>def thr_func(args_list):<br>pass |
| args_list | List, indicating the input parameters required by the user-defined Python function (`thr_func`).|

## Return Values

| Return Value| Description|
| --- | --- |
| thr_id | Int, thread ID.|
| ret | Int, error code.<br>`0`: success<br>If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

When a thread is created, the context cannot be automatically obtained. You need to call [acl.rt.set\_context](../context/function-set_context.md) to explicitly specify the context.
