# 寄存器初始化生成器 Host 回归

在仓库根目录使用 Python 3.8 或更新版本运行，仅依赖标准库：

```bash
python3 tests/host/test_register_init_short_pairs.py
```

测试通过 `process_reginfo` 读取实际的隔离 reginfo 文件，覆盖 AIC/AIV
高位调试地址行只有 2/3/4 个字段的场景。检查不完整地址对不会影响其余
8 个正常寄存器和 4 个有效调试寄存器，并保留缺少伴随行、空行、其他调试
寄存器名称及无效十六进制值的现有处理。测试结束后自动清理临时目录。

CLI 回归在独立临时目录中运行实际脚本，读取两种文件类型并检查生成的
C++ 文本和处理日志。这些测试验证 Host 解析与生成行为；不编译 Runtime
或生成的 C++ 片段，不执行设备寄存器采集。

此回归也已登记到 `runtime_api_stub_generator_ut`；可在已有 UT 构建目录中执行 `cmake --build <build-dir> --target runtime_api_stub_generator_ut`。
