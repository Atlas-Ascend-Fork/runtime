# Error Message Reporting Macro Usage Guidelines

This document describes the parameter style, control-flow behavior, applicable scenarios, and selection rules of the ErrMsg reporting macros. It helps you select the correct reporting macro based on the error code and business scenario.

---

## Background

### Two Methods of Error Recording

The Runtime code provides two methods of error recording:

1. **RT_LOG logging**: The `RT_LOG_*` macros record logs. The logs are written only to log files, and the caller cannot obtain the logs programmatically.

2. **ErrMsg reporting**: ErrorManager reports structured error information, and the caller can obtain the information programmatically.

### Complete Flow of ErrMsg

```
Error occurs → the code calls the reporting macro → ErrorManager stores the error → the caller obtains the error information
```

- **Reporting**: The code calls an ErrMsg reporting macro, such as `COND_RETURN_AND_MSG_OUTER`.
- **Storing**: The macro eventually calls the core functions of ErrorManager and stores the error information in thread-local storage.
- **Retrieval**:
  - Internal callers: They obtain the error through `GetErrMgrErrorMessage()` or `GetRawErrorMessages()`.
  - External users: They obtain the error through the `aclGetRecentErrMsg()` API.

### Error Code Format

An error code is a 6-character string: **E + module identifier + 4 digits**

| Module Identifier | Module Name | Example Error Code |
|---------|---------|-----------|
| E | Runtime | EE1001, EE9999 |
| H | ACL | EH0007, EH9999 |
| I | HCCL | EI9999 |
| L | Driver | EL9999 |
| K | Profiling | EK9999 |
| Z | Operator common error codes and operator API execution API error codes | EZ9999 |

### Two Types of Errors

- **Internal errors** (the last four digits are 9999): These errors have no JSON template and record only the raw message. They indicate internal logic errors, for example EE9999, EI9999, and EL9999.
- **External errors** (the last four digits are 0001 to 8999): These errors have a JSON template (defined in `error_code.json`) that contains title/cause/solution and is displayed to users, for example EE1001 and EH0007.

### Four Core Reporting Functions

The code wraps many ErrMsg reporting macros. All these macros eventually call the four core functions of ErrorManager:

1. **`ReportInterErrMessage()`**: Reports an internal error (EX9999) and directly stores the raw message.
2. **`ReportErrMessage()`**: Reports an external error (EX0001 to EX8999) and fills the JSON template through args_map.
3. **`ATCReportErrMessage()`**: Reports an external error and fills the JSON template through a key/value vector (the function is the same as the previous one, but the parameter form is different).
4. **`ReportErrMsgWithoutTpl()`**: Reports a user-defined error (EU0000 to EU9999) without a template and directly stores the message.

---

# 1. Runtime Module (Code Directory: `src/runtime/`)

---

## 1. Macro Table Column Definitions

The macro tables in subsequent sections use the following columns to describe the characteristics of each macro. The meaning and optional values of each column are defined as follows:

### Return Type

| Value | Meaning |
|----|------|
| rtError_t | Returns a Runtime internal error code |
| void | No return value (`return;`) |
| ACL error code (converted from rt) | Calls `GetRtExtErrCodeAndSetGlobalErr()` to convert rtError_t to an ACL external error code and set the global error code |
| None | Reports or jumps only, without returning a value through return |

### Condition Type

| Value | Meaning |
|----|------|
| Custom condition | The caller passes in an arbitrary Boolean expression (usually with `unlikely()`) |
| Null pointer | Checks `PTR == nullptr` |
| Zero value | Checks `PARAM == 0U` |
| Error code != NONE | Checks `ERRCODE != RT_ERROR_NONE` |
| Unconditional | Reports unconditionally (without checking a condition) |

### PROC

| Value | Meaning |
|----|------|
| Yes | The macro executes an arbitrary statement before reporting (such as releasing resources, closing handles, and so on). The corresponding macro name usually contains `PROC` |
| No | The macro does not execute a preceding statement |

### GOTO

| Value | Meaning |
|----|------|
| Yes | After reporting, the macro executes `goto LABEL` to jump to the error handling label and may also assign a value to the ERROR variable |
| No | The macro does not execute goto |

### Setting the Global Error Code

| Value | Meaning |
|----|------|
| Yes | When reporting, the macro calls `GetRtExtErrCodeAndSetGlobalErr()` to convert rtError_t to an ACL error code and set the global error code |
| No | The macro only reports ErrMsg and does not set the global error code |

### Recommendation Level

| Value | Meaning |
|----|------|
| Recommended | Primary macro with clear scenarios; prefer it in new code |
| Specific scenarios | Has a clear applicable scenario but is less general than the recommended macro |
| Use with caution | Has constraints or overlaps with the recommended macro; confirm before use |
| Forbidden | Has design flaws; do not use it in new code |
---

## 2. String Format Description

ErrMsg macros provide two string passing methods. You must distinguish them during use:

### printf Style (Used by _INNER Macros)

The `_INNER` series of macros (such as `COND_RETURN_AND_MSG_INNER`) uses printf-style `format, ...` parameters. You directly pass in the format string and variable arguments:

```cpp
COND_RETURN_AND_MSG_INNER(ptr == nullptr, RT_ERROR_INVALID_VALUE,
    "Init failed, devId=%u, size=%zu", devId, size);
```

**Do not** concatenate a `std::string` first and then pass it in:
```cpp
// Wrong usage: This bloats the .so file.
std::string msg = "Init failed, devId=" + std::to_string(devId);
COND_RETURN_AND_MSG_INNER(ptr == nullptr, RT_ERROR_INVALID_VALUE, "%s", msg.c_str());
```

If you need a pre-formatted string (for example, the message content requires dynamic concatenation), you must use the `RtFmtMsg` function:
```cpp
// Correct usage.
COND_RETURN_AND_MSG_INNER(ptr == nullptr, RT_ERROR_INVALID_VALUE,
    "%s", RtFmtMsg("Init failed, devId=%u, reason=%s", devId, reason).c_str());
```

