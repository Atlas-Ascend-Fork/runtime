# Error Message Rectification Principles

This document summarizes the overall principles for Runtime/ACL Error Message rectification. It is used to determine general issues such as the rectification boundary, user errors versus internal errors, parameter sources, the first occurrence site, defensive programming, duplicate structured reporting, and printing formats. For error codes, macro selection, and message templates, refer to the dedicated specifications in the same directory.

## Core Principles

The goal of Error Message rectification is to improve user readability and fault location efficiency:

- User errors guide users to achieve closed-loop self-resolution. The message should state the parameter, actual value, expected value, or a clear reason.
- Internal errors precisely locate the internal failure point. The message should state the function, object, return code, or key context.
- When you analyze a call site, you must read the context and understand the business scenario and trigger cause of the error. Do not mechanically apply rules.
- The core criteria for error classification are the error trigger source and whether the user needs, can understand, and can handle the error.

## Rectification Boundary

Rectification only handles structured error reporting and its necessary macro/error code/message matching. It does not change business behavior.

Allowed rectification:

- Error information of `RT_LOG_OUTER_MSG_IMPL`, `RT_LOG_INNER_MSG`, and their wrapper chains in Runtime.
- Error information that directly uses `REPORT_INPUT_ERROR` and `REPORT_INNER_ERROR` in Runtime.
- Error information of `ReportInputError`, `ReportInnerError`, and `ACL_LOG_INNER_ERROR` in ACL.
- Structured error reporting points with obviously unreasonable error code selection or macro usage.

Prohibited items:

- Do not modify return values. For example, keep `RT_ERROR_INVALID_PARAM` and `ACL_ERROR_INVALID_PARAM` unchanged.
- Do not modify condition checks, flow control, or cleanup logic.
- Do not modify normal log levels. For example, do not change `ERROR` to `WARN` or `DEBUG`.
- Do not mechanically convert normal logs into structured reports.
- Do not replace wrapper macros with low-level macros for message rectification. When the wrapper macro is correct, prefer changing only the macro parameters or the message.

Usually not rectified:

- Normal logs of Runtime, such as `RT_LOG_ERROR`, `RT_LOG_DEBUG`, `RT_LOG_INFO`, and `RT_LOG_WARNING`.
- Normal logs of ACL, such as `ACL_LOG_ERROR`, `ACL_LOG_DEBUG`, `ACL_LOG_INFO`, and `ACL_LOG_WARN`.
- Logs used only for internal diagnosis in defensive programming.

## User Errors and Internal Errors

The core question for distinguishing user errors from internal errors is whether the user can achieve closed-loop self-resolution by modifying parameters, the environment, or the calling method.

User errors:

- The error is triggered by a user-passed parameter, user configuration, user calling sequence, or a user-controllable resource request.
- The user can resolve the problem by adjusting their own behavior based on the documentation or error information.
- Typical scenarios include invalid parameters, null pointer parameters, invalid paths, unsupported features, unsupported systems or devices, incorrect API calling sequences, and insufficient resources.
- Runtime uses user-type EE error codes and reports them through user error macros/APIs. ACL uses EH error codes and reports them through `ReportInputError`.

Internal errors:

- The error is triggered by a Runtime/ACL internal state, internal variable, or internal logic exception.
- The user cannot directly resolve the error by modifying API parameters or the calling method. Technical support or internal fault location is usually required.
- Typical scenarios include internal state exceptions, internal buffer operation failures, and defensive scenarios that theoretically should not occur.
- Runtime internal errors mainly use `EE9999` or normal logs only.

Quick judgment:

1. Whether the error parameter comes from user input or user configuration.
2. Whether the user can resolve the error by modifying their own parameters, environment, or calling method.
3. Whether the error information can guide the user to achieve closed-loop self-resolution.

If the answer to any question is "Yes", the error is usually handled as a user error. If all answers are "No", the error is handled as an internal error.

Examples:

