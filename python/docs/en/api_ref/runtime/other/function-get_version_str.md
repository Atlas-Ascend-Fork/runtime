# Function: get\_version\_str

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

Queries the version number based on a software package name. The version number is a character string. It is the same as the value of `version` in the `version.info` file in the package installation directory.

## Prototype

- **C Prototype**

    ```c
    aclError aclsysGetVersionStr(char *pkgName, char *versionStr)
    ```

- **Python Function**

    ```python
    version_str, ret = acl.get_version_str(pkgName)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| pkgName | Str, software package name.<br>The CANN package name must be the same as the directory name in `${INSTALL_DIR}/share/info`. `${INSTALL_DIR}` must be replaced with the actual CANN installation path. For example, if the installation is performed by the `root` user, the default file storage path is `/usr/local/Ascend/cann`.<br>The driver package name is `driver`.<br>The firmware package name is `firmware`.|

## Return Values

| Return Value| Description|
| --- | --- |
| version_str | Str, version number of the string type.|
| ret | Int. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
