# aclrtMemMallocPolicy

**A single enumeration item or multiple enumeration items are supported.**

- **Configure a single enumeration item:**

    If a value other than `ACL_MEM_TYPE_LOW_BAND_WIDTH` and `ACL_MEM_TYPE_HIGH_BAND_WIDTH` is configured, the system selects the high-bandwidth or low-bandwidth physical memory allocation based on the hardware support:

  - ACL\_MEM\_MALLOC\_HUGE\_FIRST
  - ACL\_MEM\_MALLOC\_HUGE\_ONLY
  - ACL\_MEM\_MALLOC\_NORMAL\_ONLY
  - ACL\_MEM\_MALLOC\_HUGE\_FIRST\_P2P
  - ACL\_MEM\_MALLOC\_HUGE\_ONLY\_P2P
  - ACL\_MEM\_MALLOC\_NORMAL\_ONLY\_P2P
  - ACL\_MEM\_MALLOC\_HUGE1G\_ONLY
  - ACL\_MEM\_MALLOC\_HUGE1G\_ONLY\_P2P
  - ACL\_MEM\_TYPE\_LOW\_BAND\_WIDTH   = 0x0100
  - ACL\_MEM\_TYPE\_HIGH\_BAND\_WIDTH  = 0x1000
  - ACL\_MEM\_ACCESS\_USER\_SPACE\_READONLY = 0x100000

    If `ACL_MEM_TYPE_LOW_BAND_WIDTH` or `ACL_MEM_TYPE_HIGH_BAND_WIDTH` is configured, the system uses `ACL_MEM_MALLOC_HUGE_FIRST` by default and preferentially allocates huge pages.

- **Configure multiple enumeration item bits or**:

    You can select one of the following two groups (for example, `ACL_MEM_MALLOC_HUGE_FIRST | ACL_MEM_TYPE_HIGH_BAND_WIDTH`):

  - ACL_MEM_MALLOC_HUGE_FIRST, ACL_MEM_MALLOC_HUGE_ONLY, ACL_MEM_MALLOC_NORMAL_ONLY
  - ACL_MEM_TYPE_LOW_BAND_WIDTH, ACL_MEM_TYPE_HIGH_BAND_WIDTH

**The enumerations are described as follows:**

- ACL\_MEM\_MALLOC\_HUGE\_FIRST = 0

    When the allocated memory is less than or equal to 1 MB, only normal page memory is allocated even under this memory allocation policy. When the allocated memory is greater than 1 MB, the allocation of huge page memory is prioritized. If the huge page memory is insufficient, normal page memory is allocated.

- ACL\_MEM\_MALLOC\_HUGE\_ONLY =1

    Allocate only huge page memory. If the huge page memory is insufficient, an error is returned.

- ACL\_MEM\_MALLOC\_NORMAL\_ONLY = 2

    Allocates only normal page memory. If the normal page memory is insufficient, an error is returned.

- ACL\_MEM\_MALLOC\_HUGE\_FIRST\_P2P = 3

    Applicable to inter-device memory copy. Prioritize the allocation of huge page memory. If huge page memory is insufficient, allocate normal page memory.

    <!-- npu="310b" id1 -->
    Atlas 200I/500 A2 inference products: This option is not supported in the current version.
    <!-- end id1 -->

- ACL\_MEM\_MALLOC\_HUGE\_ONLY\_P2P = 4

    Applicable to inter-device memory copy. Allocate only huge page memory. If the huge page memory is insufficient, an error is returned.

    <!-- npu="310b" id2 -->
    Atlas 200I/500 A2 inference products: This option is not supported in the current version.
    <!-- end id2 -->

- ACL\_MEM\_MALLOC\_NORMAL\_ONLY\_P2P= 5

    Applicable to inter-device memory copy. Allocate only normal page memory.

    <!-- npu="310b" id3 -->
    Atlas 200I/500 A2 inference products: This option is not supported in the current version.
    <!-- end id3 -->