### Structured Parameter Style (Used by _OUTER Macros)

The `_OUTER` series of macros (such as `COND_RETURN_AND_MSG_OUTER`) uses structured parameters. `ErrorCodeProcess` automatically converts each parameter to a string to match the `%s` placeholders in the X-macro templates in `error_code_meta.h`. The number of parameters must be consistent with the template.

```cpp
COND_RETURN_AND_MSG_OUTER(ret != RT_ERROR_NONE, RT_ERROR_FEATURE_NOT_SUPPORT,
    ErrorCode::EE1006, __func__, "stream mode switching");
```

For a reason parameter that requires dynamic concatenation, **do not** directly add `std::string` objects either; use `RtFmtMsg` instead:
```cpp
// Wrong usage: This bloats the .so file.
COND_RETURN_AND_MSG_OUTER(..., ErrorCode::EE1016, __func__,
    "Changing stream " + std::to_string(id) + " is not supported");

// Correct usage.
COND_RETURN_AND_MSG_OUTER(..., ErrorCode::EE1016, __func__,
    RtFmtMsg("Changing stream %u is not supported", id));
```

> **Why is `std::string` addition forbidden?** `std::string` concatenation generates many temporary string objects and template instantiation code in the build artifacts, which significantly bloats the .so file. `RtFmtMsg` uses an on-stack `char[]` buffer and `snprintf`, so the build artifacts are more compact.

### Semantic Function Description (_WITH_DESC / _WITH_FUNC_DESC Variants)

Some `_OUTER` macros provide the `_WITH_DESC` or `_WITH_FUNC_DESC` suffix variants. The difference lies in how the function description is passed in:

| Variant Suffix | Function Description Source | Example |
|---------|------------|------|
| No suffix (such as `RT_LOG_OUTER_MSG_WITH_FUNC`) | `__func__` (C++ function name) | `"MemCopySync"` |
| `_WITH_DESC` / `_WITH_FUNC_DESC` | The `funcDesc` string passed in by the caller | `"Synchronous memory copy"` |

`__func__` is the compiler-generated function name, which is not friendly enough to users. The `_WITH_DESC` / `_WITH_FUNC_DESC` variants allow you to pass in a semantic description string, making the error information easier to understand.

**Selection recommendation**: In new code, for non-API-layer code (functions that do not start with acl, rt, or aclrt), prefer the `_WITH_DESC` / `_WITH_FUNC_DESC` variants and pass in a string that describes the semantics of the current operation. For example:

```cpp
// Recommended: use a semantic description.
RT_LOG_OUTER_MSG_WITH_FUNC_DESC(ErrorCode::EE1005, "Closing the IPC shared memory");

// Not recommended: use __func__ (the function name is meaningless to users).
RT_LOG_OUTER_MSG_WITH_FUNC(ErrorCode::EE1005);
```

---

## 3. External Error Code Macros

External error codes have JSON templates. You can obtain the formatted message with title/cause/solution through `GetErrMgrErrorMessage()`.

### EE1003 - Invalid_Argument (Parameter Value Validation)

Use these macros when a parameter value is invalid. The macro automatically injects the parameter name string, so you only need to pass in the parameter value and the expected value. The `_DESC` variant additionally receives the `FUNC_DESC` parameter for a semantic function description (see the "Semantic Function Description" section for details).

| Macro Name | Return Type | Condition Type | PROC | GOTO | Set Global Error Code | Recommendation Level | Alternative Macro |
|------|---------|---------|------|------|--------------|---------|--------|
| COND_RETURN_AND_MSG_OUTER_WITH_PARAM | rtError_t | Custom condition | No | No | No | Recommended | — |
| COND_RETURN_AND_MSG_OUTER_WITH_PARAM_DESC | rtError_t | Custom condition | No | No | No | Recommended | — |
| COND_RETURN_AND_MSG_OUTER_WITH_PARAM_NAME | rtError_t | Custom condition | No | No | No | Recommended | — |
| COND_RETURN_AND_MSG_OUTER_WITH_PARAM_NAME_DESC | rtError_t | Custom condition | No | No | No | Recommended | — |
| ZERO_RETURN_AND_MSG_OUTER | rtError_t | Zero value | No | No | No | Recommended | — |
| COND_RETURN_EXT_ERRCODE_AND_MSG_OUTER_WITH_PARAM | ACL error code (converted from rt) | Custom condition | No | No | Yes | Recommended | — |
| COND_RETURN_EXT_ERRCODE_AND_MSG_OUTER_WITH_PARAM_NAME | ACL error code (converted from rt) | Custom condition | No | No | Yes | Recommended | — |
| RT_LOG_OUTER_MSG_INVALID_PARAM | None | Unconditional | No | No | No | Specific scenarios | — |
| RT_LOG_OUTER_MSG_INVALID_PARAM_WITH_DESC | None | Unconditional | No | No | No | Specific scenarios | — |

### EE1004 - Invalid_Argument_Null_Pointer

These macros are dedicated to null pointer checks. The macro automatically uses `#PTR` (stringified parameter name), so you do not need to pass it in manually. The `_WITH_FUNC_DESC` variant additionally receives the `FUNC_DESC` parameter for a semantic function description (see the "Semantic Function Description" section for details).

| Macro Name | Return Type | Condition Type | PROC | GOTO | Set Global Error Code | Recommendation Level | Alternative Macro |
|------|---------|---------|------|------|--------------|---------|--------|
| NULL_PTR_RETURN_MSG_OUTER | rtError_t | Null pointer | No | No | No | Recommended | — |
| NULL_PTR_RETURN_MSG_OUTER_WITH_FUNC_DESC | rtError_t | Null pointer | No | No | No | Recommended | — |
| PARAM_NULL_RETURN_ERROR_WITH_EXT_ERRCODE | ACL error code (converted from rt) | Null pointer | No | No | Yes | Recommended | — |

