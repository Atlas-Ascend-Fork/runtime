# aclrtPlaceHolderInfo

## Definition

```python
place_holder_list = [{"addrOffset": addr_offset, "dataOffset": data_offset}]
```

Description: placeholder mechanism information.

| Name| Description|
| --- | --- |
| addrOffset | Position offset to be updated. During launch, Runtime allocates the device memory and updates the device memory address to hostArgs. This parameter specifies the position offset to be updated.|
| dataOffset | Offset of the data area. The data area pointed to by `placeholder` needs to be copied to the device. This parameter specifies the address offset of the data area based on `hostArgs`.|
