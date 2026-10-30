# aclrtPhysicalMemProp

| Name| Description|
| --- | --- |
| handleType | Handle type. Currently, only `ACL_MEM_HANDLE_TYPE_NONE` is supported.|
| allocationType | Memory allocation type. Currently, only `ACL_MEM_ALLOCATION_TYPE_PINNED` is supported.|
| memAttr | Memory attributes. For details, see [aclrtMemAttr](../datatypes/aclrtMemAttr.md).|
| location | Memory location. For details, see [aclrtMemLocation](aclrtMemLocation.md). Refer to the following example. `id` indicates the device ID or NUMA ID, and `type` indicates the type of the memory location.<br>location = {<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;'id' : 0, <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;'type' : ACL_MEM_LOCATION_TYPE_DEVICE<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; } |
| reserve | Reserved.|
