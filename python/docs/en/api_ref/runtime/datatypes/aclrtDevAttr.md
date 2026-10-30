# aclrtDevAttr

Enumerated values and descriptions:

- ACL\_DEV\_ATTR\_AICPU\_CORE\_NUM  = 1

    Number of AICPUs

- ACL\_DEV\_ATTR\_AICORE\_CORE\_NUM = 101

    Number of AI Cores

- ACL\_DEV\_ATTR\_VECTOR\_CORE\_NUM = 201

    Number of vector cores.

- ACL\_DEV\_ATTR\_WARP\_SIZE = 202

    Number of threads in a warp. In the Single Instruction Multiple Thread (SIMT) programming model, a warp is a set of threads that execute the same instruction.

    <!-- npu="950" id1 -->
    Only Ascend 950PR&950DT products support this option.

    <!-- end id1 -->
    For product models that do not support this option, **0** is returned by default.

- ACL\_DEV\_ATTR\_MAX\_THREAD\_PER\_VECTOR\_CORE = 203

    Maximum number of threads that can reside on each vector core at the same time.

    <!-- npu="950" id2 -->
    Only Ascend 950PR&950DT products support this option.
    <!-- end id2 -->

    For product models that do not support this option, **0** is returned by default.

- ACL\_DEV\_ATTR\_LOCAL\_MEM\_PER\_VECTOR\_CORE = 204

    Maximum local memory that can be used on each VECTOR_CORE, in bytes.

    <!-- npu="950" id3 -->
    Only Ascend 950PR&950DT products support this option.

    <!-- end id3 -->
    For product models that do not support this option, **0** is returned by default.

- ACL\_DEV\_ATTR\_MAX\_GRID\_DIM\_X = 205

    Maximum value of the grid dimension X, used for grid configuration of thread blocks in the SIMT programming model.

    <!-- npu="950" id4 -->
    Only Ascend 950PR&950DT products support this option.

    <!-- end id4 -->
    For product models that do not support this option, **0** is returned by default.

- ACL\_DEV\_ATTR\_MAX\_GRID\_DIM\_Y = 206

    Maximum value of the grid dimension Y, used for grid configuration of thread blocks in the SIMT programming model.

    <!-- npu="950" id5 -->
    Only Ascend 950PR&950DT products support this option.

    <!-- end id5 -->
    For product models that do not support this option, **0** is returned by default.

- ACL\_DEV\_ATTR\_MAX\_GRID\_DIM\_Z = 207

    Maximum value of the grid dimension Z, used for grid configuration of thread blocks in the SIMT programming model.

    <!-- npu="950" id6 -->
    Only Ascend 950PR&950DT products support this option.

    <!-- end id6 -->
    For product models that do not support this option, **0** is returned by default.

- ACL\_DEV\_ATTR\_MAX\_BLOCK\_PER\_GRID = 208

    Maximum number of blocks in each grid, used for grid configuration of thread blocks in the SIMT programming model.

    <!-- npu="950" id7 -->
    Only Ascend 950PR&950DT products support this option.

    <!-- end id7 -->
    For product models that do not support this option, **0** is returned by default.

- ACL\_DEV\_ATTR\_MAX\_THREADS\_PER\_BLOCK = 209

    Maximum number of threads in each block, used for grid configuration of thread blocks in the SIMT programming model.

    <!-- npu="950" id8 -->
    Only Ascend 950PR&950DT products support this option.

    <!-- end id8 -->
    For product models that do not support this option, **0** is returned by default.

- ACL\_DEV\_ATTR\_MAX\_BLOCK\_DIM\_X = 210

    Maximum value of the block dimension X, used for thread block configuration in the SIMT programming model.

    <!-- npu="950" id9 -->
    Only Ascend 950PR&950DT products support this option.

    <!-- end id9 -->
    For product models that do not support this option, **0** is returned by default.

- ACL\_DEV\_ATTR\_MAX\_BLOCK\_DIM\_Y = 211

    Maximum value of the block dimension Y, used for thread block configuration in the SIMT programming model.

    <!-- npu="950" id10 -->
    Only Ascend 950PR&950DT products support this option.

    <!-- end id10 -->
    For product models that do not support this option, **0** is returned by default.

- ACL\_DEV\_ATTR\_MAX\_BLOCK\_DIM\_Z = 212

    Maximum value of the block dimension Z, used for thread block configuration in the SIMT programming model.

    <!-- npu="950" id11 -->
    Only Ascend 950PR&950DT products support this option.
    <!-- end id11 -->

    For product models that do not support this option, **0** is returned by default.

- ACL\_DEV\_ATTR\_TOTAL\_GLOBAL\_MEM\_SIZE = 301

    Total available memory on the device, in bytes.

- ACL\_DEV\_ATTR\_L2\_CACHE\_SIZE = 302

    L2 cache size, in bytes.

- ACL\_DEV\_ATTR\_SMP\_ID = 401

    Symmetric multiprocessing (SMP) ID, which is used to identify whether devices run on the same operating system.

- ACL\_DEV\_ATTR\_PHY\_CHIP\_ID = 402

    Physical chip ID.

