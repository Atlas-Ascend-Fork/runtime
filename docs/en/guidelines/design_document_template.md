# Introduction

## Purpose

Describe the purpose of this document and clarify the target readers. State that this document describes the software requirements and design of a requirement, feature, or API change in the Runtime repository.

## Scope

This section describes the content included in and excluded from the document. Clarify which modules, APIs, platforms, tests, and document synchronization work are within the scope of this design.

# Overall Description

This section describes general factors that affect the product and product requirements. It does not describe specific requirement details. Instead, it builds context for the subsequent specific requirements, design, and testing.

## Software Overview

### Project Introduction

Describe the background of this design. For example, state whether this requirement enhances existing Runtime capabilities, refactors a sub-module, extends public APIs, or adds capabilities for a new platform or new scenario.

### Product Environment Introduction

Describe the overall environment that consists of Runtime and other components, products, and platforms.

1. If this capability is independent and self-contained, state it here.
2. If this capability belongs to a larger system, do the following:

> A. Describe the responsibility boundaries of related components and identify API boundaries.
>
> B. Identify the main external APIs involved in this requirement, for example `aclrt*`, `rt*`, driver, toolchain, profiling, dump, and so on.
>
> C. Describe related hardware platforms, chip capabilities, the host machine environment, external dependencies, and device-side restrictions.

Use a block diagram to describe component relationships, call directions, and external APIs.

## Software Functions

Summarize the main functions that this requirement must implement. Provide only a high-level description here, and put detailed designs in subsequent sections. Organize the functions by functional domain, for example:

* ACL public APIs
* Runtime core capabilities (device/context/stream/event/notify/memory/model)
* Maintenance and test capabilities (profiling/dump/log)
* Toolchain or platform adaptation capabilities

## Design Constraints

Describe the items that restrict development choices, for example:

* Platform capability restrictions
* Public API/ABI compatibility requirements
* Directory boundary constraints
* Build macro constraints
* Performance, memory, log, and thread model restrictions

## Assumptions and Dependencies

Describe the upstream and downstream versions, driver capabilities, third-party components, public libraries, test environments, and document prerequisites that this iteration depends on.

# Feature 1 Requirement Analysis & Design

## Overall Introduction

## Functional Requirements

### Functional Requirement 1

> Use short words as the functional requirement name. Do not use "Functional Requirement (1)" as the function name.

1. Introduction

> List the functional requirements related to this feature one by one, including the expected behavior under normal flows, error input, invalid states, and invalid input. Requirements should be concise, complete, unambiguous, and verifiable. Mark "TBD" when information is uncertain.

2. Input

> This subsection should contain:
>
> A. Detailed descriptions of all input data, including source, quantity, unit, timing, range, precision, and tolerance.
>
> B. References to the API specification or API control document.

3. Processing

> This subsection should describe:
>
> A. Input validity validation.
>
> B. Key operation steps and event timing.
>
> C. Exception scenario handling, for example overflow, communication failure, driver return exceptions, resource allocation failures, and unsupported capabilities.
>
> D. Any input-to-output conversion method, state machine, or key algorithm.
>
> E. Validity checks on output results.

4. Output

> This subsection should contain:
>
> A. Detailed descriptions of all output data, return values, side effects, logs, files, callbacks, and state changes.
>
> B. References to the API specification or API control document.

### Functional Requirement 2

## Non-Functional Requirements

### Maintainability

### Testability

### Portability

### Reliability

### Platforming Requirements

Runtime must be compatible with multiple SoCs, multiple driver capabilities, and multiple runtime environments. Handle differences in common path design preferably through capability queries, configuration registration, and platform isolation directories. Do not directly hardcode platform branches in common logic.

### Feature Cross Analysis

This section directly lists the impact assessment of this requirement on the following typical domains. State at least "involved/not involved" and the reason:

* Public APIs of `include/external/acl/`
* Externally released header files in `pkg_inc/runtime/`
* Boundary between `src/runtime/api/` and `src/runtime/core|feature/`
* device/context/stream/event/notify/memory/model
* dump/profiling/log/toolchain
* Platform adaptation directories and driver interaction
* Test projects, documents, and samples

## Performance

### API Call Latency

*For requirements that involve public APIs or high-frequency internal APIs, you must evaluate the impact of new logic on API latency. Focus on identifying extra branches, locks, string processing, logs, and memory allocation in hot paths.*

### Memory and Resource Usage

*Evaluate the impact of new features on resource usage such as memory, stream, event, context, threads, and handles. In principle, describe the lifecycle, upper limit, and release timing of new resident resources.*

### Execution Performance

*All execution-state related code requires an evaluation of the impact on task submission, scheduling, synchronization, copy, and device execution paths. If the impact occurs on high-frequency paths, quantify it to the microsecond/nanosecond level as much as possible.*

### Maintainability and Log Overhead

*For changes related to profiling, dump, trace, and logs, evaluate whether they introduce extra collection overhead, I/O jitter, or massive logs.*

## API Design

### New/Modified API Description

*When adding or modifying APIs, clarify the API prototype, parameter constraints, return values, thread safety requirements, lifecycle requirements, and version compatibility policy.*

### API Check Items

