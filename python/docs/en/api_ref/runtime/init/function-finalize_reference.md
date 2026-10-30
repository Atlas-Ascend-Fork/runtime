# Function: finalize\_reference

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

Performs deinitialization to destroy the resources used by the ACL API in the process.

acl.finalize_reference involves reference counting. Each time [acl.init](function-init.md) is called, the reference count is incremented by 1. Each time acl.finalize_reference is called, the reference count decreases by 1. Deinitialization is performed only when the reference count decreases to 0. The difference between [acl.finalize](function-finalize.md) and this API is that calling [acl.finalize](function-finalize.md) clears the count and directly performs deinitialization.

## Prototype

- **C Prototype**

    ```c
    aclError aclFinalizeReference(uint64_t *refCount)
    ```

- **Python Function**

    ```python
    count, ret = acl.finalize_reference()
    ```

## Parameters

None

## Return Values

| Return Value| Description|
| --- | --- |
| count | Int, reference count.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

Before exiting the application process, ensure that [acl.finalize](function-finalize.md) or acl.finalize_reference has been called to complete deinitialization. Otherwise, an exception may occur. For example, an error is reported when the application process exits.

You are advised not to call [acl.finalize](function-finalize.md) or acl.finalize_reference in the destructor. Otherwise, the process may exit abnormally due to the unknown singleton destruction sequence.
