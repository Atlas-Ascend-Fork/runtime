# Function: bytes\_to\_ptr

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

Converts a `bytes` object into void* data. The converted data can be transferred to the C function for direct use.

## Prototype

```python
ptr = acl.util.bytes_to_ptr(data)
```

## Parameters

| Parameter| Description|
| --- | --- |
| data | Data of the bytes type.|

## Return Values

| Return Value| Description|
| --- | --- |
| ptr | Int, data that can be accessed by the C language.|

## Constraints

The input lifetime of this function must be greater than the output lifetime. Otherwise, undefined behaviors may occur.

## Precautions

Example modification:

```python
bytes_in = np_arr_in.tobytes()
bytes_ptr = acl.util.bytes_to_ptr(bytes_in)
```
