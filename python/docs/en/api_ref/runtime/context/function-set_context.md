# Function: set\_context

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

Sets the context of a thread.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtSetCurrentContext(aclrtContext context)
    ```

- **Python Function**

    ```python
    ret = acl.rt.set_context(context)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| context | Int, pointer address of the current context object in the thread.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- The following scenarios are supported:
  - If you explicitly create a context (for example, ctx1) by calling [acl.rt.create\_context](function-create_context.md) in a thread (for example, thread1), you do not need to call acl.rt.set\_context to specify the context bound to the calling thread. ctx1 is bound to thread1 by default.
  - If [acl.rt.create\_context](function-create_context.md) is not called to explicitly create a context, the default context is bound to the calling thread. In this case, the default context cannot be destroyed by calling [acl.rt.destroy\_context](function-destroy_context.md).
  - If acl.rt.set\_context is called for multiple times to set the context of the thread, the last setting applies.

- If the device of the context to be bound to a thread has been reset, the context cannot be bound to the thread. Otherwise, exceptions may occur.
- It is recommended that a context created in a thread be used in that thread. If thread A calls [acl.rt.create\_context](function-create_context.md) to create a context and thread B uses this context, you need to ensure the tasks execution sequence of the two threads that are in the same stream of the same context.
