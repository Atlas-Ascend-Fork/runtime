# callback

本目录聚焦 Stream 回调、HostFunc 回调和异常回调能力。

## 样例列表

- [0_simple_callback](./0_simple_callback/README.md)：演示 Report 回调和 HostFunc 处理线程的注册与执行。
- [1_callback_hostfunc](./1_callback_hostfunc/README.md)：演示 Stream 上 HostFunc 回调的下发与执行顺序。
- [2_callback_exception](./2_callback_exception/README.md)：演示异常回调和 Runtime 错误信息查询。
- [3_operator_fault_diagnosis](./3_operator_fault_diagnosis/README.md)：让自定义算子先正常计算、再主动报错，通过异常回调找到出错任务和核函数。
