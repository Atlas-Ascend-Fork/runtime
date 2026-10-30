# Shape and Memory Size Calculation of Matrices A, B, and C

- If the transpose flag of matrices A, B, and C is set to `ACL_TRANS_N` or `ACL_TRANS_T` the size of the memory allocated to store the matrix data must match the actual data size. The formulas for calculating the shape and memory size are as follows:
    - Matrix A: shape = \(m, k\); Memory size = m \* k \* acl.data\_type\_size\(data\_type\_a\)
    - Matrix B: shape = \(k, n\) Memory size: = k \* n \* acl.data\_type\_size\(data\_type\_b\)
    - Matrix C: shape = \(m, n\); Memory size = m \* n \* acl.data\_type\_size\(data\_type\_c\)

- If the transpose flag of matrices A, B, and C is set to `ACL_TRANS_NZ`, the internal data format is used. The matrices are 4D. The formulas for calculating the shape and memory size are as follows (assuming that `m`, `k`, and `n` are the original axes):

    - When matrix A and matrix B are of type aclFloat16, `m`, `k`, and `n` should be rounded up to the nearest multiples of 16, respectively.
        - Matrix A: shape = \(⌈k/16⌉, ⌈m/16⌉, 16, 16\); memory size = ⌈m/16⌉ \* 16 \* ⌈k/16⌉ \* 16 \* acl.data\_type\_size\(data\_type\_a\)
        - Matrix B: shape = \(⌈n/16⌉, ⌈k/16⌉, 16, 16\); memory size = ⌈k/16⌉ \* 16 \* ⌈n/16⌉ \* 16 \* acl.data\_type\_size\(data\_type\_b\)
        - Matrix C: shape = \(⌈n/16⌉, ⌈m/16⌉, 16, 16\); memory size = ⌈m/16⌉ \* 16 \* ⌈n/16⌉ \* 16 \* acl.data\_type\_size\(data\_type\_c\)
        
    - When matrix A and matrix B are of type int8\_t, the axes to reduce should be rounded up to the nearest multiples of 32 and the axes not to reduce should be rounded up to the nearest multiples of 16, respectively.
        - Matrix A: shape = \(⌈k/32⌉, ⌈m/16⌉, 16, 32\); memory size = ⌈m/16⌉ \* 16 \* ⌈k/32⌉ \* 32 \* acl.data\_type\_size\(data\_type\_a\)
        - Matrix B: shape = \(⌈n/16⌉, ⌈k/32⌉, 32, 16\); memory size = ⌈k/32⌉ \* 32 \* ⌈n/16⌉ \* 16 \* acl.data\_type\_size\(data\_type\_b\)
        - Matrix C: shape = \(⌈n/16⌉, ⌈m/16⌉, 16, 16\); memory size = ⌈m/16⌉ \* 16 \* ⌈n/16⌉ \* 16 \* acl.data\_type\_size\(data\_type\_c\)

 >[!NOTE]NOTE
 >⌈ ⌉ indicates rounding-up.
