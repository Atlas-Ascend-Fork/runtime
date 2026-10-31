# EH0015 File\_Operation\_Error

## Symptom

The following is error format. The meanings of the placeholders %s in sequence are: dynamic library name (or path), error cause.

```text
Failed to load dynamic library %s. Reason: %s.
```

Error examples:

```text
Failed to load dynamic library libdatatransfer.so. Reason: /usr/local/Ascend/cann-9.2.0/lib64/libdatatransfer.so: undefined symbol: TdtHostInit.
```

## Solution

1. Use the correct dynamic library path.
2. Ensure that the required dynamic library has been correctly installed.
