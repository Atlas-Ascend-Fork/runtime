# Function: get\_version (Discarded)

**Note: This API will be deprecated in future releases. Use [acl.sys.get\_version\_str](function-get_version_str.md) instead.**

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

Returns the version number. The pyacl version ID can be formatted as *A.B.C*, where *A* indicates incompatible changes, *B* indicates new APIs, and *C* indicates the patch version.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtGetVersion(int32_t *majorVersion, int32_t *minorVersion, int32_t *patchVersion)
    ```

- **Python Function**

    ```python
    major_version, minor_version, patch_version, ret = acl.get_version()
    ```

## Parameters

None

## Return Values

| Return Value| Description|
| --- | --- |
| major_version | Int, major version. The value starts from `1` and is incremented by 1 with each incompatible API change.|
| minor_version | Int, minor version. The value starts from `0` and is incremented by 1 with each newly added API.|
| patch_version | Int, Patch version. The value starts from 0, indicating that this version has only fixed bugs. The value is incremented by 1 if the `majorVersion` and `minorVersion` remain unchanged. When the `majorVersion` and `minorVersion` increase, `patchVersion` remains at `0`.|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
