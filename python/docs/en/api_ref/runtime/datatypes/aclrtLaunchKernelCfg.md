# aclrtLaunchKernelCfg

## Description

Provides configurations for task dispatch.

## Prototype

```python
cfg= [{"id": attr_id, "value": attr_value}]
```

Note: **cfg** can contain multiple dictionaries. Each dictionary contains an ID-value pair.

## Member

| Name| Description|
| --- | --- |
| attr_id | Int, attribute ID. For details, see [aclrtLaunchKernelAttrId](aclrtLaunchKernelAttrId-aclrtLaunchKernelAttrValue.md).|
| attr_value | Int, attribute value. For details, see [aclrtLaunchKernelAttrValue](aclrtLaunchKernelAttrId-aclrtLaunchKernelAttrValue.md).|

Note: `attr_id` and `attr_value` are used in pairs. The value of `attr_value` varies according to the value of `attr_id`.
