# Function: get\_soc\_name

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

Obtains the processor version of the current operating environment.

## Prototype

- **C Prototype**

    ```c
    const char *aclrtGetSocName()
    ```

- **Python Function**

    ```python
    name = acl.get_soc_name()
    ```

## Parameters

None

## Return Values

| Return Value| Description|
| --- | --- |
| name | Str, processor version. If the chip version fails to be obtained by calling this API, `None` is returned.|
