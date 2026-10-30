# aclprofAicoreMetrics

The AI Core performance metrics are described as follows:

ACL_AICORE_ARITHMETIC_UTILIZATION = 0: proportions of computation metrics.

ACL_AICORE_PIPE_UTILIZATION = 1: ratio of the time consumed by the compute unit to the time consumed by the MTE.

ACL_AICORE_MEMORY_BANDWIDTH = 2: proportions of external memory read/write instructions.

ACL_AICORE_L0B_AND_WIDTH = 3: proportions of internal memory read/write instructions.

ACL_AICORE_RESOURCE_CONFLICT_RATIO = 4: proportions of pipeline queue instructions.

ACL_AICORE_MEMORY_UB = 5: proportions of internal memory read/write instructions.

ACL_AICORE_L2_CACHE = 6: read/write cache hit counts and miss reallocation counts. Only Atlas A2 and Atlas A3 products are supported.

ACL_AICORE_L2_CACHE = 6: read/write cache hit counts and miss reallocation counts. Only Atlas 200I/500 A2 inference products are supported.

ACL_AICORE_PIPE_EXECUTE_UTILIZATION = 7: time consumption ratios of the compute units and MTEs. Only Atlas 200I/500 A2 inference products are supported.

ACL_AICORE_MEMORY_ACCESS = 8: bandwidth data volume of operator memory access on the core. Only Atlas A2 products and Atlas A3 products are supported.

ACL_AICORE_NONE = 0xFF: Data is not collected.
