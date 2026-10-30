# Function: numpy\_contiguous\_to\_ptr

>[!NOTE]NOTE
>This API will be deprecated. Use [acl.util.bytes\_to\_ptr](function-bytes_to_ptr.md) instead.

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

Obtains the memory data pointer address of the numpy.ndarray array.

If the input numpy.ndarray array is non-contiguous in the memory, convert the non-contiguous memory into contiguous one and then obtain the memory data pointer address of the converted numpy.ndarray array.

## Prototype

```python
ptr, data_out = acl.util.numpy_contiguous_to_ptr(data_in)
```

## Parameters

| Parameter| Description|
| --- | --- |
| data_in | NumPy data.|

## Return Values

| Return Value| Description|
| --- | --- |
| ptr | Int, data that can be accessed by the C language.|
| data_out | NumPy data. If the memory of the input NumPy array data_in is not row-contiguous, the return value data_out is the NumPy array after the memory is converted to row-contiguous.|

## Constraints

If data of the int type is accessed, the memory data pointer address of the numpy.ndarray object needs to be converted into int.

## Precautions

- Example modification:

    ```python
    np_ptr, data_out = acl.util.numpy_contiguous_to_ptr(np_arr_in)
    ```

    After modification:

    ```python
    bytes_in = np_arr_in.tobytes()
    bytes_ptr = acl.util.bytes_to_ptr(bytes_in)
    ```

- To continue to use this API, ensure that the operating environment uses Python 3.8 or later and NumPy 1.22.0 or later.
- Before using the pointer address returned by this function, ensure that the lifetime of the input numpy.ndarray object has not ended (not deleted or reclaimed by the GC of Python). Otherwise, undefined behavior will occur.
