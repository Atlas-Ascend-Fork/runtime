# Function: memcpy2d

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

Implements synchronous memory copy, which is mainly used for matrix data replication.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtMemcpy2d(void *dst, size_t dpitch, const void *src, size_t spitch, size_t width, size_t height, aclrtMemcpyKind kind)
    ```

- **Python Function**

    ```python
    ret = acl.rt.memcpy2d(dst, dpitch, src, spitch, width, height, kind)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| dst | Int, pointer address of the destination memory address.|
| dpitch | Int, address distance between two adjacent columns of vectors in the destination memory.|
| src | Int, pointer address of the source memory address.|
| spitch | Int, address distance between two adjacent columns of vectors in the source memory.|
| width | Int, matrix width to be copied.|
| height | Int, matrix height to be copied.|
| kind | Int, memory copy type.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- Currently, only memory copy of the `ACL\_MEMCPY\_HOST\_TO\_DEVICE` and `ACL\_MEMCPY\_DEVICE\_TO\_HOST` types is supported.
<!-- npu="310p" id7 -->
- On Atlas inference products, this API cannot be called in open Ctrl CPU mode. In addition, Atlas inference acceleration modules do not support this API.
<!-- end id7 -->
<!-- npu="310b" id8 -->
- On Atlas 200I/500 A2 inference products, this API cannot be called in Ascend RC mode.
<!-- end id8 -->