### EE1010 - Execution_Error_Invalid_Context

These macros validate the ownership of objects such as stream/model/context. The macro automatically injects `__func__` and the object name.

| Macro Name | Return Type | Condition Type | PROC | GOTO | Set Global Error Code | Recommendation Level | Alternative Macro |
|------|---------|---------|------|------|--------------|---------|--------|
| COND_RETURN_AND_MSG_INVALID_CONTEXT | rtError_t | Custom condition | No | No | No | Recommended | — |
| RT_LOG_OUTER_MSG_INVALID_CONTEXT | None | Unconditional | No | No | No | Specific scenarios | — |

### EE1013 - Resource_Error_Insufficient_Host_Memory

These macros are dedicated to memory allocation failures. `bufSize` is the size of the requested memory.

| Macro Name | Return Type | Condition Type | PROC | GOTO | Set Global Error Code | Recommendation Level | Alternative Macro |
|------|---------|---------|------|------|--------------|---------|--------|
| COND_PROC_RETURN_AND_MSG_ALLOC_FAILED | rtError_t | Custom condition | Yes | No | No | Recommended | — |

### EE1016 - Stream_Capture_Mode_Not_Support

These macros are dedicated to stream capture mode checks. They check whether the current context supports the capture operation. If the operation is not supported, the macro reports EE1016 and returns `RT_ERROR_STREAM_CAPTURE_MODE_NOT_SUPPORT`. The `CheckCaptureModeSupport()` function internally completes the actual ErrMsg reporting through `RT_LOG_OUTER_MSG_IMPL(ErrorCode::EE1016, funcName, reason)`. The `_WITH_DESC` variant passes in a semantic function description instead of `__func__` (see the "Semantic Function Description" section for details).

| Macro Name | Return Type | Condition Type | PROC | GOTO | Set Global Error Code | Recommendation Level | Alternative Macro |
|------|---------|---------|------|------|--------------|---------|--------|
| CHECK_CAPTURE_MODE_SUPPORT_AND_RETURN | None | Custom condition | No | No | No | Recommended | — |
| CHECK_CAPTURE_MODE_SUPPORT_AND_RETURN_WITH_DESC | None | Custom condition | No | No | No | Recommended | — |

### EE1017 - Invalid_Argument (Reserved Parameter Validation)

Use these macros for reserved parameter validation. `param` is the parameter name, and `reason` is the reason why the parameter is invalid.

| Macro Name | Return Type | Condition Type | PROC | GOTO | Set Global Error Code | Recommendation Level | Alternative Macro |
|------|---------|---------|------|------|--------------|---------|--------|
| COND_RETURN_AND_MSG_RESERVED_PARAM | rtError_t | Custom condition | No | No | No | Recommended | — |
| RT_LOG_OUTER_MSG_RESERVED_PARAM | None | Unconditional | No | No | No | Specific scenarios | — |

### EE1001 - Invalid_Argument

**Forbidden.** The EE1001 error code and its dedicated macros (`COND_RETURN_OUT_ERROR_MSG_CALL` and `COND_PROC_RETURN_OUT_ERROR_MSG_CALL`) are forbidden in new code. They are used only for fallback logic.


### Primary Wrapper Macros for General External Error Codes

These macros apply to external error codes without dedicated macros, such as EE1005 to EE1021 (excluding the EE1016 capture mode scenario), EE2002, WE0000, and WE0001. The caller passes in the `ErrorCode` enum value and the corresponding parameters.

| Macro Name | Return Type | Condition Type | PROC | GOTO | Set Global Error Code | Recommendation Level | Alternative Macro |
|------|---------|---------|------|------|--------------|---------|--------|
| COND_RETURN_AND_MSG_OUTER | rtError_t | Custom condition | No | No | No | Recommended | — |
| COND_RETURN_VOID_AND_MSG_OUTER | void | Custom condition | No | No | No | Recommended | — |
| COND_PROC_RETURN_AND_MSG_OUTER | rtError_t | Custom condition | Yes | No | No | Recommended | — |
| COND_PROC_RETURN_VOID_AND_MSG_OUTER | void | Custom condition | Yes | No | No | Recommended | — |
| COND_GOTO_MSG_OUTER | None | Custom condition | No | Yes | No | Recommended | — |
| COND_RETURN_EXT_ERRCODE_AND_MSG_OUTER | ACL error code (converted from rt) | Custom condition | No | No | Yes | Recommended | — |
| COND_RETURN_EXT_WARNCODE_AND_MSG_OUTER | ACL error code (converted from rt) | Custom condition | No | No | Yes | Recommended | — |
---

### Low-Level Reporting Macros for General External Error Codes

These macros directly call ErrorManager or a low-level logging API. They apply to special scenarios where higher-level macros cannot meet requirements. Some macros already have better alternatives and should not be used directly.

| Macro Name | Error Code Filling Method | Actual Error Code | Reporting Type | Recommendation Level | Alternative Macro |
|------|--------------|-----------|---------|---------|--------|
| RT_LOG_OUTER_MSG | Explicit input | String error code | External | Specific scenarios | — |
| RT_LOG_OUTER_MSG_IMPL | Explicit input | ErrorCode enum | External | Specific scenarios | — |
| RT_LOG_OUTER_MSG_WITH_FUNC | Explicit input | ErrorCode enum | External | Specific scenarios | — |
| RT_LOG_OUTER_MSG_WITH_FUNC_DESC | Explicit input | ErrorCode enum | External | Specific scenarios | — |
| REPORT_INPUT_ERROR | Explicit input | String error code | External | **Cannot be used directly** | — |
| REPORT_ENV_ERROR | Explicit input | String error code | External | **Cannot be used directly** | — |
---

