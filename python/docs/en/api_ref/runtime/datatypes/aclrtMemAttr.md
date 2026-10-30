# aclrtMemAttr

- ACL\_DDR\_MEM = 0

    DDR memory, that is, all huge page memory and normal page memory on the DDR.

- ACL\_HBM\_MEM = 1

    High bandwidth memory, including all huge pages and common pages.

- ACL\_DDR\_MEM\_HUGE = 2

    DDR hugepage memory.

- ACL\_DDR\_MEM\_NORMAL = 3

    Normal DDR memory.

- ACL\_HBM\_MEM\_HUGE = 4

    Huge page of on-chip memory.

- ACL\_HBM\_MEM\_NORMAL = 5

    Common page of on-chip memory.

- ACL\_DDR\_MEM\_P2P\_HUGE = 6

    Huge page memory for inter-device memory copy.

- ACL\_DDR\_MEM\_P2P\_NORMAL = 7

    Normal page memory for inter-device memory copy.

- ACL\_HBM\_MEM\_P2P\_HUGE = 8

    Huge page memory for inter-device memory copy.

- ACL\_HBM\_MEM\_P2P\_NORMAL = 9

    Normal page memory for inter-device memory copy.

- ACL\_HBM\_MEM\_HUGE1G = 10

    Huge page, the memory allocation granularity is 1 GB. If the memory is less than 1 GB, it is rounded up to 1 GB.

- ACL\_HBM\_MEM\_P2P\_HUGE1G = 11

    Huge page memory for inter-device memory copy. The memory allocation granularity is 1 GB. If the memory is less than 1 GB, it is rounded up to 1 GB.

The preceding options are compatible with earlier versions. You need to select memory attribute options that match the hardware memory (DDR or on-chip memory).

The following options automatically select DDR or on-chip memory based on the underlying hardware memory. You do not need to pay attention to hardware details. The following options are recommended.

- ACL\_MEM\_NORMAL = 12

    Normal DDR memory.

- ACL\_MEM\_HUGE = 13

    Huge page, the memory allocation granularity is 2 MB. If the memory is less than 2 MB, it is rounded up to 2 MB.

- ACL\_MEM\_HUGE1G = 14

    Huge page, the memory allocation granularity is 1 GB. If the memory is less than 1 GB, it is rounded up to 1 GB.

- ACL\_MEM\_P2P\_NORMAL = 15

    Normal page memory for inter-device memory copy.

- ACL\_MEM\_P2P\_HUGE = 16

    Huge page memory for inter-device memory copy. The memory allocation granularity is 2 MB. If the memory is less than 2 MB, it is rounded up to 2 MB.

- ACL\_MEM\_P2P\_HUGE1G = 17

    Huge page memory for inter-device memory copy. The memory allocation granularity is 1 GB. If the memory is less than 1 GB, it is rounded up to 1 GB.

To allocate a huge page of 1 GB, if the allocation granularity is 2 MB, 512 (1024/2) page tables are used. If the allocation granularity is 1 GB, only one page table is used by the huge page of 1 GB. This reduces the number of page tables, expands the address range of the translation lookaside buffer (TLB), and improves the discrete access performance. The TLB serves as a high-speed cache module within the AI Processor, storing mappings between recently accessed virtual addresses and their corresponding physical addresses.

<!-- npu="A3,910b" id1 -->
Only Atlas A3 and Atlas A2 products support Huge1G options.
<!-- end id1 -->
