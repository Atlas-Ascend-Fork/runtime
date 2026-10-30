# aclrtMemLocationType

| Data Format| Description|
| --- | --- |
| ACL_MEM_LOCATION_TYPE_HOST = 0 | Host memory allocated by the ACL API (for example, aclrtMallocHost).|
| ACL_MEM_LOCATION_TYPE_DEVICE = 1 | Device memory allocated through the ACL API (for example, aclrtMalloc).|
| ACL_MEM_LOCATION_TYPE_UNREGISTERED = 2 | Memory that is not allocated through the ACL API.|
| ACL_MEM_LOCATION_TYPE_MANAGED = 3 | Unified virtual memory (UVM).|
| ACL_MEM_LOCATION_TYPE_HOST_NUMA = 4 | Host memory allocated by using the aclrtMallocPhysical API based on the NUMA ID.|
