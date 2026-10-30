# Overview

- If media data processing is involved, pay attention to the following points when using the memory:
    1. Media data processing has higher requirements on the memory for storing the input and output data (for example, the start address of the memory must be 128-byte aligned). Therefore, the following dedicated memory allocation APIs are required:
        - When calling [Media Data Processing V1](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/acce/dvpp/aclpythondevg_01_0220.html) APIs to crop or resize images, call the [acl.media.dvpp\_malloc](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/acce/dvpp/aclpythondevg_01_0223.html) API to allocate memory.
        - When calling [Media Data Processing V2](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/acce/dvpp/aclpythondevg_01_0411.html) APIs to crop or resize images, call the [acl.himpi.dvpp\_malloc](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/acce/dvpp/aclpythondevg_01_0416.html) API to allocate memory.

    2. The memory allocated by the preceding APIs can be used for media data processing and other tasks. For example, the output of media data processing can be used as the input of model inference to implement memory reuse and reduce memory copy.
    3. The address space accessed by media data processing is limited. You are advised to call [acl.rt.malloc](../memory/function-malloc.md), [acl.rt.malloc_host](function-malloc_host.md), or [acl.rt.malloc_cached](function-malloc_cached.md) described in [Memory Management](memory_management.md) to allocate memory for completing other tasks (such as model loading).

<!-- npu="910b" id6 -->
- For Atlas A2 products, if huge page memory on the device is required, note that the current version reserves huge page memory in advance to prevent insufficient huge page memory. Before using the huge page memory, you can call the acl.rt.get\_mem\_info API to query the free on-chip huge page memory (corresponding to the `ACL\_HBM\_MEM\_HUGE` type) and on-chip normal memory (corresponding to the `ACL\_HBM\_MEM\_NORMAL` type).
<!-- end id6 -->
<!-- npu="A3,910b,910,310p,310b" id7 -->
- In the Ascend EP mode, when an inference or training job is executed for the first time after the device is started, the AI CPU operators are migrated from the host to the device and cached on the device to improve performance. Therefore, some device memory (100 MB to 200 MB, varying depending on the chip) is occupied. If the device is restarted, the AI CPU operator buffer is released.

    This restriction applies to the following products:

  <!-- npu="310p" id1 -->
  - Atlas inference products
  <!-- end id1 -->
  <!-- npu="310b" id2 -->
  - Atlas 200I/500 A2 inference products
  <!-- end id2 -->
  <!-- npu="910" id3 -->
  - Atlas training products
  <!-- end id3 -->
  <!-- npu="910b" id4 -->
  - Atlas A2 training products
  <!-- end id4 -->
  <!-- npu="A3" id5 -->
  - Atlas A3 products
  <!-- end id5 -->

<!-- end id7 -->
