# Function: ptr\_to\_bytes

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

Converts `void*` data into a bytes object, which can be directly accessed by Python code.

## Prototype

```python
bytes_out = acl.util.ptr_to_bytes(ptr, size)
```

## Parameters

| Parameter| Description|
| --- | --- |
| ptr | Int, pointer address in the C language. It is the start address of the data that can be accessed.|
| size | Int, data size, in bytes.|

## Return Values

| Return Value| Description|
| --- | --- |
| bytes_out | bytes object|

## Precautions

Example modification:

```python
bytes_out = acl.util.ptr_to_bytes(bytes_ptr, size)
```

acl.util.ptr\_to\_bytes may cause data performance deterioration. Therefore, you are advised to use the data of the [acl.util.bytes\_to\_ptr](function-bytes_to_ptr.md) function for subsequent calculation.
