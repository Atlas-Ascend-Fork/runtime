# Function: get\_mem\_info

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

Obtains the free and total memory sizes of an app with specified attributes, excluding the memory size reserved for the system.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtGetMemInfo(aclrtMemAttr attr, size_t *free, size_t *total)
    ```

- **Python Function**

    ```python
    free, total, ret = acl.rt.get_mem_info(attr)
    ```

## Parameters

| Parameter| Input/Output| Description|
| --- | --- | --- |
| attr | Input| Int, attribute value of the memory to be queried. For details, see [aclrtMemAttr](../datatypes/aclrtMemAttr.md).|

## Return Values

| Return Value| Description|
| --- | --- |
| free | Int, free memory size of the corresponding attribute, in bytes.|
| total | Int, total memory size of the corresponding attribute, in bytes.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- Before calling this API, you must specify the compute device (for example, by calling acl.rt.set\_device). Therefore, no device ID is involved in this API.
- Select the memory attribute based on the actual hardware support. Otherwise, the free memory size and total memory size output by this API call are both 0. If the hardware does not support HBM memory, the API automatically queries DDR memory information when you query HBM memory information. For example, when you query `ACL\_HBM\_MEM`, the API actually queries `ACL\_DDR\_MEM`.