### API-Layer Fallback Macros

**Used only for fallback reporting in the rt API layer; other scenarios are forbidden**

**Mapping rule**: Internally, the mapping is performed through the switch statement of `FuncErrorReason()`:

| rtError_t | Reported Error Code | Reporting Method |
|-----------|-----------|---------|
| RT_ERROR_INVALID_VALUE | EE1001 | RT_LOG_OUTER_MSG (printf) |
| RT_ERROR_CONTEXT_NULL | EE1001 | RT_LOG_OUTER_MSG (printf) |
| RT_ERROR_FEATURE_NOT_SUPPORT | EE1001 | RT_LOG_OUTER_MSG (printf) |
| RT_ERROR_INVALID_HANDLE | EE1017 | RT_LOG_OUTER_MSG_IMPL (independent parameters) |
| RT_ERROR_STREAM_SYNC_TIMEOUT | EE1002 | RT_LOG_OUTER_MSG (printf) |
| default | EE9999 | RT_LOG_CALL_MSG(ERR_MODULE_GE) |

| Macro Name | Return Type | Condition Type | PROC | GOTO | Set Global Error Code | Recommendation Level | Alternative Macro |
|------|---------|---------|------|------|--------------|---------|--------|
| ERROR_RETURN_WITH_EXT_ERRCODE | ACL error code (converted from rt) | Error code != NONE | No | No | Yes | Recommended | — |
| REPORT_FUNC_ERROR_REASON | None | None | No | No | No | Cannot be used directly | ERROR_RETURN_WITH_EXT_ERRCODE |
---


## 4. Internal Error Code Macros

Internal error codes have no JSON template. Only one error is displayed as the first error in one error retrieval. The first external error code is preferred as the first error (with title/cause/solution), and all remaining errors enter TraceBack. If this report contains only internal error codes, the first one becomes the first error (in the format `XX9999: Inner Error!`), and the remaining errors enter TraceBack.

### _INNER Series (EE9999)

These macros map to EE9999 (or WE9999) and apply to Runtime internal logic errors. They use printf-style format strings.

**Mapping rule**: Macros with the `_INNER` suffix are mapped through the `RT_LOG_LEVEL_TO_ERR_MSG[]` array: RT_LOG_ERROR → EE9999, RT_LOG_WARNING → WE9999, and other levels → INVALID_HEAD (abnormal, should not be used).

| Macro Name | Return Type | Condition Type | PROC | GOTO | Set Global Error Code | Recommendation Level | Alternative Macro |
|------|---------|---------|------|------|--------------|---------|--------|
| NULL_STREAM_PTR_RETURN_MSG | rtError_t | Null pointer | No | No | No | Recommended | — |
| NULL_PTR_RETURN_MSG | rtError_t | Null pointer | No | No | No | Recommended | — |
| NULL_PTR_PROC_RETURN_ERROR_MSG_INNER | rtError_t | Null pointer | Yes | No | No | Recommended | — |
| NULL_PTR_GOTO_MSG_INNER | None | Null pointer | No | Yes | No | Recommended | — |
| ZERO_RETURN_MSG | rtError_t | Zero value | No | No | No | Use with caution | COND_RETURN_AND_MSG_INNER or ZERO_RETURN_AND_MSG_OUTER |
| COND_RETURN_AND_MSG_INNER | rtError_t | Custom condition | No | No | No | Recommended | — |
| COND_RETURN_VOID_AND_MSG_INNER | void | Custom condition | No | No | No | Recommended | — |
| COND_AND_MSG_INNER | None | Custom condition | No | No | No | Recommended | — |
| COND_PROC_RETURN_ERROR_MSG_INNER | rtError_t | Custom condition | Yes | No | No | Recommended | — |
| COND_RETURN_ERROR_MSG_INNER | rtError_t | Custom condition | No | No | No | Use with caution | COND_RETURN_AND_MSG_INNER |
| COND_GOTO_ERROR_MSG_AND_ASSIGN_INNER | None | Custom condition | No | Yes | No | Recommended | — |
| COND_PROC_GOTO_MSG_INNER | None | Custom condition | Yes | Yes | No | Recommended | — |
| ERROR_RETURN_MSG_INNER | rtError_t | Error code != NONE | No | No | No | Recommended | — |
| ERROR_PROC_RETURN_MSG_INNER | rtError_t | Error code != NONE | Yes | No | No | Recommended | — |
| ERROR_GOTO_MSG_INNER | None | Error code != NONE | No | Yes | No | Recommended | — |
| ERROR_PROC_GOTO_MSG_INNER | None | Error code != NONE | Yes | Yes | No | Recommended | — |
| COND_RETURN_EXT_ERRCODE_AND_MSG_INNER | ACL error code (converted from rt) | Custom condition | No | No | Yes | Recommended | — |
### _CALL Series (MODULE_TYPE Mapping)

These macros map to the internal error code of the corresponding module through MODULE_TYPE. They apply to cross-module error reporting and mark the error source.

**Mapping rule**: Macros with the `_CALL` suffix are mapped through the `RT_MODULE_TYPE_TO_ERR_MSG[]` array:

| MODULE_TYPE | Mapped Error Code | Description |
|-------------|-----------|------|
| ERR_MODULE_AICPU | E39999 | AI CPU module |
| ERR_MODULE_DRV | EL9999 | Driver module |
| ERR_MODULE_HCCL | EI9999 | HCCL module |
| ERR_MODULE_GE | EE9999 | GE module (not recommended for new use) |
| ERR_MODULE_PROFILE | EK9999 | Profiling module |
| ERR_MODULE_TBE | EZ9999 | TBE module |
| ERR_MODULE_SYSTEM | EE9999 | System module |
| ERR_MODULE_RTS | EE9999 | RTS module |
| ERR_MODULE_FE | E29999 | FE module |
| ERR_MODULE_AICPU_TIMEOUT | E30008 | AI CPU timeout |
| ERR_MODULE_INVALID_ARGUMENT | EE1001 | Invalid parameter |

