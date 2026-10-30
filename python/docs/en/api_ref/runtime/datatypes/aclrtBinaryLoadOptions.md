# aclrtBinaryLoadOptions

## Description

Optional parameter for loading the operator binary file.

## Definition

```python
options = [{"type": option_type, "value": option_value}]
```

Note: Options can contain multiple dictionaries. Each dictionary contains a type-value pair.

## Member

| Name| Description|
| --- | --- |
| option_type | Int, parameter type. For details, see [aclrtBinaryLoadOptionType](aclrtBinaryLoadOptionType-aclrtBinaryLoadOptionValue.md).|
| option_value | Int, parameter value. For details, see [aclrtBinaryLoadOptionValue](aclrtBinaryLoadOptionType-aclrtBinaryLoadOptionValue.md).|

Note: `option_type` and `option_value` are used in pairs. The value of `option_value` varies according to the value of `option_type`.
