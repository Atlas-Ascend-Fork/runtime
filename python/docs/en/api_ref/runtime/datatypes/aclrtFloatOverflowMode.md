# aclrtFloatOverflowMode

| Data Format| Description|
| --- | --- |
| ACL_RT_OVERFLOW_MODE_SATURATION = 0 | Saturation mode. If this mode is used, the compute precision may be inaccurate. This mode is only compatible with earlier versions and will not be evolved in the future.|
| ACL_RT_OVERFLOW_MODE_INFNAN = 1 | /Inf/NaN mode (IEEE 754-compliant). This is the default mode.|
| ACL_RT_OVERFLOW_MODE_UNDEF = 2 | Reserved.|

<!-- npu="950" id1 -->
For Ascend 950PR&950DT products, only the Inf/NaN mode is supported.
<!-- end id1 -->

<!-- npu="910,310p,310b" id2 -->
For Atlas 200I/500 A2 inference products, Atlas inference products, and Atlas training products, only the saturation mode is supported.
<!-- end id2 -->