| Macro Name | Return Type | Condition Type | PROC | GOTO | Set Global Error Code | Recommendation Level | Alternative Macro |
|------|---------|---------|------|------|--------------|---------|--------|
| NULL_PTR_PROC_RETURN_ERROR_MSG_CALL | rtError_t | Null pointer | Yes | No | No | Specific scenarios | — |
| NULL_PTR_GOTO_MSG_CALL | None | Null pointer | No | Yes | No | Specific scenarios | — |
| COND_RETURN_ERROR_MSG_CALL | rtError_t | Custom condition | No | No | No | Specific scenarios | — |
| COND_PROC_RETURN_ERROR_MSG_CALL | rtError_t | Custom condition | Yes | No | No | Specific scenarios | — |
| COND_GOTO_ERROR_MSG_AND_ASSIGN_CALL | None | Custom condition | No | Yes | No | Specific scenarios | — |
| COND_PROC_GOTO_MSG_CALL | None | Custom condition | Yes | Yes | No | Specific scenarios | — |
| ERROR_RETURN_MSG_CALL | rtError_t | Error code != NONE | No | No | No | Specific scenarios | — |
| ERROR_PROC_RETURN_MSG_CALL | rtError_t | Error code != NONE | Yes | No | No | Specific scenarios | — |
| ERROR_GOTO_MSG_CALL | None | Error code != NONE | No | Yes | No | Specific scenarios | — |
| ERROR_PROC_GOTO_MSG_CALL | None | Error code != NONE | Yes | Yes | No | Specific scenarios | — |

### Low-Level Reporting Macros for Internal Error Codes

These macros directly call ErrorManager or a low-level logging API. They apply to special scenarios where higher-level macros cannot meet requirements. Some macros already have better alternatives and should not be used directly.

| Macro Name | Error Code Filling Method | Actual Error Code | Reporting Type | Recommendation Level | Alternative Macro |
|------|--------------|-----------|---------|---------|--------|
| RT_LOG_INNER_MSG | Mapping | RT_LOG_LEVEL | Internal | Specific scenarios | — |
| RT_LOG_CALL_MSG | Mapping | MODULE_TYPE | Internal | Specific scenarios | — |
| RT_LOG_CALL_MSG_NO_RT_LOG | Mapping | MODULE_TYPE | Internal | **Cannot be used directly** | RT_LOG_CALL_MSG |
| REPORT_INNER_ERROR | Explicit input | String error code | Internal | **Cannot be used directly** | RT_LOG_INNER_MSG |
| REPORT_CALL_ERROR | Explicit input | String error code | Internal | **Cannot be used directly** | RT_LOG_CALL_MSG |

---

## 5. Quick Selection Guide

Select a macro that meets your requirements in the following way:

```
Does the error code you want to report have a dedicated macro?
├─ Yes (EE1003/EE1004/EE1010/EE1013/EE1016/EE1017, see Section 3)
│   └─ Can a dedicated macro meet my scenario? (determine by PROC/GOTO/return type/set global error code)
│       ├─ Yes → use the dedicated macro
│       └─ No
│           └─ Can a general macro meet my scenario?
│               ├─ Yes → use the general macro (see "Primary Wrapper Macros for General External Error Codes" in Section 3)
│               └─ No → use the low-level macro (see "Low-Level Reporting Macros for General External Error Codes" in Section 3)
│
└─ No (EE1001 is forbidden; EE1005~EE1023, EE2002, WE0000, WE0001, and so on have no dedicated macros)
    └─ Can a general macro meet my scenario?
        ├─ Yes → use the general macro (see "Primary Wrapper Macros for General External Error Codes" in Section 3)
        └─ No → use the low-level macro (see "Low-Level Reporting Macros for General External Error Codes" in Section 3)
```

For internal error codes (EE9999 / MODULE_TYPE mapping), the selection method is similar:

```
I want to report an internal error code
├─ The current code belongs to a Runtime module → use the _INNER series (see Section 4)
│   └─ Can the primary _INNER macro meet my scenario?
│       ├─ Yes → use the primary _INNER macro
│       └─ No → use the low-level _INNER macro (see "Low-Level Reporting Macros for Internal Error Codes" in Section 4)
│
└─ The current code calls other modules (GE/DRV/HCCL, and so on) and needs to mark the error source
    → use the _CALL series + the corresponding ERR_MODULE_xxx (see Section 4)
```

For API-layer fallback scenarios (used only in the rt API layer):

```
I want to make a fallback return in an rt API entry function
└─ use ERROR_RETURN_WITH_EXT_ERRCODE (see "API-Layer Fallback Macros" in Section 3)
```

# 2. ACL Module (Code Directory: `src/acl/`)

> Organization principle: EH error codes serve as the primary dimension, and dedicated macros take precedence over general macros.

---

## 1. Macro Table Column Definitions

The macro tables in subsequent sections use the following columns to describe the characteristics of each macro. The meaning and optional values of each column are defined as follows:

### Return Type

| Value | Meaning |
|----|------|
| aclError | Returns an ACL error code (such as `ACL_ERROR_INVALID_PARAM`) |
| nullptr | Returns a null pointer |
| void | No return value (`return;`) |
| Original return value | Passes through the return value of the called function (such as rtError_t and ge::Status) |
| None | Reports a log only, without changing the control flow |

### Condition Type

| Value | Meaning |
|----|------|
| Null pointer | Checks `val == nullptr` |
| Parameter value | Checks whether the parameter value is valid (range, positive/negative sign, equality, and so on) |
| Return value != OK | Checks whether the return value of the called function is not a success |
| Custom condition | The caller passes in an arbitrary Boolean expression |
| Unconditional | Reports unconditionally (without checking a condition) |

### ErrMsg Reporting

