# Runtime DT Case Development Guide

This guide targets UT/ST development in the Runtime repository. It focuses on where to place test cases, how to integrate them into the build, and the basic constraints to follow when you design test cases. This guide assumes that you already have a basic knowledge of gtest, so it does not cover test framework syntax in detail.

> This guide focuses on test case conventions. For compilation and execution, use `bash tests/build_ut.sh` first.

## Detailed Guidance

| Document | Content | Applicable Scenario |
|------|------|---------|
| [Test Framework Guide](test_framework_guide.md) | gtest, gmock/mockcpp, common stubs, module-specific stub/data, and build integration | Read when you construct inputs, create stubs, or organize test assets |
| [UT Case Development Guide](ut_case_development_guide.md) | UT design checklist, complete verification, global state restoration, and compatibility test suggestions | Read when you write or supplement UTs |

## Basic Knowledge

### When to Add DT Test Cases

Generally, you need to add DT test cases in the following two situations:

1. During the development of a new requirement, a new API, or a new platform branch, add UTs for the new behaviors and add STs when necessary.
2. When you fix an issue, add a corresponding regression test case if the issue can be stably reproduced by a test. The recommended workflow is as follows: first reproduce the issue with a UT/ST, then fix the code, and finally confirm that the regression test case passes stably.

### Runtime DT Test Project

The test project of the Runtime repository is located in the `tests/` directory. The core structure is as follows:

```yaml
tests
 - build_ut.sh: Entry for test build, execution, and coverage statistics
 - depends: Common stubs and dependency fakes
   - ge: Stubs related to dependent components
   - mmpa: Platform abstraction layer stubs
   - profiling: Profiling-related stubs
   - runtime: Stubs for runtime/drv APIs
   - slog: Log stubs
   - tdt: Stubs related to data transmission
   - toolchain: Stubs related to the toolchain
 - ut
   - acl: ACL API tests, including `testcase/` and `testcase_c/`
   - runtime: Runtime core and C API tests
   - adump: Dump-related UTs/STs
   - msprof: Profiling-related UTs/STs
   - platform: Platform capability UTs/STs
   - queue_schedule: Queue scheduling UTs/STs
   - aicpu_sched: AICPU scheduling UTs/STs
   - atrace: Trace-related tests
   - tsd: TSD-related tests
   - error_manager: Error management tests
   - mmpa: Platform abstraction layer tests
   - slog: Log module tests
```

The Runtime repository does not have a separate `tests/st` directory. STs are usually placed in the same `tests/ut/**` directory tree as the corresponding modules, commonly in `tests/ut/msprof/st`, `tests/ut/platform/st`, and `tests/ut/adump/st`.

### Common Execution Commands

```bash
# Build and run all tests.
bash tests/build_ut.sh -u

# Build and run a specified module.
bash tests/build_ut.sh -u runtime
bash tests/build_ut.sh -u acl
bash tests/build_ut.sh -u msprof

# Enable coverage.
bash tests/build_ut.sh -c

# Enable AddressSanitizer.
bash tests/build_ut.sh --asan -u runtime
```

The common targets currently supported by `tests/build_ut.sh` include `full`, `acl`, `runtime`, `runtime_c`, `platform`, `queue_schedule`, `aicpu_sched`, `slog`, `atrace`, `msprof`, `adump`, `tsd`, `error_manager`, and `mmpa`. To add a new top-level test target, update `ut_path_map` in `tests/build_ut.sh` accordingly.

## Adding New Test Case Files to the Build System

The Runtime test project uses CMake for the build. After you add a test case, check the following integration points at least:

1. Add the new file to the `CMakeLists.txt` of the corresponding module, for example, to `UT_FILES` or to the source file list of `add_executable(...)`.
2. If you add a test subdirectory, add `add_subdirectory(...)` to the parent `CMakeLists.txt`.
3. If you want to run the new module or submodule directly with `bash tests/build_ut.sh -u <target>`, update `ut_path_map` in `tests/build_ut.sh` accordingly.

Example:

```cmake
set(UT_FILES
    "acl_queue_unittest.cpp"
    "acl_new_feature_unittest.cpp"
)
```

## Test Case Conventions

### Rule 1: Prioritize Consistency With the Existing Naming Style of the Directory

The existing UT naming in the Runtime repository is not fully consistent. Common suffixes include:

* `*_unittest.cpp` / `*_unittest.cc`
* `*_utest.cpp` / `*_utest.cc`

For example:

* `tests/ut/acl/testcase/acl_queue_unittest.cpp`
* `tests/ut/runtime/runtime/test/rt_utest_api.cc`
* `tests/ut/tsd/tsdclient/test/package_process_config_utest.cpp`

When you add a new file, follow the principle of "**keeping the same style within the same directory**". Do not introduce a new suffix style into a directory that already has a clear naming convention.

For ST files, uniformly use `*_stest.cpp` / `*_stest.cc` and place them in the `st/` directory of the corresponding module or in a platform scenario directory, for example:

* `tests/ut/msprof/st/api/testcase/api_dc_stest.cpp`
* `tests/ut/msprof/st/msprofbin/test/running_mode_stest.cpp`

### Rule 2: One Test Case Verifies Only One Clear Scenario

For both UTs and STs, a test case should focus on one scenario and perform complete verification of that scenario. Do not chain multiple weakly related scenarios in one test case; otherwise, the cost of issue locating and subsequent maintenance increases.

### Rule 3: Test Case Names Should Express the Tested Object, Expected Behavior, and Trigger Scenario

The naming styles of historical test cases in the Runtime repository also vary, but new test cases should meet the following requirements at least:

* The name shows which API, class method, or feature the case tests
* The name shows whether the expected result is success, failure, or a certain state change
* The name shows the key scenario that triggers the behavior

If the same file already has a stable naming style, prioritize consistency with it.

### Rule 4: Perform Complete Verification Rather Than Checking Only the Return Value

In addition to the return value, verify the observable results directly related to the scenario, for example:

* Content of output parameters
* Member state changes
* Number of mock invocations and their arguments
* Files, directories, logs, callbacks, and side effects
* Whether the global state is restored

A test case that verifies only "success/failure of the return" is of limited value. Try to avoid such test cases.
