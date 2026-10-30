# Function: get\_cann\_version

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

Queries the CANN software package version.

## Prototype

- **C Prototype**

    ```c
    aclError aclsysGetCANNVersion(aclCANNPackageName name, aclCANNPackageVersion *version)
    ```

- **Python Function**

    ```python
    version, ret = acl.get_cann_version(name)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| name | Int, software package to be queried. For details, see [aclCANNPackageName](../datatypes/aclCANNPackageName.md). If the software package to be queried is not installed, an error is reported, and the error code is `100003`.|

## Return Values

| Return Value| Description|
| --- | --- |
| version | Dict, CANN software package version number. For details, see [aclCANNPackageVersion](../datatypes/aclCANNPackageVersion.md).|
| ret | Int. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