| Value | Meaning |
|----|------|
| EH00xx | Reports a predefined EH error code through `AclErrorLogManager::ReportInputError()` |
| EH9999 | Reports an internal error through `AclErrorLogManager::ReportInnerError()` or `ReportCallError()` |

---

## 2. EH Error Code Reference

| Constant Name | Error Code | Purpose |
|--------|--------|------|
| `INVALID_PARAM_MSG` | EH0001 | Invalid parameter (general) |
| `INVALID_NULL_POINTER_MSG` | EH0002 | Null pointer (general) |
| `INVALID_PATH_MSG` | EH0003 | Invalid path |
| `INVALID_FILE_MSG` | EH0004 | Invalid file |
| `INVALID_AIPP_MSG` | EH0005 | Invalid AIPP parameter |
| `UNSUPPORTED_FEATURE_MSG` | EH0006 | Unsupported feature |
| `INVALID_VALUE_MSG` | EH0007 | Invalid value (with expected value) |
| `NULL_POINTER_FUNC_MSG` | EH0008 | Null pointer (function parameter) |
| `INVALID_PARAM_REASON_MSG` | EH0009 | Invalid parameter (with reason) |
| `ALLOC_MEMORY_FAILED_MSG` | EH0010 | Memory allocation failure |
| `UNSUPPORTED_SYSTEM_MSG` | EH0011 | Unsupported system |
| `INVALID_PARAM_NO_VALUE_MSG` | EH0012 | Invalid parameter (no value) |
| `STANDARD_FUNC_FAILED_MSG` | EH0013 | Standard function call failure |
| (Hardcoded) | EH9999 | Internal error/call error (fallback) |

---

## 3. Null Pointer Check Macros (EH0008)

These macros check whether a pointer is `nullptr`. If the condition is met, the macro reports the EH0008 error and returns. This macro family is the most frequently used in the ACL layer (472+ usage sites). The `_WITH_FUNC_DESC` / `_AND_FUNC_DESC` variants replace `__func__` with a semantic description passed in by the caller (see "Semantic Function Description" in Section 8 for details).

| Macro Name | Return Type | Condition Type | Reported ErrMsg | Recommendation Level | Alternative Macro |
|------|---------|---------|------------|---------|--------|
| ACL_REQUIRES_NOT_NULL_WITH_INPUT_REPORT | ACL_ERROR_INVALID_PARAM | Null pointer | EH0008 | Recommended | — |
| ACL_REQUIRES_NOT_NULL_WITH_INPUT_REPORT_AND_FUNC_DESC | ACL_ERROR_INVALID_PARAM | Null pointer | EH0008 | Recommended | — |
| ACL_REQUIRES_NOT_NULL_RET_INPUT_REPORT | Caller-specified | Null pointer | EH0008 | Recommended | — |
| ACL_REQUIRES_NOT_NULL_RET_INPUT_REPORT_WITH_FUNC_DESC | Caller-specified | Null pointer | EH0008 | Recommended | — |
| ACL_REQUIRES_NOT_NULL_RET_NULL_INPUT_REPORT | nullptr | Null pointer | EH0008 | Recommended | — |
| ACL_REQUIRES_NOT_NULL_WITH_INPUT_REPORT_WITH_PRAM_NAME | ACL_ERROR_INVALID_PARAM | Null pointer | EH0008 | Specific scenarios | — |

**Description**:
- `ACL_REQUIRES_NOT_NULL_WITH_INPUT_REPORT` is the preferred macro. It returns `ACL_ERROR_INVALID_PARAM` and reports EH0008.
- The `_WITH_FUNC_DESC` / `_AND_FUNC_DESC` variants additionally receive the `funcDesc` parameter, which is used by non-API-layer code to pass in a semantic function description.
- The `_WITH_PRAM_NAME` variant applies to scenarios where the parameter name differs from the variable name.

---

## 4. Parameter Value Validation Macros (EH0007 / EH0009 / EH0012)

### EH0007 - Invalid Value (With Expected Value)

Use these macros when a parameter value is invalid. The macro automatically injects `__func__`, the parameter value, the parameter name, and the expected value. The `_WITH_FUNC_DESC` / `_AND_FUNC_DESC` variants replace `__func__` with a semantic description passed in by the caller (see "Semantic Function Description" in Section 8 for details).

| Macro Name | Return Type | Condition Type | Reported ErrMsg | Recommendation Level | Alternative Macro |
|------|---------|---------|------------|---------|--------|
| ACL_CHECK_INVALID_VALUE_WITH_EXPECT | ACL_ERROR_INVALID_PARAM | Parameter value (negated) | EH0007 | Recommended | — |
| ACL_CHECK_INVALID_VALUE_WITH_EXPECT_RET | Caller-specified | Parameter value (negated) | EH0007 | Recommended | — |
| ACL_CHECK_INVALID_VALUE_WITH_DESC | Caller-specified | Parameter value (negated) | EH0007 | Specific scenarios | — |
| ACL_CHECK_INVALID_VALUE_WITH_DESC_AND_FUNC_DESC | Caller-specified | Parameter value (negated) | EH0007 | Specific scenarios | — |
| ACL_REQUIRES_PARAM_EQUAL_REPORT | ACL_ERROR_INVALID_PARAM | Parameter value (not equal) | EH0007 | Recommended | — |
| ACL_REQUIRES_POSITIVE_REPORT | ACL_ERROR_INVALID_PARAM | Parameter value (<=0) | EH0007 | Recommended | — |
| ACL_REQUIRES_POSITIVE_REPORT_WITH_FUNC_DESC | ACL_ERROR_INVALID_PARAM | Parameter value (<=0) | EH0007 | Recommended | — |

