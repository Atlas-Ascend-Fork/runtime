<!-- ==================== HERO Section ==================== -->

<h1 align="center">CANN Runtime</h1>

<p align="center">
  <b>Lightweight Runtime Environment for Ascend AI Processors · Edge-Cloud Consistency · High-Performance Inference</b><br>
  CANN Runtime is the core runtime foundation of Ascend AI processors. By providing a unified API, it enables upper-layer applications, AI frameworks, and acceleration libraries to efficiently use the hardware compute resources of AI processors.
</p>

---

<!-- ==================== Document Navigation ==================== -->
## 📚 Document Navigation

| Document | Positioning and Content | Entry |
|------|-----------|------|
| **⚡ Quick Start** | Serves you as a beginner starting from zero on your first contact with Runtime. It provides a Runtime overview + programming model explanation. Read the documents in order | [Runtime Overview](quick_start/Runtime_overview.md) · [Programming Model](quick_start/Runtime_programming_model.md) |
| **📖 Programming Guide** | An in-depth development manual for you after you run Hello CANN in the entry stage and need to deeply understand the principles. Principle analysis + example code | [Programming Guide](dev_guide/README.md) |
| **📋 API Reference** | An API dictionary for you to look up function definitions at any time during development. Function signatures + parameter descriptions + return values | [Header File Description](api_ref/01_overview.md) · [API Reference](api_ref/README.md) |
| **📋 Log Reference** | Describes how to set the log level and where to obtain log files when you locate faults. It also describes the log content format and log configuration. | [Log Reference](log_ref/README.md) |
| **📋 Error Code Reference** | An error code dictionary for you to look up the error message, possible cause, and solution of each error code during debugging. | [Error Code Reference](error_code_ref/README.md) |
| **📋 Environment Variable Reference** | An environment variable dictionary for you to look up the function, value, configuration method, and usage constraint of each environment variable during development and running. | [Environment Variable Reference](env_vars/README.md) |
| **🏗️ Architecture Guide** | Architecture documentation for contributors. It covers the overall Runtime architecture, module design, and analysis of core components | [Architecture Guide](design/README.md) |
| **📝 R&D Specifications** | Specification guides for contributors, including a design document template, coding guidelines, test specifications, and code review rules | [R&D Specifications and Contribution Guide](guidelines/README.md) |

---

<!-- ==================== Learning Roadmap ==================== -->
## 🗺️ Learning Roadmap

Follow the paths below step by step, from environment preparation to independent development:

### 🌱 Entry Stage

| Learning Step | Description | Entry |
|---------|---------|------|
| **Environment Preparation** | One-click CANN installation | [One-Click CANN Installation](https://www.hiascend.com/cann/download) |
| **Concepts and Principles** | Core Runtime concepts and the programming model: Host-Device architecture, Context, Stream, synchronous and asynchronous modes, and the typical execution flow | [Runtime Overview](quick_start/Runtime_overview.md) · [Programming Model](quick_start/Runtime_programming_model.md) |
| **Hello CANN** | The first runnable Runtime program, which completes a minimal compute loop | [Hello CANN](../../example/0_quickstart/0_hello_cann/README.md) |

---

### 🚀 Intermediate Stage

| Topic | Core Content | Corresponding Sample |
|------|---------|---------|
| **Initialization** | Includes environment initialization, device resource configuration, log management, and so on | [device_normal](../../example/1_basic_features/device/0_device_normal/README.md) |
| **Memory Management** | Includes host machine memory management, Device memory management, multi-stream synchronization memory, memory copy (synchronous and asynchronous), and physical memory sharing (pid) | [h2d_sync_memory_copy](../../example/1_basic_features/memory/1_h2d_sync_memory_copy/README.md) |
| **Asynchronous Tasks** | Includes Stream management, Event management, kernel loading and execution, and memory semantic synchronization | [simple_stream](../../example/1_basic_features/stream/0_simple_stream/README.md) |

---

### 🔥 Advanced Stage

| Topic | Core Content | Corresponding Sample |
|------|---------|---------|
| **ACL Graph** | Includes single-stream capture, cross-stream capture, and task update | [model_update](../../example/2_advanced_features/model_ri/1_model_update/README.md) |
| **Multi-Device Programming** | Includes cross-Device data interaction, P2P memory access, and multi-card parallel scheduling | [device_P2P](../../example/1_basic_features/device/2_device_P2P/README.md) |
| **Inter-Process Communication** | Includes IPC Event synchronization and IPC memory sharing (with or without a specified PID) | [ipc_event](../../example/2_advanced_features/ipcevent/0_ipcevent/README.md) · [ipc_memory](../../example/1_basic_features/memory/11_ipc_memory_withoutpid/README.md) |
| **Performance Tuning** | Includes Profiling collection and dumping to disk, obtaining performance data of operators in the network model, and visually displaying parsed raw performance data | [create_config](../../example/5_performance/profiling/0_create_config/README.md) |

---

<!-- ==================== FAQ ==================== -->
## ❓ FAQ

| Problem Type | Typical Scenario | Entry |
|---------|---------|------|
| **Entry Stage** | Common entry-level problems such as initialization failures, Device configuration, and version compatibility | [Version Mismatch](FAQ/mismatch_version_between_Runtime_and_CANN.md) · [aclInit Failure](FAQ/aclInit_initialization_failures.md) · [aclrtSetDevice Failure](FAQ/aclrtSetDevice_call_failure.md) · [Time Consumption of the First aclrtSetDevice Call](FAQ/first_time_aclrtSetDevice_task_long_time.md) · [Default Mechanisms](FAQ/understand_default_device_and_default_stream.md) |
| **Basic Development** | Basic API usage problems such as memory management, Stream synchronization, and data copy | [Memory Allocation Failure](FAQ/aclrtMalloc_allocation_failures.md) · [Stream Delivery Failure](FAQ/aclrtMemcpyAsync_fail_in_incorrect_stream.md) · [Memory Policy](FAQ/select_proper_mem_allocation_policy.md) · [Synchronization Mechanisms](FAQ/diff_between_Stream_and_Event_sync.md) |
| **Intermediate Scenarios** | Complex scenario problems such as multi-device programming, ACL Graph, and inter-process communication | [Multi-Device Stream](FAQ/multi_devices_stream_tasks_deliver_fail.md) · [ACL Graph Task Submission](FAQ/ACLGraph_restrictions.md) · [IPC Page Table Alignment](FAQ/inter_process_IPC_page_table_align_requirements.md) · [P2P Configuration Failure](FAQ/cross_device_data_interaction_configuration_fail.md) |
| **Fault Diagnosis** | Diagnosis methods such as error code interpretation, operator exceptions, and log-based fault location | [Asynchronous Error Codes](FAQ/obtain_and_understand_Runtime_async_errCodes.md) · [EE1023 Insufficient Resources](FAQ/EE1023_insufficient_resource.md) · [Abnormal Operator Output](FAQ/all_zero_output_common_causes.md) · [Stop-on-Error Fault Location](FAQ/stop_on_error_locate_method.md) · [plog Log-Based Fault Location](FAQ/use_plog_locate_device_exceptions.md) |

---

<!-- ==================== Bottom Links ==================== -->
<p align="center">
  <b>Related Resources</b><br>
  <a href="https://www.hiascend.com">Ascend Community</a> ·
  <a href="../../example/README.md">Runtime Sample Repository</a> ·
  <a href="https://www.hiascend.com/document">Full Documentation Center</a>
</p>

<p align="center">
  <sub>CANN Runtime Documentation | Ascend</sub>
</p>
