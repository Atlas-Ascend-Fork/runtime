# Function: float\_to\_float16

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

Converts data from float32 to [aclFloat16](../datatypes/aclFloat16.md).

## Prototype

- **C Prototype**

    ```c
    aclFloat16 aclFloatToFloat16(float value)
    ```

- **Python Function**

    ```python
    output = acl.float_to_float16(value)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| value | float: data to be converted.|

## Return Values

| Return Value| Description|
| --- | --- |
| output | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
