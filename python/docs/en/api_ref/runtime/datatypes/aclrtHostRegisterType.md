# aclrtHostRegisterType

| Data Format| Description|
| --- | --- |
| ACL_HOST_REGISTER_MAPPED = 0 | Maps and registers the host memory as accessible to the device, including read and write.|
| ACL_HOST_REGISTER_IOMEMORY = 4 | Maps and registers the I/O space (registers and caches) of a third-party PCIe device on the host as accessible to the device, including read and write.|
| ACL_HOST_REGISTER_READONLY = 8 | Maps and registers the host memory as read-only to the device. Reserved. Not supported yet.|

<!-- npu="A3" id1 -->
For Atlas A3 products, if `ACL_HOST_REGISTER_IOMEMORY` is set, only the x86 architecture is supported. The Arm architecture is not supported.
<!-- end id1 -->
