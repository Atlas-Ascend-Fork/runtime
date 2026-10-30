# Function: destroy\_aipp

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

Destroys data of the `aclmdlAIPP` type created by the [acl.mdl.create\_aipp](function-create_aipp.md) call.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlDestroyAIPP(const aclmdlAIPP *aippParmsSet)
    ```

- **Python Function**

    ```python
    ret = acl.mdl.destroy_aipp(aipp_parms_set)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| aipp_parms_set | Int, pointer address of the `aclmdlAIPP` data object to be destroyed.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|
