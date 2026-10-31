# Coding Guidelines

This document defines the unified coding guidelines that you must follow when implementing code in the Runtime repository.

Document structure:

- `1. General C/C++ Coding Guidelines` applies to all C/C++ code in the Runtime repository, including source code and UT code.
- `2. Runtime Restrictive Guidelines` mainly applies to `src/`, `include/`, `pkg_inc/`, `cmake/`, and other non-test code. When you review or write UT code, refer to this section only when the related scenarios are actually involved.

## 1. General C/C++ Coding Guidelines

### Rule 1: Do Not Hardcode Sensitive Information or Use Forbidden Sensitive Words

- Do not hardcode plaintext passwords, keys, or other high-sensitivity data in source code.
- Thoroughly clean up obsolete accounts, passwords, and sensitive configurations of unknown purpose left over from history.
- Avoid large arrays of unclear purpose, vague hidden data definitions, and hidden data definitions with poor readability. Reviewers may suspect them as backdoor implementations.
- If public network IP addresses, domain names, email addresses, or misleading sensitive words are hardcoded in code or configurations, you must be able to justify their legitimate purpose. Suspicious public network addresses pointing to China are strictly forbidden.

### Rule 2: Ensure a Legal Access Range When External Data Is Used as an Array Index or Pointer Offset

- If array indexes, memory offsets, lengths, or capacities are directly controlled by external input, perform strict range validation first to prevent out-of-bounds access.

### Rule 3: Strictly Check Integer Operations to Ensure No Overflow, Reversal, or Division by 0

- If an integer operation result participates in memory allocation, offset computation, loop boundaries, or copy lengths, evaluate the risks of overflow, reversal, truncation, and division by zero.

### Rule 4: Keep Resource Management and Lifecycles Clear, and Acquire and Release Resources in Pairs

- Release file handles, memory, and handles such as device, driver, context, stream, event, and notify promptly after their lifecycles end.
- Do not omit cleanup actions in exception branches or early-return paths.
- Immediately assign a definite new value after a resource is released to prevent dangling pointers and double release.
- Acquire and release resources such as memory, locks, and handles in pairs. Prefer RAII to manage resource lifecycles.

### Rule 5: Check the Size Before Memory Allocation and Verify Whether the Allocation Succeeds

- The allocation size may come from external input. Check its validity, and do not allocate memory of length 0.
- For an external allocator, verify whether both the returned struct pointer and the `data` pointer inside the struct are valid.
- After memory allocation, evaluate whether initialization is required to avoid reading uninitialized memory.

### Rule 6: Validate External Input, Null Pointers, Array Indexes, and Loop Boundaries First

- Complete validity checks on external input such as user parameters, driver return values, configuration files, and environment variables before the input enters critical logic.
- Confirm that a pointer is valid before dereferencing it.
- Keep array indexes, lengths, and loop boundaries within legal ranges.

### Rule 7: Handle Errors Completely, and Do Not Swallow Errors

- Propagate error return values correctly along the call chain. Do not silently swallow errors.
- Returned error codes must be semantically accurate.
- Release the resources already allocated on an error path at the same time.
- Use error handling macros correctly. Do not log an error without finalizing the error reporting, and do not return directly without context.

### Rule 8: Ensure That Buffers, Memory Operations, and Object Lifecycles Meet Basic Security Constraints

- Avoid out-of-bounds access to arrays or buffers.
- Strictly pair `new/delete`, `malloc/free`, and `new[]/delete[]`. Do not mix them.
- Check for null after using `new(std::nothrow)`. Do not check for `nullptr` again after using normal `new`.
- Do not return the address of stack space.
- Before releasing an object, define the handling policy for the member pointers inside the object to prevent double release or dangling references.

### Rule 9: Explicitly Ensure Thread Safety in Concurrent Scenarios

- Define an explicit protection policy for shared data in multi-thread scenarios to prevent race conditions and visibility problems.
- Do not nest normal locks arbitrarily to avoid deadlock risks.
- When thread context switches, asynchronous tasks, or callbacks are involved, clarify the timing relationships and resource validity periods.

### Rule 10: Do Not Write Code That Depends on Expression Evaluation Order or Implicit Precedence

- Code such as `func(a++, a)` depends on an unspecified evaluation order and is undefined behavior. Avoid it.
- Use parentheses in complex expressions to clarify operation precedence. Do not rely on the default precedence order.

### Rule 11: Keep Code Style and Commit Content Clean and Consistent

- Changed code must comply with the `.clang-format` configuration of the repository.
- Names must follow project conventions. Use upper camel case for function names, and private methods allow a trailing underscore. Use lower camel case for variable names. Use uppercase words separated by underscores for constants and macros. Use upper camel case for class names.
- New files must contain the CANN Open Software License copyright header.
- The include order must follow project conventions.
- Do not leave debug code, commented-out code, unused includes, or unused variables in a commit.
- New file permissions must be reasonable. Use 644 for source code and 755 for executable scripts.

## 2. Runtime Restrictive Guidelines

### Rule 12: Strictly Validate Reserved Parameters of Public APIs to Prevent Compatibility Problems When the Parameters Are Enabled in Later Versions

- Force users to pass an invalid value for a reserved parameter. Otherwise, compatibility problems are easily introduced when the parameter is enabled later.
- The invalid value of a numeric reserved parameter is generally `0`.
- The invalid value of a pointer reserved parameter is generally `nullptr`.

### Rule 13: Prefer `size_t` for Return Values or Parameters That Express Memory Lengths in Public APIs

- Prefer `size_t` for semantics such as memory lengths, buffer sizes, and byte counts. This preference prevents insufficient expression ranges of 32-bit lengths.

