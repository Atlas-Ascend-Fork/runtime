# EH0015 File\_Operation\_Error

## 错误信息

报错格式如下，占位符%s的含义依次为动态库名（或路径）、报错原因：

```text
Failed to load dynamic library %s. Reason: %s.
```

报错示例如下：

```text
Failed to load dynamic library libdatatransfer.so. Reason: /usr/local/Ascend/cann-9.2.0/lib64/libdatatransfer.so: undefined symbol: TdtHostInit.
```

## 解决方法

1. 使用正确的动态库路径。
2. 确保所需动态库已正确安装。
