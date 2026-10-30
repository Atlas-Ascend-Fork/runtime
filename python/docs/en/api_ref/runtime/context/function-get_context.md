# Function: get\_context

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

Obtains the context of a thread.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtGetCurrentContext(aclrtContext context)
    ```

- **Python Function**

    ```python
    context, ret = acl.rt.get_context()
    ```

## Parameters

None

## Return Values

| Return Value| Description|
| --- | --- |
| context | Int, pointer address of the created context object.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

If you call [acl.rt.set\_context](../context/function-set_context.md) multiple times to set the context of the current thread, the context set last time is obtained.