| **Check Item** | **Sub Check Item** | **Whether Involved** |
|------------|--------------|--------------|
| **API Description** | Whether the API needs review; the review focuses on API compatibility, calling constraints, and resource lifecycles | |
| **API Description** | Whether supplementary material descriptions, samples, or migration instructions are required | |
| **API Description** | Whether the API document clarifies the API prototype, function, return values, and error codes | |
| **API Compatibility** | Whether modifications under `include/`, `include/external/acl/`, and `pkg_inc/runtime/` remain backward compatible | |
| **API Compatibility** | Whether the API signature has a breaking change | |
| **API Compatibility** | Whether deprecated APIs are marked instead of directly deleted | |
| **API Compatibility** | Whether the enum newly adds `XX_MAX` or affects multi-version matching compatibility | |
| **API Constraints** | Whether the API involves constraints such as calling sequence, thread context, device/context, and memory ownership | |
| **API Constraints** | Whether a clear error is reported when an API call does not meet the constraint conditions | |
| **Directory Specifications** | Whether content is mistakenly added to `pkg_inc/runtime/runtime` and whether it should be placed in `pkg_inc/runtime/rt_external*` or another external boundary | |
| **Document Synchronization** | Whether the corresponding documents in `docs/` are updated at the same time when `include/external/acl/acl_rt.h` is modified | |
| **Document Synchronization** | Whether `docs/zh/api_ref/25_data_types_and_operation_APIs.md` is updated at the same time when `include/external/acl/error_codes/rt_error_codes.h` is modified | |
| **Test** | Whether separate UT/ST/compatibility cases need to be added | |

## Software Design

### Key Data Structures

### Key Technologies/Algorithms

### Flow Design

### Modifications to Sub-Modules

*If the adjustment involves the main flow of a sub-module, directory boundaries, or calling directions, clearly state the changes in responsibility boundaries and the affected modules.*

### Error Handling

#### System Errors

*Describe how to handle system-level errors such as memory allocation failures, driver failures, resource creation failures, thread creation failures, and file/directory failures.*

#### API Errors

*Describe the error codes, error messages, and propagation policy that are exposed to external entities.*

### Supplementary Runtime Design Check Items

| **Check Item** | **Check Item Description** | **Whether Involved** |
|------------|----------------|--------------|
| **Architecture Boundary** | Non-`api` directories in `src/runtime` should not call methods in the `api` directory; for example, the `feature` directory should not access `Api::Instance` | |
| **Compilation Macro** | The `src/runtime` directory only allows `STATIC_RT_LIB`, `RUNTIME_API`, `CFG_DEV_PLATFORM_PC`, and compiler built-in macros; do not add other compilation macros | |
| **External Input Validation** | Whether validation policies are defined for user API parameters, driver return values, configuration files, environment variables, and external file paths | |
| **Resource Lifecycle** | When adding memory, handles, threads, callbacks, caches, or singleton resources, whether the lifecycle, release path, and exception reclamation policy are clarified | |
| **Cross-SO Destruction Risk** | Whether static/global objects make cross-SO calls, release cross-SO objects, or depend on the unloading order during destruction | |
| **Hot Path Logs** | Whether the performance impact of new logs, string concatenation, and maintainability instrumentation in hot paths is evaluated | |

## Security Check

### Coding Guidelines

For details, see [coding-guidelines.md](coding-guidelines.md)

### Design Check Items

| **Check Item** | **Check Item Description** | **Whether Involved** |
|------------|----------------|--------------|
| **Resource Lifecycle Management** | Resources with overly long lifecycles may cause insufficient resources, slow responses, and system crashes; clarify whether a resource is process-level, device-level, context-level, or call-level | |
| **Thread Creation** | Whether a new thread needs to copy context information such as ThreadLocalContext and ErrorContext; whether a thread name needs to be set | |
| **Global State Restoration** | Whether the design modifies the SoC type, device, environment variables, singleton states, or static caches; if yes, how the test and exception paths restore the states | |
| **External Data Usage** | Whether external input may be used as an array index, length, offset, memory allocation size, or enum value in critical logic | |
| **Logs and Sensitive Information** | Whether risks exist such as sensitive information printing, improper error log levels, or excessive hot path logs | |

## Compatibility Check

Focus on the following compatibility problems:

* Whether old-version applications or old APIs still work on the new-version Runtime
* Whether the external boundaries of `include/` and `pkg_inc/` introduce ABI/API incompatibility
* Whether newly added enum values, struct fields, and reserved parameters affect old logic after being enabled
* Whether documents, samples, and tests cover compatibility scenarios

## Document Synchronization

If this design involves public API changes, error code changes, or user-visible behavior changes, clarify the list of documents to be updated at the same time, for example:

* `docs/zh/api_ref/`
* `docs/zh/dev_guide/`
* `example/`
* Migration instructions, FAQ, and release notes

## DT Design

### Test Boundary

*Test entry (which API or component the test is based on), test exit (which data validations are performed), stub modules, dependent environments, and cleanup scope.*

### Test Design

*Describe which types of cases need to be designed, and export them to the case list. Case types generally include UT and ST, and when necessary include compatibility tests, performance tests, and special regression tests.*

| **Test Category** | **Key Test Item** | **Test Method** | **Case Type** |
|--------------|----------------|--------------|--------------|
| **Function** | | | |
| **Exception Handling** | | | |
| **Performance** | | | |
| **Compatibility** | | | |
| **Resources and Leaks** | | | |
| **Feature Cross** | | | |

### Test Framework Design

### Supplementary Test Implementation Check Items

| **Check Item** | **Check Item Description** | **Whether Involved** |
|------------|----------------|--------------|
| **Assertion Completeness** | Each test case must have `EXPECT`/`ASSERT` assertions to verify results; do not only call APIs without validation | |
| **Mock Cleanup** | Whether each test class calls `verify` or `reset` on mock objects in `TearDown` to ensure test isolation | |
| **Private Member Access** | Whether unnecessary use of `#define private public` / `#define protected public` is avoided | |
| **SetChipType** | Whether direct calls to `SetChipType` in UT are minimized, and whether restoration logic exists if the call is required | |
| **Pointer Member Restoration** | If a test modifies pointer members, global pointers, or singleton states of a class, whether the original values are restored on exit | |
