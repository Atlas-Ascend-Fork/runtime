# Function: numpy\_to\_ptr

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

## Prototype

```python
ptr = acl.util.numpy_to_ptr(data)
```

## Parameters

| Parameter| Description|
| --- | --- |
| data | Data of the numpy.ndarray type.|

## Return Values

| Return Value| Description|
| --- | --- |
| ptr | Int, memory data pointer address of the NumPy array.|

## Precautions

- To continue to use this API, ensure that the operating environment uses Python 3.8 or later and NumPy 1.22.0 or later.
- Example modification:

    ```python
    np_ptr = acl.util.numpy_to_ptr(np_arr_in)
    ```

    After modification:

    ```python
    bytes_in = np_arr_in.tobytes()
    bytes_ptr = acl.util.bytes_to_ptr(bytes_in)
    ```

- Before using the pointer address returned by this function, ensure that the lifetime of the input numpy.ndarray object has not ended (not deleted or reclaimed by the GC of Python). Otherwise, undefined behavior will occur.
- If the input numpy.ndarray array is non-contiguous in memory, the following information is displayed when the API is called:

    ```text
    Warning:The input ndarray is discontiguous. Please use acl.util.numpy_contiguous_to_ptr instead.
    ```

    Use [acl.util.numpy\_contiguous\_to\_ptr](function-numpy_contiguous_to_ptr.md) to obtain the address object of the NumPy array. Otherwise, when [acl.rt.memcpy](../memory/function-memcpy.md) is used to copy data, the copied data may be inconsistent with the target data because [acl.rt.memcpy](../memory/function-memcpy.md) copies contiguous memory addresses.

- You can use the flags attribute of the NumPy array to check whether the NumPy array is contiguous in memory.

    ```python
    print(data.flags)
    ```

    The results are as follows:

    ```text
    C_CONTIGUOUS : True
    F_CONTIGUOUS : False
    OWNDATA : True
    WRITEABLE : True
    ALIGNED : True
    WRITEBACKIFCOPY : False
    UPDATEIFCOPY : False
    ```

    `C\_CONTIGUOUS: True` indicates rows in the NumPy array are contiguous in memory. `F\_CONTIGUOUS: False` indicates columns in the NumPy array are not contiguous in memory.
