# aclTransType

| Transposing Manner| Description|
| --- | --- |
| ACL_TRANS_N = 0 | Do not transpose (default)|
| ACL_TRANS_T = 1 | Transposition|
| ACL_TRANS_NZ = 2 | Transpose to internal format, which provides better interface performance. You are advised to use this format when an input matrix is used as the repository and the operator transposed to the NZ format will be reused.|
| ACL_TRANS_NZ_T = 3 | Transpose to internal format, reserved|
