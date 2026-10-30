# Function: float16\_to\_float

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

Converts data from [aclFloat16](../datatypes/aclFloat16.md) to float32.

## Prototype

- **C Prototype**

    ```c
    float aclFloat16ToFloat(aclFloat16 value)
    ```

- **Python Function**

    ```python
    output = acl.float16_to_float(value)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| value | Int, data to be converted, of the [aclFloat16](../datatypes/aclFloat16.md) type.|

## Return Values

| Return Value| Description|
| --- | --- |
| output | Float.|