```cpp
// User error: priority comes from an external API input parameter. The user can modify the calling parameter to achieve closed-loop self-resolution.
COND_RETURN_AND_MSG_OUTER_WITH_PARAM(priority > 2, RT_ERROR_INVALID_PARAM,
    priority, "[0, 2]");

// Internal error: internalState is a Runtime internal state. The user cannot directly resolve the problem by modifying API parameters.
COND_RETURN_AND_MSG_INNER(internalState == nullptr, RT_ERROR_INTERNAL_ERROR,
    "Internal error in %s: state is null", __func__);
```

## Parameter Source Determination

The parameter source is more important than the function name. The same system call failure may be classified differently due to different parameter sources.

- Parameters of APIs in public API header files are regarded as user parameters.
- Formal parameters in the ACL Impl layer that are directly forwarded from public APIs are regarded as user parameters.
- Formal parameters of private functions inside Impl or Runtime require call chain tracing. Parameters from public APIs are handled as user parameters, and parameters from internal variables are handled as internal parameters.
- Temporary variables, member variables, and internal state objects defined inside a function are usually handled as internal parameters or internal states.
- When a system call or secure function involves both user parameters and internal parameters, the failure is usually handled as a user error as long as a user parameter can trigger it.

Do not determine the error category only by function names such as `memcpy_s`, `malloc`, and driver APIs. Determine it based on the parameter source, calling layer, and user controllability.

## First Occurrence Site Principle

The first occurrence site is the initial position where the error occurs, that is, the direct error source.

The first occurrence site usually has the following characteristics:

- The position where the direct call fails or the exception condition first becomes true.
- The error is not simply returned from a lower-layer function.
- The current context knows the failed object, parameters, return code, and reason best.

Handling principles:

- Exception: On paths where aclrt/rt external API functions return error codes, the entry function serves as the user-visible error reporting boundary. The first occurrence site principle and the duplicate structured reporting deduplication principle do not apply. Even if a lower layer has already reported ErrMsg for the same error, the entry function still needs to report ErrMsg again to ensure that the external API has API-level error information.
- Except for the preceding exception scenarios, the error source should print logs sufficient for fault location. In principle, the source should also report ErrMsg when returning an error code.
- If the current function only receives the error code returned by a lower layer and the lower layer has already reported the same error, the current function only needs to return the error code and print normal logs as needed.
- In a multi-layer call chain, the same error is reported in a structured way only at the most appropriate first occurrence site.
- The source that reports an internal error also needs to retain locatable context, avoiding printing only generalized failure information at the outer layer.

Examples:

```cpp
// First occurrence site: malloc directly fails. The current context knows the size and return result best.
void *ptr = malloc(size);
if (ptr == nullptr) {
    RT_LOG_ERROR("Failed to allocate %zu bytes memory.", size);
    COND_PROC_RETURN_AND_MSG_ALLOC_FAILED(ptr == nullptr, RT_ERROR_MEMORY_ALLOCATION,
        (void)0, std::to_string(size));
}

// Not the first occurrence site: the error is returned from a lower layer, and the lower layer has already reported the same error.
rtError_t ret = AllocateMemory(size, &ptr);
if (ret != RT_SUCCESS) {
    RT_LOG_ERROR("AllocateMemory failed with error %d.", ret);
    return ret;
}
```

## Defensive Programming

Defensive programming refers to exception scenarios that theoretically should not occur. Usually, the upper layer has already performed validation, or internal conventions guarantee that the condition will not be true.

Determination criteria:

- The upstream function has already validated and intercepted the error.
- Conventions between internal modules guarantee that the parameters or states are valid.
- The code logic guarantees that the condition theoretically will not be true.
- The check condition is closer to an internal assertion or fallback protection.

Handling principles:

- In defensive programming scenarios, only print normal logs and do not report structured errors.
- Do not package defensive checks as user errors.
- If the defensive check is actually located at a user-visible entry, or user input can directly trigger it, do not handle it as a defensive scenario. Report it as a user error.

Examples:

```cpp
// The upper-layer function has validated and guaranteed that stream != nullptr.
rtError_t ProcessStreamInternal(rtStream_t stream) {
    if (stream == nullptr) {
        // Defensive programming: This theoretically should not occur. Keep only the normal log.
        RT_LOG_ERROR("Unexpected null stream in internal function %s.", __func__);
        return RT_ERROR_INTERNAL_ERROR;
    }
    // ... Business logic
    return RT_SUCCESS;
}

// External entry: User-passed nullptr can directly trigger the error. ErrMsg reporting is required.
rtError_t rtProcessStream(rtStream_t stream) {
    NULL_PTR_RETURN_MSG_OUTER(stream, RT_ERROR_INVALID_PARAM);
    return ProcessStreamInternal(stream);
}
```

## Duplicate Structured Reporting

Except for the aclrt/rt external API entry exception, the same error should not be structurally reported multiple times in the call chain.

Check method:

1. Locate the current structured reporting point.
2. Trace the upper-layer calls of the current function and the lower-layer return paths.
3. Confirm whether the same error has already been reported at a position closer to the source.
4. Except for the aclrt/rt external API entry exception, if the error has already been reported, the current call site only returns the error code and prints normal logs as needed.

Determination principles:

- The aclrt/rt external API entry exception is handled according to the exception clause in the "First Occurrence Site Principle" section.
- When the upper layer has already reported the same error, the current function does not report it again.
- When the lower layer has already reported the same error, the upper layer does not package it again as a new structured error.
- Different error sources or different failure branches should each have ErrMsg. Do not report again on paths where the lower layer has already reported. For paths where reporting is missing, the upper layer can add the report.
- Completely identical structured messages are forbidden in the same ErrMsg output.
- Messages with different error codes or wording that express the same failure fact without valid information increment are essentially identical and are also forbidden.
- Remove redundant ErrMsg from the call stack as much as possible. When a middle layer only expresses "call failure" or repeats the lower-layer root cause, delete the middle-layer report.
- When the first error point has incomplete information but the acl/rt API layer can supplement the calling scenario or additional fault location information, keep the first error point and API layer reports and delete the redundant middle-layer reports.
- Keep a middle layer only when it provides unique information that neither the first error point nor the API layer can reasonably express, and it must not be identical or essentially identical to other layers.
- Before deleting or migrating a report, confirm that each actually reachable error path that should be structurally reported still has an appropriate ErrMsg, and that the return code, cleanup sequence, and other business logic are not changed.
- When the current function directly produces an error and the lower layer has not reported it, the current function reports the error as the first occurrence site.
- When the driver API or low-level module has completed internal processing, for example, when driver memory-related errors are handled by existing dedicated methods such as `DRV_MALLOC_ERROR_PROCESS` or `DRV_ERROR_PROCESS`, the external caller avoids duplicate structured reporting.
- Normal `RT_LOG_*` logs do not count as duplicate structured reporting. Do not rely on ErrorManager container deduplication to replace the preceding checks.

Examples:

```cpp
// First occurrence site: The low-level function directly detects the malloc failure and reports it.
rtError_t AllocateMemoryInternal(size_t size, void **ptr) {
    *ptr = malloc(size);
    if (*ptr == nullptr) {
        COND_PROC_RETURN_AND_MSG_ALLOC_FAILED(*ptr == nullptr, RT_ERROR_MEMORY_ALLOCATION,
            (void)0, std::to_string(size));
    }
    return RT_SUCCESS;
}

// Middle layer: When the lower layer has already reported the same error, do not report it in a structured way again.
rtError_t CreateBufferInternal(size_t size, Buffer *buf) {
    void *ptr = nullptr;
    rtError_t ret = AllocateMemoryInternal(size, &ptr);
    if (ret != RT_SUCCESS) {
        RT_LOG_ERROR("Failed to allocate memory for buffer in %s.", __func__);
        return ret;
    }
    // ... Business logic
    return RT_SUCCESS;
}

// External entry exception: The entry function is the user-visible reporting boundary. Even if the lower layer has already reported the error, the entry function still needs to report the API-level ErrMsg again.
rtError_t rtCreateBuffer(size_t size, rtBuffer_t *buffer) {
    Buffer buf;
    rtError_t ret = CreateBufferInternal(size, &buf);
    if (ret != RT_SUCCESS) {
        RT_LOG_OUTER_MSG_IMPL(ErrorCode::EE1013, std::to_string(size));
        return ret;
    }
    // ... Business logic
    return RT_SUCCESS;
}
```

