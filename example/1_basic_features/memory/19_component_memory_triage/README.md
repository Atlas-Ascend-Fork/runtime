# 19_component_memory_triage

## 描述

运维人员排查单 Device 上的组件内存占用时，本样例读取组件名称、当前占用和历史峰值，按每组件阈值生成排查建议，并输出按当前占用降序排列的报告。

默认当前占用阈值为 64 MiB，峰值阈值为 128 MiB。任一组件的当前占用达到阈值时，优先提示排查当前占用最大的组件；否则，若峰值达到阈值，则提示回看峰值最大的组件；两者均未达到阈值时输出 `WITHIN_BUDGET`。阈值可通过运行参数调整，判断结果仅用于排查建议，不代表程序失败。

样例检查返回数量、组件名称、当前占用不超过峰值以及当前占用的降序关系。查询数组填满时会扩大查询数量后重新获取快照，最多容纳 256 项；仍填满时报告失败，不输出完整报告。该上限是样例的保护值，不是接口规定的组件数量上限。

统计单位为 Byte，阈值参数单位为 MiB（1 MiB = 1048576 Byte）。统计值不表示剩余可分配内存，也不用于判断某次业务分配的精确增量、峰值发生时间或内存泄漏。

## 产品支持情况

| 产品 | 是否支持 |
| --- | --- |
| A2（Atlas A2系列产品） | √ |
| A3（Atlas A3系列产品） | √ |
| A5（Ascend 950PR/Ascend 950DT） | × |

## 编译运行

安装 CANN 并准备受支持的 Device 后，设置实际安装路径并运行：

```bash
export ASCEND_INSTALL_PATH=<CANN安装目录>
cd <runtime仓库>/example/1_basic_features/memory/19_component_memory_triage
bash run.sh
```

脚本加载 CANN 环境，在 `build/` 下构建并执行样例，使用可见 Device 0。可选参数依次为当前占用阈值、峰值阈值，均为正十进制整数，单位 MiB；只提供第一个参数时，峰值阈值保留默认值。

```bash
bash run.sh 1 128
bash run.sh 64 1
```

在本次实测的组件占用约 28 MiB 的环境中，上述两条命令分别输出 `CURRENT_PRESSURE` 和 `HISTORICAL_PEAK`。实际判断取决于运行时快照，可根据报告中的数值调整阈值复现。非法参数、查询失败、数据校验失败或清理失败均返回非零退出码，且不输出成功标记。

## CANN RUNTIME API

在该Sample中，涉及的关键功能点及其关键接口，如下所示：

- 初始化与单 Device 绑定：
  - `aclInit`：进行初始化配置。
  - `aclrtSetDevice`：绑定可见 Device 0。
- 组件内存排查：
  - `aclrtGetMemUsageInfo`：查询组件名称、当前内存占用和峰值，驱动排查优先级判断。（A2、A3支持，A5不支持）
- 资源清理：
  - `aclrtResetDevice`：释放所绑定 Device 的资源。
  - `aclFinalize`：实现去初始化。

## 示例输出

以下为默认阈值的一次成功运行，省略构建日志；组件名称、数量和内存统计随环境变化。

```text
[INFO]  Complete component snapshot: device=0 components=... capacity=8
[INFO]  Verified component names, current <= peak, and descending current usage
[INFO]  Per-component limits: current=67108864 bytes peak=134217728 bytes
[INFO]  Component[0] RUNTIME current=... bytes peak=... bytes
[INFO]  Triage: WITHIN_BUDGET; all reported components are below both limits
[INFO]  Component memory triage succeeded
```
