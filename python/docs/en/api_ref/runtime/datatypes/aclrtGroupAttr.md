# aclrtGroupAttr

<!-- npu="310b" id1 -->
Atlas 200I/500 A2 inference products do not support this setting.
<!-- end id1 -->

<!-- npu="910" id2 -->
Atlas training products do not support this setting.
<!-- end id2 -->

<!-- npu="910b" id3 -->
Atlas A2 products do not support this setting.
<!-- end id3 -->

<!-- npu="A3" id4 -->
Atlas A3 products do not support this setting.
<!-- end id4 -->

<!-- npu="310p" id5 -->
In the open Ctrl CPU form of Atlas inference products, only `ACL_GROUP_AICORE_INT` and `ACL_GROUP_GROUPID_INT` can be configured.
<!-- end id5 -->

| Data Format| Description|
| --- | --- |
| ACL_GROUP_AICORE_INT= 0 | An int for the number of AI Cores corresponding to the group.|
| ACL_GROUP_AIV_INT = 1 | An int for the number of Vector Cores corresponding to the group.|
| ACL_GROUP_AIC_INT = 2 | An int for the number of AI CPU threads corresponding to the group.|
| ACL_GROUP_SDMANUM_INT = 3 | An int for the number of channels for asynchronous memory copy.|
| ACL_GROUP_SDMANUM_INT = 4 | An int for the number of streams that can be scheduled at the same time in the specified group. The value is less than or equal to 32. Currently, a maximum of 32 streams can be scheduled at the same time at the system level. The data type of the attribute value is integer.|
| ACL_GROUP_GROUPID_INT = 5 | Group ID. The data type of the attribute value is integer.|
