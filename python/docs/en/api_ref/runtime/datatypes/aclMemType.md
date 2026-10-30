# aclMemType

| Memory Type| Definition|
| --- | --- |
| ACL_MEMTYPE_DEVICE = 0 | Device memory.|
| ACL_MEMTYPE_HOST = 1 | Host memory.|
| ACL_MEMTYPE_HOST_COMPILE_INDEPENDENT = 2 | Host memory.|

>[!NOTE]
>Both ACL_MEMTYPE_HOST and ACL_MEMTYPE_HOST_COMPILE_INDEPENDENT identify the host memory, but they function differently:
>
>- ACL_MEMTYPE_HOST: If ACL_OP_JIT_COMPILE is set to `disable` by calling aclSetCompileopt, setting this option does not trigger operator rebuild when the input or output value of the operator changes. If ACL_OP_JIT_COMPILE is set to `enable` by calling aclSetCompileopt, setting this option triggers operator rebuild when the input or output value of the operator changes.
>- ACL_MEMTYPE_HOST_COMPILE_INDEPENDENT: When this option is set, changes in the input or output values of the operator do not trigger rebuild of the operator. If the operator build depends on the input or output value and ACL_MEMTYPE_HOST_COMPILE_INDEPENDENT is set, the build may fail.
