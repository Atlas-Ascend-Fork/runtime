# Function: destroy\_event

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

Destroys an event. This API can be called to destroy an event before the event is complete. In this case, this API does not block the thread until the event is complete. Event-related resources are automatically released when the event is complete.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtDestroyEvent(aclrtEvent event)
    ```

- **Python Function**

    ```python
    ret = acl.rt.destroy_event(event)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| event | Int, pointer address of the event to be destroyed.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

When calling acl.rt.destroy\_event to destroy a specified event, ensure that the event is not being used by other APIs.
