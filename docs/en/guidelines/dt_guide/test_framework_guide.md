# Test Framework Guide

> Back to [Runtime DT Case Development Guide](README.md)

Testing in the Runtime repository is mainly based on gtest, combined with gmock, mockcpp, common stubs, and module-specific stub/data to organize test cases. This guide introduces the capabilities of the existing test framework and helps you reuse existing facilities instead of reinventing the wheel.

## Test Base Class

Most test cases directly inherit `testing::Test` and perform common initialization and cleanup in `SetUp` / `TearDown`.

Common responsibilities include:

* Restoring the default mock behavior
* Creating and destroying simulators
* Setting and restoring the global chip type, device, and environment variables
* Verifying and clearing mock objects

If multiple test cases share the same initialization logic, extract a unified fixture to avoid duplicated code.

## Mock Frameworks

### gmock

gmock is suitable for scenarios with existing mock classes or API expectation verification. Common usages include:

* `EXPECT_CALL(...)`
* `Mock::VerifyAndClear(...)`

Typical scenarios:

* Tests of ACL-related APIs
* Scenarios where you need to verify the invocation count and arguments of a mock object

### mockcpp

mockcpp is suitable for replacing global functions, static functions, and member functions. It is widely used in the repository. Common APIs include:

* `MOCKER(...)`
* `MOCKER_CPP(...)`
* `MOCKER_CPP_VIRTUAL(...)`
* `GlobalMockObject::verify()`

Typical scenarios:

* Stubbing system APIs such as `dlopen` / `dlsym` / `access`
* Stubbing driver-, runtime-, and device-related functions
* Replacing internal call chains of singletons

## Common Stubs and Test Assets

### `tests/depends/`

`tests/depends/` provides common stubs that are reused across modules. Before you add a new test, check this directory first to see whether reusable capabilities already exist. The current main contents include:

* `ge/`
* `mmpa/`
* `profiling/`
* `runtime/`
* `slog/`
* `tdt/`
* `toolchain/`

### Module-Level `stub/`, `data/`, and `json/`

Many modules maintain dedicated test assets in their own test directories, for example:

* `tests/ut/msprof/st/stub/`
* `tests/ut/msprof/st/data/`
* `tests/ut/acl/json/`
* `tests/ut/runtime/runtime_c/stub/`

If a stub or data serves only one module, place it inside the module to avoid polluting the common directory.

## Simulators and Auxiliary Capabilities

Some STs/UTs use the ready-made simulators and data management capabilities in modules, for example:

* `SimulatorMgr()` creates/destroys the platform simulator
* `DataMgr()` initializes and verifies scenario data

These capabilities are usually coupled with module scenarios. When you add a test case, reuse the existing helpers first and do not reimplement a new set of simulation logic.

## Build Integration

After you add new test code, you usually need to modify the `CMakeLists.txt` of the corresponding module. Common integration methods include:

* Add the new file to `UT_FILES`
* Add the new directory to `add_subdirectory(...)`
* Add the dependent stubs, header files, and link libraries for the new executable target

If you add a module that can be run directly with `bash tests/build_ut.sh -u <target>`, also update the target mapping in `tests/build_ut.sh` accordingly.

## Coverage and Sanitizer

The unified entry point in the repository is `tests/build_ut.sh`:

```bash
# Coverage.
bash tests/build_ut.sh -c

# AddressSanitizer.
bash tests/build_ut.sh --asan -u runtime
```

If the new test creates a large number of temporary files or directories, run coverage or sanitizer locally as well to expose leakage and residual state problems as early as possible.