### Rule 14: Strictly Ensure API and ABI Compatibility When Modifying Public APIs

- Strictly evaluate API/ABI compatibility for modifications to `include/`, `include/external/acl/`, and the boundaries of externally released header files.
- Do not use `std::string` as an ABI boundary type in public APIs of external header files. Use a compatible alternative in the repository instead.
- Consider reserved fields and backward compatibility when you add or modify structs.
- Mark deprecated APIs for compatibility first instead of deleting them directly.

### Rule 15: Do Not Hardcode Chip, Platform, or Driver Capability Branches in Common Paths

- Handle differences in common logic preferably through capability queries, configuration registration, or platform isolation directories.
- Converge logic that must distinguish platforms in `config/`, platform subdirectories, or a clear capability adaptation layer.

### Rule 16: Do Not Add EVENT/TRACE Prints Arbitrarily in Load/Execution Hot Paths

- Massive logs in hot paths introduce obvious performance jitter and I/O pressure.
- Do not add EVENT/TRACE level logs that are enabled by default in load/execution hot paths.
- You can add DEBUG/INFO logs that are disabled by default, but evaluate the switch policy and string overhead.
- Use ERROR logs only for real exceptions, not for normal branches.

### Rule 17: Confirm Resource Lifecycle Constraints in Advance When Calling APIs Provided by Other Components That Require Runtime to Pass In Resources

- During both design and coding, clarify whether a cross-component API holds the passed-in pointer, when it reuses the pointer, and when it releases it.

### Rule 18: Do Not Rely on Unordered Container Traversal Results in Order-Sensitive Logic

- If the container traversal order affects the order of tasks, events, notifications, callback registration, or resource initialization, do not directly rely on traversal results of unordered containers such as `std::unordered_map`.
- Prefer ordered containers or explicit sorting when a stable order is required.
- Do not use in-process address values as the order basis.

### Rule 19: Do Not Implement the Singleton Pattern Inline in Header Files

- Header file inline singletons may cause multiple instances, destruction order, and crash problems in multi-compilation-unit, dynamic library, and `dlopen` scenarios.

### Rule 20: Do Not Add Undisclosed Public API Boundaries

- Place new public APIs only in clear public boundary header files. Do not expose capabilities through internal header files or internal symbols.

### Rule 21: Do Not Make Cross-SO Function Calls in Destructors of Static or Global Objects

- The destruction order across dynamic libraries is unpredictable. It can easily cause dangling references, abnormal termination, and crashes.
- Typical risks include the following: the depended-on SO has been unloaded; the `shared_ptr` destruction triggers a virtual destructor, but the SO containing the actual type is invalid; and other threads still access static objects during program exit.
- The recommended practice is to put cleanup work in an explicit `Finalize()` API or an equivalent API, complete cleanup at runtime, and keep the destructor empty or recycle only local objects.

### Rule 22: Keep Implementation Logic Consistent with the Design and API Constraints

- Before coding, clarify the design intent, API constraints, and scenario expectations of the change.
- Do not omit branches, boundary conditions, or exception paths in the implementation.
- Keep the handling of normal flows, exception flows, and boundary scenarios consistent.

### Rule 23: Ensure Reasonable Log Levels, Content, and Hot Path Overhead When Writing Logs

- Use `RT_LOG_ERROR` only for unrecoverable errors, `RT_LOG_WARNING` for function degradation or non-fatal exceptions, `RT_LOG_INFO` for key operation nodes, and `RT_LOG_DEBUG` for debugging information.
- Log content must contain sufficient context and must not print sensitive information.
- Format strings must match parameter types.
- Do not hardcode function names in log content, and do not include English spelling errors.
- Do not introduce high-frequency logs in hot paths.
- Use in-project error log macros correctly, for example `COND_RETURN_ERROR_MSG_INNER` and `RecordErrorLog`.
- Use Arabic numerals consistently for English words that represent numeric values in logs and error messages: replace the standalone word `zero` with `0` (for example, `count is zero` → `count is 0` and `greater than zero` → `greater than 0`); do not replace hyphenated compound words (`zero-size`, `non-zero`, `divide-by-zero`, `zero-copy`) or technical terms (`zero copy`).

### Rule 24: Simultaneously Meet Compatibility Requirements When Modifying Public APIs

- When you modify header files in the `include/` directory, design the change according to backward compatibility principles.
- Public API function signatures must not have breaking changes unless the change has been explicitly accepted and the migration design is complete.
- Deprecate APIs through markers instead of deleting them directly.
- Do not arbitrarily introduce `XX_MAX` in enum definitions or affect multi-version matching compatibility.
- Do not mistakenly add content to `pkg_inc/runtime/runtime`. If addition is required, first confirm whether the content should be placed at another public boundary.

### Rule 25: Simultaneously Update Documents When Modifying Public APIs and Error Codes

- When you modify `include/external/acl/acl_rt.h`, update the corresponding `docs/` documents in the same change.
- When you modify `include/external/acl/error_codes/rt_error_codes.h`, update `docs/zh/api_ref/25_data_types_and_operation_APIs.md` in the same change.

### Rule 26: Follow the Existing Software Architecture and Build Boundaries During Implementation

- Non-`api` directories in `src/runtime` should not call methods in the `api` directory. For example, the `feature` directory should not access `Api::Instance`.
- Keep the existing directory boundaries, platform isolation boundaries, and component responsibility boundaries clear when you write the implementation.
- The `src/runtime` directory only allows `STATIC_RT_LIB`, `RUNTIME_API`, `CFG_DEV_PLATFORM_PC`, and compiler built-in macros. Do not add other compilation macros.