## Printing Format Specifications

The Error Message printing format should follow the following specifications to ensure that the information is clear, standardized, and easy for users to understand.

### Enum Value Printing Specifications

**Rule 1: Printing user-passed enum values**

For user-passed enum parameters, use the enum-to-string function for printing, in the format `EnumName(value)`:
- Examples of valid values: `GLOBAL(0)`, `THREAD_LOCAL(1)`, `RELAXED(2)`
- Example of an invalid value (not in the enum definition): `UNKNOWN(100)`. The numeric value must be printed as well.

**Rule 2: Description of expected values (valid value ranges)**

| Expected Value Type | Description Method | Example |
|-----------|---------|------|
| Continuous interval `[a, b)` or `[a, b]` | Keep the original interval description | `[0, 10]` |
| Discrete enum values (one or more specific enum values) | Use the `EnumName(value)` format, consistent with Rule 1 | `RELAXED(2)` or `GLOBAL(0) THREAD_LOCAL(1)` |

**Rule 3: Printing the chip type (chipType)**

The chip type (chipType) is an internal enum. The enum-to-string format in Rule 1 does not apply. Keep only numeric printing and do not print the enum name description.

```cpp
// src/runtime/api/api_c_standard_soc.cc:593
COND_RETURN_EXT_ERRCODE_AND_MSG_OUTER((priority != RT_STREAM_GREATEST_PRIORITY) &&
    (!IS_SUPPORT_CHIP_FEATURE(chipType, RtOptionalFeatureType::RT_FEATURE_STREAM_CREATE_PRIORITY_GREATEST)),
    RT_ERROR_INVALID_VALUE, ErrorCode::EE1011, __func__, StreamPriorityToString(priority).c_str(), "priority",
    "The priority can be set to RT_STREAM_GREATEST_PRIORITY only when chipType is " + std::to_string(CHIP_DC) +
    ". The actual chipType is " + std::to_string(chipType));
```

### Parameter Printing Specifications

- User input parameters need to print the parameter name and the parameter value or address, ensuring that users can accurately locate the problem parameter.
- Presenting with the `[%s]` square bracket format is forbidden. Use `%s` directly or integrate the variable into the sentence. The square bracket format of numeric variables (`%u`, `%d`, and so on), such as `label [%u]`, is not subject to this restriction.

### Proper Noun Printing Specifications

Proper nouns need to use correct capitalization and formatting. Keep the original text unsplit and use a consistent format.

Common proper nouns:
- AI CPU
- ACL Graph
- SQ/CQ
- IPC Notify

### ID Parameter Printing Specifications

Printing formats for identifiers such as `stream id` and `model id`:
- `stream (stream_id=%d)`
- `model (model_id=%d)`
- `event (event_id=%d)`
- `notify (notify_id=%u)`

### Internal Function Name Printing Specifications

Print internal function names as functional descriptions instead of printing the function names directly, so that users can understand them.

Examples:
- Recommended: `Failed to allocate memory for internal buffer.`
- Not recommended: `Malloc failed.`

### EE9999/EH9999 Sentence Pattern Specifications

For internal errors (EE9999/EH9999), use the `Failed to` sentence pattern to clearly describe the failed operation.

Example: `Failed to allocate memory for internal buffer.`

### Sentence Completeness Specifications

Use one complete sentence to express the error message:
- Capitalize the first letter.
- Determine whether to add a period at the end of the sentence based on the error code type.

### Error Message Reason Description Specifications

The `Reason: %s` part in ErrMessage supplements the specific cause of the error. It should follow the following specifications:

- Reason should concisely describe the specific cause of the failure and avoid repeating the information already expressed by ErrMessage.
- Reason should not only state the cause of the problem but also provide executable solutions for the user.
- Reason content should be consistent with the context and help users understand the root cause of the failure.