**Description**:
- The condition of the `ACL_CHECK_INVALID_VALUE_WITH_EXPECT` series is **negated**: `if (!(condition))` means that the macro reports an error when the condition is not met.
- `ACL_REQUIRES_PARAM_EQUAL_REPORT` applies to scenarios where a parameter must equal a specific value.
- `ACL_REQUIRES_POSITIVE_REPORT` applies to scenarios where a parameter must be a positive number.
- The `_WITH_FUNC_DESC` / `_AND_FUNC_DESC` variants additionally receive the `funcDesc` parameter, which is used by non-API-layer code to pass in a semantic function description.

### EH0009 - Invalid Parameter (With Reason)

Use these macros when a parameter is invalid and you need to explain the reason in detail. The `_AND_FUNC_DESC` variant replaces `__func__` with a semantic description passed in by the caller (see "Semantic Function Description" in Section 8 for details).

| Macro Name | Return Type | Condition Type | Reported ErrMsg | Recommendation Level | Alternative Macro |
|------|---------|---------|------------|---------|--------|
| ACL_CHECK_INVALID_PARAM_WITH_REASON | ACL_ERROR_INVALID_PARAM | Custom condition | EH0009 | Recommended | — |
| ACL_CHECK_INVALID_PARAM_WITH_REASON_AND_FUNC_DESC | ACL_ERROR_INVALID_PARAM | Custom condition | EH0009 | Recommended | — |
| ACL_CHECK_INVALID_PARAM_WITH_REASON_RET | Caller-specified | Custom condition | EH0009 | Recommended | — |
| ACL_CHECK_INVALID_PARAM_WITH_REASON_RET_AND_FUNC_DESC | Caller-specified | Custom condition | EH0009 | Recommended | — |
| ACL_CHECK_INVALID_PARAM_WITH_REASON_DESC_RET | Caller-specified | Custom condition | EH0009 | Specific scenarios | — |
| ACL_CHECK_RESERVED_PARAM_REPORT_RET | Caller-specified | Parameter value (not equal) | EH0009 | Recommended | — |

**Description**:
- `ACL_CHECK_RESERVED_PARAM_REPORT_RET` is dedicated to reserved parameter validation (the parameter must equal a specific value, such as `flags == 0`).
- `ACL_CHECK_INVALID_PARAM_WITH_REASON_DESC_RET` applies to scenarios where you need to manually pass in the parameter name and parameter value (not `#param` stringification).
- The `_AND_FUNC_DESC` variant additionally receives the `funcDesc` parameter, which is used by non-API-layer code to pass in a semantic function description.

### EH0012 - Invalid Parameter (No Value)

Use these macros when a parameter is invalid but the parameter value does not need to be displayed.

| Macro Name | Return Type | Condition Type | Reported ErrMsg | Recommendation Level | Alternative Macro |
|------|---------|---------|------------|---------|--------|
| ACL_CHECK_INVALID_PARAM_NO_VALUE | ACL_ERROR_INVALID_PARAM | Custom condition (negated) | EH0012 | Recommended | — |

---

## 5. File Validation Macros (EH0004)

Use these macros when the file path is invalid or the file fails to open.

| Macro Name | Return Type | Condition Type | Reported ErrMsg | Recommendation Level | Alternative Macro |
|------|---------|---------|------------|---------|--------|
| ACL_CHECK_INVALID_FILE_MSG_RET | Caller-specified | Custom condition | EH0004 | Recommended | — |
| ACL_CHECK_FILE_OPEN_FAILED | Caller-specified | Custom condition (negated) | EH0004 | Recommended | — |

**Description**:
- `ACL_CHECK_FILE_OPEN_FAILED` automatically obtains `strerror(errno)` as the failure reason.
- `ACL_CHECK_INVALID_FILE_MSG_RET` requires you to manually pass in the reason.

---

## 6. Memory Allocation Validation Macros (EH0010)

Use these macros when memory allocation fails.

| Macro Name | Return Type | Condition Type | Reported ErrMsg | Recommendation Level | Alternative Macro |
|------|---------|---------|------------|---------|--------|
| ACL_CHECK_MALLOC_RESULT_REPORT_RET | Caller-specified | Null pointer | EH0010 | Recommended | — |

**Description**:
- The macro reports EH0010 (with buf_size) and returns the caller-specified type (either nullptr or an error code).

---

## 7. Internal Error Reporting Macros (EH9999)

These macros report the EH9999 internal error code.

### Report Only (Without Changing the Control Flow)

| Macro Name | Return Type | Condition Type | Recommendation Level |
|------|---------|---------|---------|
| ACL_LOG_INNER_ERROR / ACL_LOG_CALL_ERROR | None | Unconditional | Recommended |

**Description**:
- The two macros have exactly the same implementation (both call `AclErrorLogManager::ReportInnerError()` → `REPORT_INNER_ERR_MSG("EH9999", ...)`).

### Condition Check + Reporting + Return

| Macro Name | Return Type | Condition Type | Recommendation Level |
|------|---------|---------|---------|
| ACL_CHECK_WITH_INNER_MESSAGE_AND_RETURN | Caller-specified | Custom condition (negated) | Recommended |
| ACL_REQUIRES_NOT_NULL_WITH_INNER_REPORT | ACL_ERROR_INVALID_PARAM | Null pointer | Specific scenarios |
| ACL_CHECK_MALLOC_RESULT | ACL_ERROR_BAD_ALLOC | Null pointer | Specific scenarios |
| ACL_REQUIRES_EQ | ACL_ERROR_INVALID_PARAM | Parameter value (not equal) | Specific scenarios |
| ACL_REQUIRES_LE | ACL_ERROR_INVALID_PARAM | Parameter value (greater than) | Specific scenarios |

**Description**:
- `ACL_CHECK_WITH_INNER_MESSAGE_AND_RETURN`: The condition is negated (`if (!(exp))`), and this macro is the most general.
- `ACL_REQUIRES_NOT_NULL_WITH_INNER_REPORT`: Null pointer check + EH9999. To report EH0008, use the macros in Section 3.
- `ACL_CHECK_MALLOC_RESULT`: Memory allocation failure. The macro always returns `ACL_ERROR_BAD_ALLOC`. To report EH0010, use `ACL_CHECK_MALLOC_RESULT_REPORT_RET`.

