# 为 ACL Graph 任务添加批次和操作说明

## 描述

查看 ACL Graph 调试文件时，只看任务类型和编号，不容易判断每条任务在处理哪批数据、执行什么操作。本样例演示为任务添加批次编号和操作说明，方便在图中找到对应的数据处理步骤。

样例用固定字节值模拟两批数据。两批数据共用一块 4096 字节的 Device 缓冲区，依次执行以下操作：

1. **第 0 批**：将缓冲区的每个字节填为 17，再复制到第 0 批独立的结果区。
2. **第 1 批**：复用同一缓冲区，将每个字节填为 34，再复制到第 1 批独立的结果区。

每批包含“填充”和“复制”两个任务。样例给这四个任务分别添加批次编号和操作名称，导出 `graph_task_annotations.json`，供读者查看每个任务的用途。

程序随后执行图并回读结果：第 0 批的 4096 个字节应全部为 17，第 1 批应全部为 34。这也检查了缓冲区被第二批复用后，第一批保存的结果仍然正确。

## 产品支持情况

| 产品 | 是否支持 |
| --- | --- |
| Atlas A2系列产品 | √ |
| Atlas A3系列产品 | √ |
| Ascend 950PR/Ascend 950DT | √ |


## 编译运行

依赖 CMake、C++17 编译器、Make 及可用的受支持 Device。程序使用当前可见的逻辑 Device 0；运行前使用 `npu-smi info` 确认设备属于支持的产品。

```bash
cd ${git_clone_path}/example/2_advanced_features/model_ri/6_graph_task_annotation
# 将 ${install_root} 替换为 CANN 安装根目录。
export ASCEND_INSTALL_PATH=${install_root}/cann
source "${ASCEND_INSTALL_PATH}/set_env.sh"
bash run.sh
```

脚本构建并运行 `build/main`，导出 `build/graph_task_annotations.json`，并逐字节校验两个批次的执行结果。程序日志同时打印到终端并保存至样例目录下的 `output_msg.txt`。任一构建、接口调用、清理或数据校验失败，脚本均返回非零值；全部成功时由程序输出 `Graph execution and data verification passed`。

查看任务标注：

1. 在 Chrome 中打开 `chrome://tracing/`，加载 `build/graph_task_annotations.json`。
2. 选择一个任务，在任务详情的 `args.ExtendInfo` 中查看 `batch_id`（第几批数据）、`op_name`（做什么操作）和 `description`（操作说明）。
3. 例如，`batch_id=1` 且 `op_name=ArchiveBatch` 的任务，就是把第 1 批数据复制到对应结果区的任务；该批数据的 `marker` 为 34。需要与其他日志关联时，可查看同一任务的 `Model Id`、`Stream Id` 和 `Task Id`。

标注名称与实际动作的对应关系如下：

| `op_name` | `business_phase` | 实际动作 |
| --- | --- | --- |
| `FillBatchMarker` | `prepare` | 将共享缓冲区的每个字节填为本批固定值 |
| `ArchiveBatch` | `archive` | 将共享缓冲区复制到本批独立的 Device 结果区 |

程序自动检查两批数据的执行结果；任务标注可按上述步骤查看。调试 JSON 用于查看图结构，时间轴上的间隔和长度不表示实际执行耗时。

## CANN RUNTIME API

在该Sample中，涉及的关键功能点及其关键接口，如下所示：

- 初始化与资源管理
    - `aclInit`、`aclFinalize`：进行初始化配置和去初始化。
    - `aclrtSetDevice`、`aclrtResetDeviceForce`：绑定及释放单 Device 资源。
    - `aclrtMalloc`、`aclrtFree`：申请及释放复用缓冲区和批次结果区。
    - `aclrtCreateStream`、`aclrtDestroyStream`：创建及销毁任务 Stream。
- 捕获与任务标注
    - `aclmdlRICaptureBegin`、`aclmdlRICaptureEnd`：开始及结束 ACL Graph 单流捕获。
    - `aclrtSetStreamAttribute`、`aclrtGetStreamAttribute`：设置并检查 `ACL_STREAM_ATTR_CACHE_OP_INFO` 算子信息缓存开关。
    - `aclrtCacheLastTaskOpInfo`：为当前线程最后下发的任务缓存算子描述，供后续性能数据采集使用，Host 缓冲区大小范围为 `(0, 64KB]`。本样例的描述包含标注名称、数据类型和元素数量。
    - `aclrtCacheLastTaskExtendInfo`：为同一任务缓存批次编号和操作说明等 UTF-8 JSON 信息，导出后位于 `args.ExtendInfo`，大小范围为 `(0, 4KB]`；样例按字符串实际字节数传入，不包含结尾空字符。
- 批次处理与结果验证
    - `aclrtMemset`：捕获前将结果区设置为区别于预期结果的初值。
    - `aclrtMemsetAsync`：录入批次标记填充任务。
    - `aclrtMemcpyAsync`：录入将本批数据复制到独立 Device 结果区的任务。
    - `aclmdlRIDebugJsonPrint`：导出包含业务扩展信息的调试 JSON。
    - `aclmdlRIExecuteAsync`、`aclrtSynchronizeStream`：执行图并等待任务完成。
    - `aclrtMemcpy`：将结果回读到 Host，逐字节验证各批次标记。
    - `aclmdlRIDestroy`：销毁模型运行实例及缓存信息，随后释放图引用的缓冲区。

任务下发与两个缓存接口位于同一 Host 线程，两者之间没有其他任务下发。捕获期间不执行同步操作；图使用的 Device 内存及 Host 标注字符串保留至模型销毁。

## 示例输出

成功运行后，会输出导出路径和两个批次的数据校验结果。


```text
[INFO]  Exported annotated graph: graph_task_annotations.json
[INFO]  Batch 0 verified: 4096 bytes, marker=17
[INFO]  Batch 1 verified: 4096 bytes, marker=34
[INFO]  Graph execution and data verification passed
```