- ACL\_MEM\_TYPE\_LOW\_BAND\_WIDTH = 6

    Allocates memory from the high-bandwidth physical memory.

    <!-- npu="310b" id4 -->
    For Atlas 200I/500 A2 inference products, this item is invalid. By default, the system selects the allocation rule based on hardware-supported memory types.
    <!-- end id4 -->

- ACL\_MEM\_TYPE\_HIGH\_BAND\_WIDTH = 7

    Allocates memory from the low-bandwidth physical memory.

    <!-- npu="310b" id5 -->
    For Atlas 200I/500 A2 inference products, this option is invalid. The system selects a memory type based on the memory type supported by the hardware by default.
    <!-- end id5 -->

- ACL\_MEM\_MALLOC\_HUGE1G\_ONLY = 8

    Allocates huge page memory with a granularity of 1 GB. If the allocated memory is not a multiple of 1 GB, it is rounded up to the nearest multiple of 1 GB. For example, if 1.9 GB memory is requested, 2 GB memory is actually allocated according to the round-up rule.

    If this item is configured, only 1 GB huge page memory is allocated. If the 1 GB huge page memory is insufficient, an error is returned. The 1 GB huge page resources are limited. You can use `ACL_MEM_MALLOC_HUGE_FIRST` to allocate huge pages.

    Compared with `ACL_MEM_MALLOC_HUGE_ONLY`, the memory allocation granularity of the `ACL_MEM_MALLOC_HUGE_ONLY` option is 2 MB. If you want to allocate a 1 GB huge page, 512 (1024/2) page tables are occupied. However, the memory allocation granularity of the ACL_MEM_MALLOC_HUGE1G_ONLY option is 1 GB. A 1 GB huge page occupies only one page table. This effectively reduces the number of page tables and expands the address range of the TLB (Translation Lookaside Buffer) cache, thereby improving the performance of discrete access. The TLB serves as a high-speed cache module within the AI Processor, storing mappings between recently accessed virtual addresses and their corresponding physical addresses.

    <!-- npu="910,310p,310b" id6 -->
    This option is not supported for Atlas 200I/500 A2 inference products, Atlas inference products, and Atlas training products.
    <!-- end id6 -->

- ACL\_MEM\_MALLOC\_HUGE1G\_ONLY\_P2P = 9

    Allocates huge page memory in granularity of 1 GB only in the scenario of memory copy between two devices. If the allocated memory is not a multiple of 1 GB, it is rounded up to the nearest multiple of 1 GB. For example, if 1.9 GB memory is requested, 2 GB memory is actually allocated according to the round-up rule.

    If this item is configured, only 1 GB huge page memory is allocated. If the 1 GB huge page memory is insufficient, an error is returned. The 1 GB huge page resources are limited. You can use the `ACL_MEM_MALLOC_HUGE_FIRST_P2P` option to apply for huge pages.

    Compared with `ACL_MEM_MALLOC_HUGE_ONLY_P2P`, the memory allocation granularity of the `ACL_MEM_MALLOC_HUGE_ONLY_P2P` option is 2 MB. If you want to allocate a 1 GB huge page, 512 (1024/2) page tables are occupied. However, the memory allocation granularity of the `ACL_MEM_MALLOC_HUGE1G_ONLY_P2P` option is 1 GB. A 1 GB huge page occupies only one page table. This effectively reduces the number of page tables and expands the address range of the TLB (Translation Lookaside Buffer) cache, thereby improving the performance of discrete access. The TLB serves as a high-speed cache module within the AI Processor, storing mappings between recently accessed virtual addresses and their corresponding physical addresses.

    <!-- npu="910,310p,310b" id7 -->
    This option is not supported for Atlas 200I/500 A2 inference products, Atlas inference products, and Atlas training products.
    <!-- end id7 -->

- ACL\_MEM\_ACCESS\_USER\_SPACE\_READONLY = 10

    Specifies that the allocated memory is read-only in user mode. Memory modification in user mode would fail.