- ACL\_DEV\_ATTR\_SUPER\_POD\_DEVICE\_ID = 403

    SuperPoD device ID, which indicates the device ID in the supernode product.

- ACL\_DEV\_ATTR\_SUPER\_POD\_SERVER\_ID = 404

    SuperPoD server ID, which indicates the server ID in the supernode product.

- ACL\_DEV\_ATTR\_SUPER\_POD\_ID = 405

    SuperPoD ID, which indicates the supernode ID in the cluster.

- ACL\_DEV\_ATTR\_CUST\_OP\_PRIVILEGE = 406

    Whether the custom operator can execute more system call permissions.

    The options are as follows:

  - **0**: The custom operator has limited system call permissions (for example, the write operation cannot be performed).
  - **1**: The custom operator can execute more system call permissions.

    <!-- npu="950" id12 -->
    Ascend 950PR&950DT products do not support this option.

    <!-- end id12 -->
- ACL\_DEV\_ATTR\_MAINBOARD\_ID = 407

    Mainboard ID.

- ACL\_DEV\_ATTR\_HD\_CONNECT\_TYPE = 408

    Interconnection protocol between the host and device.

    The options are as follows:

  - **0**: PCIe
  - **1**: Huawei Cache Coherence System (HCCS)
  - **2**: UnifiedBus (UB)

    <!-- npu="950" id13 -->
    Only Ascend 950PR&950DT products support this option.
    <!-- end id13 -->
    For product models that do not support this option, an error is returned.

- ACL\_DEV\_ATTR\_DEVICE\_FORM\_FACTOR = 409

    Device form.

    The options are as follows:

  - 0: PoD, indicating compute cabinets.
  - 1: A+K servers, indicating the Ascend + Kunpeng architectures.
  - 2: A+X servers, indicating the Ascend + non-Kunpeng architectures (such as x86).
  - 3: PCIe card

    <!-- npu="950" id14 -->
    Only Ascend 950PR&950DT products support this option.
    <!-- end id14 -->

- ACL\_DEV\_ATTR\_SUPER\_POD\_CHASSIS\_ID = 410

    SuperPoD chassis ID, which indicates the chassis ID in the supernode product.
    <!-- npu="950" id40 -->
    Only Ascend 950PR&950DT products support this option.
    <!-- end id40 -->
    For product models that do not support this option, an error is returned.
    
- ACL\_DEV\_ATTR\_IS\_VIRTUAL = 501

    Whether the instance is an Ascend virtual instance.

  - 0: not an Ascend virtualization instance, but a physical machine.
  - 1: Ascend virtual instance, which may be a VM or container.

- ACL\_DEV\_ATTR\_NPU\_ARCH = 601

    NPU architecture version.

    The mapping between product models and NPU architecture versions is as follows:

  <!-- npu="950" id15 -->
  - Ascend 950PR&950DT products: 3510
  <!-- end id15 -->
  <!-- npu="A3" id16 -->
  - Atlas A3 products: 2201
  <!-- end id16 -->
  <!-- npu="910b" id17 -->
  - Atlas A2 products: 2201
  <!-- end id17 -->
  <!-- npu="310b" id18 -->
  - Atlas 200I/500 A2 inference products: 3002
  <!-- end id18 -->
  <!-- npu="310p" id19 -->
  - Atlas inference products: 2002
  <!-- end id19 -->
  <!-- npu="910" id20 -->
  - Atlas training products: 1001
  <!-- end id20 -->

## Relationships Between AI Cores, Cube Cores, and Vector Cores

The definition of a Core helps you better understand the relationships between AI Cores, Cube Cores, and Vector Cores. A Core is a compute core with an independent Scalar compute unit. Generally, the Scalar compute unit provides multiple functions for the compute core, such as the single instruction multiple data (SIMD) instruction dispatch. Therefore, the Scalar compute unit is also called the intra-core scheduling unit. The AI data processing core unit varies with products. Currently, there are the following types:

- The AI data processing core unit is an AI Core.
  - In an AI Core, Cube and Vector share a Scalar scheduling unit.

        <!-- npu="910" id37 -->
        The Atlas training products are used as an example.
        <!-- end id37 -->

        ![](../figures/aicore_shares_one_scalar.png)

  - In an AI Core, a Cube and a Vector have their own Scalar scheduling units, which are also called a Cube Core and a Vector Core. In this case, a Cube Core and a group of Vector Cores are defined as an AI Core. The number of AI Cores is usually calculated based on the number of Cube Cores.

        <!-- npu="910b" id38 -->
        The Atlas A2 products are used as an example.
        <!-- end id38 -->

        ![](../figures/aicore_contains_multi_scalars.png)

- The AI data processing core unit consists of an AI Core and an independent Vector Core. The AI Core and Vector Core both have independent Scalar scheduling units.

    <!-- npu="310p" id39 -->
    The Atlas inference products are used as an example.
    <!-- end id39 -->

    ![](../figures/aicore_and_vectorcore.png)

## Relationships Between SuperPoD IDs, SuperPoD Server IDs, and SuperPoD Device IDs

![](../figures/podid_serverid_deviceid.png)
