# UT Coding Guidelines

This document defines the mandatory specifications for UT code in the Runtime repository. It supplements the methodology-oriented and design-oriented content in `dt_guide/ut_case_development_guide.md`.

## 1. Assertion Specifications

### Rule 1: Each Test Case Must Have Valid Assertions

- Each test case must contain at least one valid `EXPECT` or `ASSERT` assertion.
- Test code that only calls APIs without validating results is forbidden.

### Rule 2: Assertions Must Cover Key Observable Results

- In addition to return values, validate output parameters, state changes, side effects, callbacks, and file or directory results that are directly related to the scenario.
- For failure scenarios, validate error codes, error states, or key protection behaviors instead of only asserting "execution completed".

## 2. Mock and Global State Specifications

### Rule 3: Call `verify` or `reset` on Mock Objects When a Test Exits

- Each test class should complete mock cleanup in `TearDown`, `TearDownTestCase`, or an equivalent finalization point.
- Do not allow mock states to leak into subsequent cases.

### Rule 4: Restore Global States After Modification

- If a test modifies the SoC type, device, environment variables, singleton states, static caches, global pointers, or member pointers, restore the original values on exit.
- Test code must not rely on other tests to set a global state first.

## 3. Test Isolation Specifications

### Rule 5: Test Cases Must Not Depend on Each Other

- Each test must independently construct inputs, directories, configurations, and contexts.
- Do not rely on the execution order. Do not assume that a previous test has created temporary files, directories, or registered states.

### Rule 6: Clean Up Temporary Files and Directories

- When you use `/tmp`, relative path directories, or temporary files, cleanup logic is required.
- Path names should contain module or case identifiers to prevent conflicts with other cases.

## 4. Maintainability Specifications

### Rule 7: Minimize Direct Access to Private Members

- Prefer public APIs to validate behavior.
- Use `#define private public` or `#define protected public` only when no reasonable alternative exists.

### Rule 8: Minimize Direct Calls to `SetChipType` in UT

- If the call is required, state the reason at the same time and restore the state when the test exits.

### Rule 9: Keep Naming and Directory Styles Consistent

- The naming of new test files should follow the existing style of the containing directory.
- Test class names, case names, and auxiliary file names should express the object under test, the scenario, and the expected behavior.
