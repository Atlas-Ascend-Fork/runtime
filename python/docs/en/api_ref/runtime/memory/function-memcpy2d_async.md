# Function: memcpy2d\_async

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

Implements asynchronous memory copy, often used for matrix data replication. This API is asynchronous.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtMemcpy2dAsync(void *dst, size_t dpitch, const void *src, size_t spitch, size_t width, size_t height, aclrtMemcpyKind kind, aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret = acl.rt.memcpy2d_async(dst, dpitch, src, spitch, width, height, kind, stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| dst | Int, pointer address of the destination memory address.|
| dpitch | Int, address distance between two adjacent columns of vectors in the destination memory.|
| src | Int, pointer address of the source memory address.|
| spitch | Int, address distance between two adjacent columns of vectors in the source memory.|
| width | Int, matrix width to be copied.<br>It must be less than or equal to dpitch and spitch. The maximum value of width is 5,000,000.|
| height | Int, matrix height to be copied.<br>The maximum value of `height` is 5 x 1024 x 1024 = 5,242,880. Otherwise, the API returns a failure message.|
| kind | Int, memory copy type.<br>ACL_MEMCPY_HOST_TO_HOST = 0 // Copy memory within the host.<br>ACL_MEMCPY_HOST_TO_DEVICE = 1 // Copy memory from the host to the device.<br>ACL_MEMCPY_DEVICE_TO_HOST = 2 // Copy memory from the device to the host.<br>ACL_MEMCPY_DEVICE_TO_DEVICE = 3 // Copy memory within the device.<br>ACL_MEMCPY_DEFAULT = 4 // The system determines the copy direction based on the source and destination memory addresses.|
| stream | Int, pointer address of the stream.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- This API is asynchronous. A successful call indicates only that the task has been delivered, not that it has completed. After this API is called, call the synchronization API (for example, [acl.rt.synchronize\_stream](../stream/function-synchronize_stream.md)) to ensure that the memory copy task is complete.
- This API supports only the ACL\_MEMCPY\_HOST\_TO\_DEVICE, ACL\_MEMCPY\_DEVICE\_TO\_HOST, or ACL\_MEMCPY\_DEVICE\_TO\_DEVICE memory copy type. The supported types vary according to the model. For unsupported memory copy types, the API returns ACL\_ERROR\_INVALID\_PARAM.

    <!-- npu="950,A3,910b" id7 -->
    The `ACL\_MEMCPY\_DEVICE\_TO\_DEVICE` type is supported by the following models:

    <!-- npu="950" id10 -->
    Ascend 950PR&950DT products
    <!-- end id10 -->

    <!-- npu="A3" id11 -->
    Atlas A3 products
    <!-- end id11 -->

    <!-- npu="910b" id12 -->
    Atlas A2 products
    <!-- end id12 -->
    <!-- end id7 -->

<!-- npu="310p" id8 -->
- On Atlas inference products, this API cannot be called in open Ctrl CPU mode. In addition, Atlas inference acceleration modules do not support this API.
<!-- end id8 -->
<!-- npu="310b" id9 -->
- On Atlas 200I/500 A2 inference products, this API cannot be called in Ascend RC mode.
<!-- end id9 -->
