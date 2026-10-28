# 定位自定义算子的执行错误

## 描述

本样例演示自定义算子执行出错后，如何通过异常回调找到出错的设备、任务和核函数，适合调试自己开发的 Ascend C 算子。

样例使用一个名为 `checked_increment` 的简单算子，将输入整数加 1。运行过程分为三步：

1. **先确认算子能正常计算**：输入 41，检查结果是否为 42，并确认没有收到异常通知。
2. **再模拟一次执行错误**：给同一个算子打开故障开关，让它主动触发一次错误。
3. **核对故障位置**：分别从应用统一注册的进程级回调、为该算子二进制文件注册的回调中读取故障信息，检查它们是否指向同一 Device、Stream 和 Task，错误码是否一致，再确认出错的核函数就是 `checked_increment`。

运行后可以看到正常计算结果，以及两种回调报告的故障位置。故障后的处理是检查信息、清理资源并退出。

## 产品支持情况

| 产品 | 是否支持 |
| --- | --- |
| Atlas A2系列产品 | √ |
| Atlas A3系列产品 | √ |
| Ascend 950PR/Ascend 950DT | √ |


## 编译运行

样例会主动执行一次 `trap` 指令，使 Device 任务报错。请在独立的测试 Device 上运行。运行中出现这次故障的 Runtime 错误日志属于预期现象；样例检查故障信息后清理资源并退出。

1. 安装匹配的驱动、固件和 CANN Toolkit，进入当前样例目录，设置 CANN 安装路径。

   ```bash
   cd ${git_clone_path}/example/2_advanced_features/callback/3_operator_fault_diagnosis
   export ASCEND_INSTALL_PATH=${install_root}/cann
   source "${ASCEND_INSTALL_PATH}/set_env.sh"
   ```

2. 使用 `npu-smi info` 确认当前 Device 属于上表支持的产品。样例使用当前可见设备中的逻辑 Device `0`；可通过 `ASCEND_VISIBLE_DEVICES` 选择测试设备。检测实际芯片型号和 Ascend C 构建目录：

   ```bash
   npu-smi info
   source ../../../set_sample_env.sh
   echo "${SOC_VERSION}"
   echo "${ASCENDC_CMAKE_DIR}"
   ```

   `SOC_VERSION` 必须与实际芯片一致，例如 A2 的 `Ascend910B1`、A3 的 `Ascend910_9362` 或对应 A5 芯片型号。`ASCENDC_CMAKE_DIR` 必须包含 `ascendc.cmake` 和 `asc_modules/FindASC.cmake`；例如 `${ASCEND_INSTALL_PATH}/compiler/tikcpp/ascendc_kernel_cmake`。不包含原生 ASC CMake 模块的旧工具链无法构建本样例。

3. 构建并运行：

   ```bash
   bash run.sh
   ```

   脚本在 `build/` 中生成并执行 `main`，同时加载该目录下的 `operator_fault_kernel.o`。单次同步最多等待 30 秒，故障同步返回后最多等待 5 秒收集回调。故障后的 Stream 被强制销毁，算子二进制及内存被释放，进程级回调被注销，随后执行 Device 资源清理和去初始化。

## CANN RUNTIME API

在该Sample中，涉及的关键功能点及其关键接口，如下所示：

- 进程级异常回调的注册与注销：`aclrtExceptionInfoCallbackRegister` 注册用于收集异常的回调，以及一个用于演示注销的临时回调。`aclrtExceptionInfoCallbackUnregister` 在任务下发前注销临时回调，并在退出时注销收集异常的回调；临时回调的调用次数应始终为 0。
- 查找出错的核函数：`aclrtBinarySetExceptionCallback` 为加载的算子二进制文件注册异常回调及用户数据，`aclrtGetFuncHandleFromExceptionInfo` 从该回调的异常信息中获取出错的核函数句柄。
- 任务关联和错误校验：`aclrtStreamGetId`、`aclrtGetThreadLastTaskId` 获取实际提交的任务标识；`aclrtGetDeviceIdFromExceptionInfo`、`aclrtGetStreamIdFromExceptionInfo`、`aclrtGetTaskIdFromExceptionInfo`、`aclrtGetErrorCodeFromExceptionInfo` 读取异常字段。
- 算子加载、执行和卸载：`aclrtBinaryLoadFromFile`、`aclrtBinaryGetFunction`、`aclrtLaunchKernelWithHostArgs`、`aclrtBinaryUnLoad`。
- Stream 遇错即停及同步：`aclrtCreateStream`、`aclrtSetStreamFailureMode`、`aclrtSynchronizeStreamWithTimeout`、`aclrtDestroyStream`、`aclrtDestroyStreamForce`。
- 正常计算结果与内存管理：`aclrtMalloc`、`aclrtMemset`、`aclrtMemcpy`、`aclrtFree`。
- 初始化及 Device 资源管理：`aclInit`、`aclrtSetDevice`、`aclrtResetDeviceForce`、`aclFinalize`。

回调仅在调用期间读取异常字段并复制必要值，不保存 Runtime 管理的异常指针，不执行任务下发、同步或资源释放。注销接口不会等待已进入通知流程的回调；本样例使用静态存储保留回调状态及用户数据，直到进程退出。

## 示例输出

`Healthy task verified` 表示正常计算得到 42。`Process fault` 和 `Binary fault` 分别是进程级回调、算子二进制回调收集的故障信息，两行中的设备、Stream、Task 和错误码应一致；`Fault attributed to checked_increment` 表示核函数也已核对正确。

预期的任务报错、两种回调及资源清理都通过检查后，程序才打印最后一行成功日志并以 0 退出。故障任务同步成功或超时、缺少回调、信息不一致以及清理失败，都会使样例非零退出。

Stream ID、Task ID 和错误码等环境相关值以 `...` 表示，构建输出省略。

```text
[INFO]  Healthy task verified: 41 + 1 = 42; no exception notification.
[INFO]  Injecting one operator fault; a Runtime task error is expected.
[INFO]  Fault synchronization returned ... (expected execution failure).
[INFO]  Process fault: device=0, stream=..., task=..., error=....
[INFO]  Binary fault: device=0, stream=..., task=..., error=....
[INFO]  Fault attributed to checked_increment; retired observer calls=0.
[INFO]  Run the 3_operator_fault_diagnosis sample successfully.
```
