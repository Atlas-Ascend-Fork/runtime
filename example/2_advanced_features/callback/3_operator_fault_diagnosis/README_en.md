# Locate an Execution Error in a Custom Operator

## Description

This sample shows how exception callbacks identify the Device, task, and kernel function responsible for a custom operator execution error. It is intended for developers debugging their own Ascend C operators.

The sample uses a simple operator named `checked_increment` that adds 1 to an integer. The run has three steps:

1. **Check normal computation**: Pass 41, verify that the result is 42, and check that no exception notification arrives.
2. **Simulate an execution error**: Enable the fault flag for the same operator so that it deliberately raises an error.
3. **Check the fault location**: Collect exception information from the application's process callback and the callback registered for the operator binary. Check that both identify the same Device, Stream, Task, and error code, then confirm that the failing kernel function is `checked_increment`.

The output shows the healthy result and the fault location reported by both callbacks. After the fault, the program checks this information, releases resources, and exits.

## Product Support

| Product | Supported |
| --- | --- |
| Atlas A2 series products | √ |
| Atlas A3 series products | √ |
| Ascend 950PR/Ascend 950DT | √ |


## Compile and Run

The sample deliberately executes one `trap` instruction to produce a Device task error. Run it on a dedicated test Device. Runtime error logs for this injected fault are expected. After checking the fault information, the sample releases resources and exits.

1. Install matching drivers, firmware, and CANN Toolkit. Enter the sample directory and configure the CANN path.

   ```bash
   cd ${git_clone_path}/example/2_advanced_features/callback/3_operator_fault_diagnosis
   export ASCEND_INSTALL_PATH=${install_root}/cann
   source "${ASCEND_INSTALL_PATH}/set_env.sh"
   ```

2. Use `npu-smi info` to confirm that the selected Device is a supported product listed above. The sample uses logical Device `0` among the visible devices; select a test device with `ASCEND_VISIBLE_DEVICES` if needed. Detect the actual chip model and Ascend C build directory:

   ```bash
   npu-smi info
   source ../../../set_sample_env.sh
   echo "${SOC_VERSION}"
   echo "${ASCENDC_CMAKE_DIR}"
   ```

   `SOC_VERSION` must match the physical chip, for example `Ascend910B1` for A2, `Ascend910_9362` for A3, or the corresponding A5 chip model. `ASCENDC_CMAKE_DIR` must contain both `ascendc.cmake` and `asc_modules/FindASC.cmake`, for example `${ASCEND_INSTALL_PATH}/compiler/tikcpp/ascendc_kernel_cmake`. Older toolchains without the native ASC CMake modules cannot build this sample.

3. Build and run:

   ```bash
   bash run.sh
   ```

   The script builds and executes `main` in `build/`, loading `operator_fault_kernel.o` from that directory. Each synchronization waits up to 30 seconds; callback collection waits up to 5 seconds after fault synchronization returns. Cleanup force-destroys the failed Stream, unloads the operator binary, frees memory, unregisters process callbacks, releases Device resources, and finalizes.

## CANN RUNTIME API

The key features and APIs used in this sample are:

- Process callback registration and removal: `aclrtExceptionInfoCallbackRegister` registers a callback to collect exceptions and a temporary callback to demonstrate removal. `aclrtExceptionInfoCallbackUnregister` removes the temporary callback before task submission and the collecting callback during cleanup. The temporary callback must never be invoked.
- Identifying the failing kernel function: `aclrtBinarySetExceptionCallback` registers an exception callback and user data for the loaded operator binary. `aclrtGetFuncHandleFromExceptionInfo` retrieves the failing kernel function handle from that callback’s exception information.
- Task correlation and error validation: `aclrtStreamGetId` and `aclrtGetThreadLastTaskId` identify the submitted task; `aclrtGetDeviceIdFromExceptionInfo`, `aclrtGetStreamIdFromExceptionInfo`, `aclrtGetTaskIdFromExceptionInfo`, and `aclrtGetErrorCodeFromExceptionInfo` read exception fields.
- Operator loading, execution, and unloading: `aclrtBinaryLoadFromFile`, `aclrtBinaryGetFunction`, `aclrtLaunchKernelWithHostArgs`, and `aclrtBinaryUnLoad`.
- Stream stop-on-failure and synchronization: `aclrtCreateStream`, `aclrtSetStreamFailureMode`, `aclrtSynchronizeStreamWithTimeout`, `aclrtDestroyStream`, and `aclrtDestroyStreamForce`.
- Healthy result validation and memory management: `aclrtMalloc`, `aclrtMemset`, `aclrtMemcpy`, and `aclrtFree`.
- Initialization and Device resource management: `aclInit`, `aclrtSetDevice`, `aclrtResetDeviceForce`, and `aclFinalize`.

Callbacks copy required exception values during the invocation without retaining Runtime-owned exception pointers or submitting tasks, synchronizing, or releasing resources. Unregistration does not wait for notifications already in flight. The sample keeps callback state and user data in static storage until process exit.

## Sample Output

`Healthy task verified` confirms that the healthy calculation produced 42. `Process fault` and `Binary fault` show information collected by the process callback and the operator binary callback. Their Device, Stream, Task, and error values must match. `Fault attributed to checked_increment` confirms that the kernel function also matches.

The program prints the final success message and exits with status 0 only after the expected task error, both callbacks, and cleanup pass validation. Successful synchronization of the faulting task, a timeout, missing callbacks, inconsistent information, or cleanup failure causes a nonzero exit.

Environment-dependent Stream IDs, Task IDs, and error codes are replaced with `...`; build output is omitted.

```text
[INFO]  Healthy task verified: 41 + 1 = 42; no exception notification.
[INFO]  Injecting one operator fault; a Runtime task error is expected.
[INFO]  Fault synchronization returned ... (expected execution failure).
[INFO]  Process fault: device=0, stream=..., task=..., error=....
[INFO]  Binary fault: device=0, stream=..., task=..., error=....
[INFO]  Fault attributed to checked_increment; retired observer calls=0.
[INFO]  Run the 3_operator_fault_diagnosis sample successfully.
```