### Return Value Check + Reporting + Pass-Through

| Macro Name | Return Type | Condition Type | Recommendation Level |
|------|---------|---------|---------|
| ACL_REQUIRES_OK_WITH_INNER_MESSAGE | Original return value | Return value != OK | Recommended |
| ACL_REQUIRES_CALL_RTS_OK | Original return value | Return value != NONE | Recommended |
| ACL_REQUIRES_RTS_OK_WARN_NOT_SUPPORT | Original return value | Return value != NONE | Recommended |
| ACL_REQUIRES_RTS_OK | Original return value | Return value != NONE | Recommended |
| ACL_REQUIRES_CALL_GE_OK | Original return value | Return value != ge::SUCCESS | Recommended |
| ACL_REQUIRES_EOK | ACL_ERROR_FAILURE | Return value != EOK | Recommended |

**Description**:
- `ACL_REQUIRES_CALL_RTS_OK` specially handles `ACL_ERROR_RT_FEATURE_NOT_SUPPORT`: it only records a WARN log and does not report ErrMsg. Other failures report EH9999.
- `ACL_REQUIRES_RTS_OK_WARN_NOT_SUPPORT` specially handles `ACL_ERROR_RT_FEATURE_NOT_SUPPORT`: it only records a WARN log. Other failures do not report ErrMsg (rt already performs fallback reporting, and acl does not report again).
- `ACL_REQUIRES_RTS_OK` applies to scenarios where the rt API has already performed fallback reporting through `ERROR_RETURN_WITH_EXT_ERRCODE`. The acl side does not report again and only returns `ACL_GET_ERRCODE_RTS(__ret)` without reporting ErrMsg.
- `ACL_REQUIRES_EOK` applies to secure functions (memcpy_s and so on) and always returns `ACL_ERROR_FAILURE`.

---

## 8. Semantic Function Description (_WITH_FUNC_DESC / _AND_FUNC_DESC Variants)

Some macros in the ACL layer provide the `_WITH_FUNC_DESC` or `_AND_FUNC_DESC` suffix variants. The difference lies in how the function description is passed in:

| Variant Suffix | Function Description Source | Example |
|---------|------------|------|
| No suffix (such as `ACL_REQUIRES_NOT_NULL_WITH_INPUT_REPORT`) | `__func__` (C++ function name, with the `Impl` suffix automatically removed) | `"aclrtMemcpy"` |
| `_WITH_FUNC_DESC` / `_AND_FUNC_DESC` | The `funcDesc` string passed in by the caller | `"Checking the synchronous memory copy parameter validity"` |

> **Naming description**: The two suffixes have exactly the same function. Both replace `__func__` with the `funcDesc` passed in by the caller. The suffix choice depends on the base macro name. If the base macro name ends with `_REPORT`, the new variant uses `_WITH_FUNC_DESC` (for example, `ACL_REQUIRES_POSITIVE_REPORT_WITH_FUNC_DESC`). In other cases, the variant uses `_AND_FUNC_DESC` (for example, `ACL_CHECK_INVALID_VALUE_WITH_DESC_AND_FUNC_DESC`).

Macros without a suffix automatically obtain the function name through `GetFuncNameWithoutImplSuffix(__func__)`. The `_WITH_FUNC_DESC` / `_AND_FUNC_DESC` variants allow you to pass in a semantic description string, making the error information easier to understand.

**Selection recommendation**: In new code, for non-API-layer code (functions that do not start with `acl`, `rt`, or `aclrt`), prefer the `_WITH_FUNC_DESC` / `_AND_FUNC_DESC` variants and pass in a string that describes the semantics of the current operation. For example:

```cpp
// Recommended: use a semantic description for non-API-layer code.
ACL_REQUIRES_NOT_NULL_WITH_INPUT_REPORT_AND_FUNC_DESC(dst, "Checking the synchronous memory copy parameter validity");

// API-layer functions (aclrtXxx) can directly use the macro without a suffix. __func__ is a meaningful API name.
ACL_REQUIRES_NOT_NULL_WITH_INPUT_REPORT(dst);
```

For scenarios where you manually call `AclErrorLogManager::ReportInputError()`, replace `__func__` with a semantic description string as well:

```cpp
// Recommended: pass in a semantic description for non-API-layer code.
acl::AclErrorLogManager::ReportInputError(
    acl::INVALID_VALUE_MSG, std::vector<const char*>({"func", "value", "param", "expect"}),
    std::vector<const char*>({"Memory copy type conversion", acl::GetMemcpyKindDesc(kind), "kind", "..."}));
```

---

## 9. Quick Selection Guide

```
Does the error code you want to report have a dedicated macro?
├─ Yes (null pointer → EH0008, parameter value → EH0007/EH0009/EH0012, file → EH0004, memory → EH0010, see Sections 3 to 6)
│   └─ Can a dedicated macro meet my scenario? (determine by return type/condition type)
│       ├─ Yes → use the dedicated macro (for non-API-layer code, prefer the _WITH_FUNC_DESC / _AND_FUNC_DESC variants, see Section 8)
│       └─ No → manually call AclErrorLogManager::ReportInputError() (see the description below) or develop a new macro
│
└─ No (EH0001/EH0003/EH0006/EH0011/EH0013 and so on have no dedicated macros)
    └─ manually call AclErrorLogManager::ReportInputError() (see the description below) or develop a new macro
```

**Usage example**:
```cpp
acl::AclErrorLogManager::ReportInputError(acl::INVALID_PATH_MSG,
    std::vector<const char *>({"path", "reason"}),
    std::vector<const char *>({path, "file not found"}));
```
