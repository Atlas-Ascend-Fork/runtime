# Function: allocator\_register

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
- Atlas inference products: Supported
<!-- end id5 -->
<!-- npu="910" id6 -->
- Atlas training products: Supported
<!-- end id6 -->

## Function

Registers the user-provided Allocator and its callback function, so that the Allocator can be used.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtAllocatorRegister(aclrtStream stream, aclrtAllocatorDesc allocatorDesc)
    ```

- **Python Function**

    ```python
    ret = acl.rt.allocator_register(stream, allocatorDesc)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| stream | Int, stream to be registered by the Allocator. The value cannot be `NULL`. Otherwise, an error is reported.|
| allocatorDesc | Int, pointer address of the allocator descriptor.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- Currently, this API can be used only in single-operator model execution and dynamic shape model inference scenarios.

    In single-operator model use cases, call this API before executing an API (such as `acl.op.execute_v2`).

    In the dynamic-shape model inference scenario, call this API together with `aclmdlExecuteAsync`, and this API must be called before `aclmdlExecuteAsync`.

- Before calling this API, call [acl.rt.allocator\_create\_desc](../datatypes/function-allocator_create_desc.md) to create an Allocator descriptor, and then call [acl.rt.allocator\_set\_obj\_to\_desc](../datatypes/function-allocator_set_obj_to_desc.md), [acl.rt.allocator\_set\_alloc\_func\_to\_desc](../datatypes/function-allocator_set_alloc_func_to_desc.md), [acl.rt.allocator\_set\_get\_addr\_from\_block\_func\_to\_desc](../datatypes/function-allocator_set_get_addr_from_block_func_to_desc.md) and [acl.rt.allocator\_set\_free\_func\_to\_desc](../datatypes/function-allocator_set_free_func_to_desc.md) to set the Allocator object and callback function, respectively. After the Allocator descriptor is no longer needed, call [acl.rt.allocator_destroy_desc](../datatypes/function-allocator_destroy_desc.md) to destroy the Allocator descriptor.
- If you call this API multiple times for the same stream, the last registration applies.
- If you call this API for different streams using the same Allocator, concurrent execution of these streams is not allowed. Before you execute the next stream, synchronize the previous one.
- Before freeing the memory in the Allocator to the OS, call [acl.rt.synchronize\_stream](../stream/function-synchronize_stream.md) to synchronize the stream and ensure that all tasks in the stream have been completed.
