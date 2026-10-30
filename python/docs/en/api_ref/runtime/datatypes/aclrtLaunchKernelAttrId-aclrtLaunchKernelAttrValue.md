# aclrtLaunchKernelAttrId/aclrtLaunchKernelAttrValue

- ACL\_RT\_LAUNCH\_KERNEL\_ATTR\_SCHEM\_MODE = 1

    Scheduling mode. The options are as follows:

  - **0**: common scheduling mode. If there is an idle core, the operator execution is started. For example, if **blockDim** is set to **8**, the operator kernel function will be executed on eight cores. If the common scheduling mode is specified, the operator execution is started as long as one core is idle.
  - **1**: batch scheduling mode. The operator execution is started only when all required cores are idle. For example, if **blockDim** is set to **8**, the operator kernel function will be executed on eight cores. If the batch scheduling mode is specified, the operator execution is started only when all the eight cores are idle.

- ACL\_RT\_LAUNCH\_KERNEL\_ATTR\_DYN\_UBUF\_SIZE = 2

    Size of the dynamic Unified Buffer (UB) required for executing the Single Instruction Multiple Threads (SIMT) operator, in bytes. For pure SIMD operators, this parameter can only be set to **0**.

    <!-- npu="950" id1 -->
    Only Ascend 950PR&950DT products support this parameter.
    <!-- end id1 -->

- ACL\_RT\_LAUNCH\_KERNEL\_ATTR\_ENGINE\_TYPE = 3

    Operator execution engine. For details about the value, see [aclrtEngineType](aclrtEngineType.md).

    <!-- npu="310p" id2 -->
    Only Atlas inference products support this parameter.
    <!-- end id2 -->

- ACL\_RT\_LAUNCH\_KERNEL\_ATTR\_BLOCKDIM\_OFFSET

    numBlocks offset.

  - **If numBlocks ≤ Number of AI Cores**, computation on the Vector Core is not required. In this case, set engineType to `ACL_RT_ENGINE_TYPE_AIC` (indicating computation on the AI Core) and set `blockDimOffset` to `0`.
  - **numBlocks > AI Core cores**:

    - Deliver a task in one stream, set engineType to `ACL_RT_ENGINE_TYPE_AIC` (indicating computation on the AI Core), and set `blockDimOffset` to `0`.
    - Deliver a task in another stream, set `engineType` to `ACL_RT_ENGINE_TYPE_AIV` (indicating computation on the Vector Core), and set `blockDimOffset` to `aicorenumBlocks`. The formula for calculating `aicorenumBlocks` is as follows:
      - If numBlocks ≤ Number of AI Cores + Number of Vector Cores, then aicorenumBlocks = Number of AI Cores.
      - Otherwise, aicorenumBlocks = Roundup (numBlocks x Number of AI Cores)/(Number of AI Cores + Number of Vector Cores).

        <!-- npu="310p" id3 -->
        Only Atlas inference products support this parameter.
        <!-- end id3 -->

- ACL\_RT\_LAUNCH\_KERNEL\_ATTR\_BLOCK\_TASK\_PREFETCH

    Whether to block hardware from prefetching the information of the current task when the task is delivered.

    The options are as follows:

  - **0**: Do not block.
  - **1**: Block.

- ACL\_RT\_LAUNCH\_KERNEL\_ATTR\_DATA\_DUMP

    Whether to enable dump.

    The options are as follows:

  - `0`: disabled
  - `1`: enabled

- ACL\_RT\_LAUNCH\_KERNEL\_ATTR\_TIMEOUT

    Timeout interval for the task scheduler to wait for task execution. This parameter applies only to the scenario where the AI CPU or AI Core operator is executed.

    The options are as follows:

  - `0`: permanent waiting
  - `> 0`: specific timeout interval, in seconds
