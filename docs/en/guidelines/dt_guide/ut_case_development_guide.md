# UT Case Development Guide

> Back to [Runtime DT Case Development Guide](README.md)

The test scope of a UT is usually one file, one class, or a set of functions with clear boundaries. A UT focuses on isolating the tested object and verifying its externally observable behavior, instead of verifying all modules along the entire chain.

## UT Case Design Checklist

When you design test points for an API, check the following items first:

* External input verification
  * Null pointers
  * Invalid enumeration values
  * Out-of-bound length, capacity, and indexes
  * Handles or states that do not meet the preconditions
* Boundary values
  * Empty containers, zero length, and the minimum/maximum legal values
  * Single-element and multi-element scenarios
* Resource lifecycle
  * Whether allocation and release are paired
  * Whether the failure path has leakage
  * Whether repeated creation and repeated release are safe
* Global state and singletons
  * Global state switches such as `rtSetSocVersion`, `SetChipType`, and `rtSetDevice`
  * Whether environment variables, configuration switches, and static caches need to be restored
* Platform/chip branches
  * Whether the same API has branch behaviors on different SoCs and with different driver capabilities
* Callbacks and side effects
  * Whether callbacks are registered/triggered
  * Whether files, directories, logs, and statistics are generated correctly

If a check item is irrelevant to the current API, you do not need to force a test case for it.

## How to Verify

### Perform Complete Verification

A UT case should completely verify the call results according to the design. Common verification points include:

* Whether the return value or error code is accurate
* Whether output parameters are filled in correctly
* Whether the state of the tested object changes as expected
* Whether the mock is invoked with correct arguments and whether the invocation count meets the expectation
* Whether the cleanup logic on the failure path is executed

A common problem is "verifying only the return code but not the side effects". Such test cases hardly prevent behavior regressions. Avoid them.

### Avoid Duplicate Verification

Perform the same type of verification in only one test case that best fits the scenario. Too much duplicate verification causes many invalid failures after subsequent changes and reduces the maintainability of test cases.

## Common Notes in the Runtime Repository

### 1. Mock and Global State Must Be Finalized in TearDown

Many test cases in the Runtime repository depend on gmock or mockcpp. Regardless of the framework you use, complete verification and cleanup at the end of the test to avoid polluting subsequent test cases.

The common patterns are as follows:

```c++
class QueueTest : public testing::Test {
 protected:
  void SetUp() override {
    MockFunctionTest::aclStubInstance().ResetToDefaultMock();
  }

  void TearDown() override {
    Mock::VerifyAndClear((void *)(&MockFunctionTest::aclStubInstance()));
  }
};
```

Alternatively:

```c++
class PackageProcessConfigTest : public testing::Test {
 protected:
  void TearDown() override {
    GlobalMockObject::verify();
  }
};
```

If the test changes the chip type, device, environment variables, static flags, or singleton internal states during execution, restore them in `TearDown` / `TearDownTestCase` as well.

### 2. Access Private Members With Caution

The existing code in the repository contains the practice of `#define private public` / `#define protected public`, but this is only a supplementary means in restricted scenarios and should not be the default solution.

The recommended priority order is as follows:

1. Verify the behaviors exposed by public APIs first
2. If you must observe internal states, reuse existing helpers, stubs, or accessors first
3. Use `#define private public` temporarily only when no better solution exists

### 3. Ensure Isolation and Cleanup for File System Scenarios

Many Runtime tests read from and write to `/tmp`, relative path directories, or temporary files. When you add such test cases:

* Include module or test case characteristics in path names to avoid conflicts with other test cases
* Clean up temporary files and directories after the test completes
* Do not depend on other test cases to pre-create directories or files

### 4. Add Corresponding Tests for Compatibility Changes

If you modify ACL external structs, enumerations, constants, API signatures, or ABI-related content, check whether you need to add or update compatibility tests at the same time, for example:

* `tests/ut/acl/testcase/compatibility/`
* Existing ABI/API regression test cases of the corresponding module

## Discouraged UT Designs

The following types of test cases require caution:

* Verifying only "call success/failure" without verifying any result
* Chaining multiple weakly related scenarios in one test case
* Forcing tests of unrealistic exception combinations for coverage
* Depending on residual states left by the previous test case

If a scenario crosses module boundaries and requires a simulator, a device environment, or a complete process, it is usually more suitable as an ST instead of being piled up in UTs.
