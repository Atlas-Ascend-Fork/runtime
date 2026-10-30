# Function: ptr\_to\_numpy

>[!NOTE]NOTE
>This API will be deprecated. Use [acl.util.ptr\_to\_bytes](function-ptr_to_bytes.md) instead.

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
output = acl.util.ptr_to_numpy(ptr, shape, type)
```

## Parameters

| Parameter| Description|
| --- | --- |
| ptr | Int, pointer address in the C language. It is the start address of the data that can be accessed.|
| shape | Tuple, shape of the NumPy to be constructed.|
| type | Int, data type of the data in ptr.<br>Some common types are provided below:<br>`0`: NPY_BOOL<br>`1`: NPY_BYTE, NPY_INT8<br>`2`: NPY_UINT8<br>`3`: NPY_SHORT, NPY_INT16<br>`4`: NPY_USHORT, NPY_UINT16<br>`5`: NPY_INT, NPY_INT32<br>`6`: NPY_UINT, NPY_UINT32<br>`7`: NPY_INT64<br>`8`: NPY_UINT64<br>`9`: NPY_LONGLONG<br>`10`: NPY_ULONGLONG<br>`11`: NPY_FLOAT32<br>`12`: NPY_DOUBLE<br>`23`: NPY_HALF, NPY_FLOAT16|

## Return Values

| Return Value| Description|
| --- | --- |
| output | NumPy type.|

## Precautions

- Example modification:

    ```python
    np_arr_out = acl.util.ptr_to_numpy(host_ptr, np_arr_in.shape, NPY_INT32)
    ```

    After modification:

    ```python
    bytes_out = acl.util.ptr_to_bytes(ptr, size)
    np_arr_out = np.frombuffer(bytes_out, dtype=np.int32).reshape(np_arr_in.shape)
    ```

- To continue to use this API, ensure that the operating environment uses Python 3.8 or later and NumPy 1.22.0 or later.
