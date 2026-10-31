# Error Message Review Checklist

## Overview

This checklist is used to check whether ErrMsg macro modifications comply with the specifications, focusing on **the dual-source text quality of error_code.json / error_code_meta.h**, **macro parameter count matching**, **ErrMsg syntax problems**, and **parameter types**.

## 1. error_code.json Verification

### Check Item — Dual-Source Synchronization Between error_code.json and error_code_meta.h
(1) When you add or modify an error code, **you must update both places at the same time** and keep them consistent:

| File | Purpose | Consumer |
|------|------|--------|
| `src/dfx/error_manager/error_code.json` | External error code metadata | `ErrorManager::ATCReportErrMessage` (ATC / external reporting path) |
| `src/runtime/core/inc/common/error_code_meta.h` → `RUNTIME_ERROR_CODE_TABLE` | X-Macro metadata table | `GetParamNames()` / `PrintErrMsgToLog()` |

(2) ErrMessage templates **must be exactly identical** (including punctuation and spaces)
(3) Arglist parameter names and parameter counts **must be exactly identical**
(4) Updating only one place and missing the other causes inconsistency between the ATC report and the runtime screen output message, or a parameter count verification failure

### Check Item — ErrMessage Text Verification

(1) First letter not capitalized: capitalize the first English letter (except placeholders)
(2) Missing ending period: a complete sentence should end with a period. When the last `%s` is a standalone `extend_info` and the template has no period, this is a design choice
(3) `%s` count does not match the Arglist: the number of `%s` placeholders in ErrMessage must equal the number of Arglist parameters
(4) `[%s]` bracket format: string variables in ErrMessage must not use the `[%s]` bracket format. Use `%s` directly or integrate the variable into the sentence
(5) Missing object ID: when ErrMessage involves a stream/model/event/notify object, its ID value must be printed

### Check Item — suggestion Verification

(1) Missing suggestion
(2) In suggestion, multiple pieces of information do not use the line break `\n` and should be separated by spaces. Handle special cases specially
(3) Missing space after the number: add a space after `1.`/`2.`
(4) Uniformly use N/A: `NA` → `N/A`
(5) First letter not capitalized: capitalize the first English letter
(6) Missing ending period: a complete sentence should end with a period. N/A does not need one
(7) Grammar errors: subject-verb agreement, tense, prepositions, and spelling

## 2. Macro + Error Code Verification for Modification Points

### Check Item — Parameter Count Verification

In `RUNTIME_ERROR_CODE_TABLE` in `error_code_meta.h`, each EE/EH error code has Arglist parameters, which represent the parameters to pass for the current error code. An incorrect number of passed parameters causes the ErrMsg screen output report to fail.

Parameter count calculation rules:

```
The number of valid parameters == the size of GetParamNames(ErrorCode)
```

`PrintErrMsgToLog` directly returns and prints a warning log when the parameter count does not match.

**EE layer macro parameter calculation rules:**

(1) The lowest-level external error code screen output macro `RT_LOG_OUTER_MSG_IMPL` does not automatically add any parameter

(2) The macro `RT_LOG_OUTER_MSG_WITH_FUNC`, which automatically prepends the function name, and the macros re-wrapped from it automatically add `__func__` as the first parameter. **The number of valid parameters = 1 + len(args)**. Do not manually pass `__func__` again. `RT_LOG_OUTER_MSG_WITH_FUNC_DESC` and its wrapped macros (such as `RT_LOG_OUTER_MSG_INVALID_PARAM_WITH_DESC`) behave similarly, but they automatically add the `funcDesc` passed in by the caller instead of `__func__`.

(3) Dedicated macros automatically handle common parameters to simplify usage. Calculate the number of valid parameters according to the actual situation. For example, the `RT_LOG_OUTER_MSG_INVALID_PARAM` macro is dedicated to EE1003, and its expansion chain is:

```
RT_LOG_OUTER_MSG_INVALID_PARAM(parm, expect)
  → RT_LOG_OUTER_MSG_WITH_FUNC(EE1003, (parm), #parm, expect)
    → RT_LOG_OUTER_MSG_IMPL(EE1003, __func__, (parm), #parm, expect)
```

The number of valid parameters = 3 + len(args). EE1003 expects 4 parameters, and the variable parameter should be 1 (that is, the expected value expect). `RT_LOG_OUTER_MSG_INVALID_PARAM_WITH_DESC(funcDesc, parm, expect)` has the same expansion chain, except that `__func__` is replaced with `funcDesc`.

**EH layer macro description:**

EH series error codes (ACL layer) are reported with `acl::AclErrorLogManager::ReportInputError`, passing parameters through a key-value string vector, without going through the `RT_LOG_OUTER_MSG_*` macro chain. The parameter count verification rule is the same: the number of passed values must equal the number of Arglist parameters.

Sources of the `func` parameter of ACL layer macros:
- Macros without a suffix (such as `ACL_REQUIRES_NOT_NULL_WITH_INPUT_REPORT`): automatically obtain the function name through `GetFuncNameWithoutImplSuffix(__func__)` (removing the `Impl` suffix)
- `_WITH_FUNC_DESC` / `_AND_FUNC_DESC` variants (such as `ACL_REQUIRES_NOT_NULL_WITH_INPUT_REPORT_AND_FUNC_DESC` and `ACL_REQUIRES_POSITIVE_REPORT_WITH_FUNC_DESC`): use the `funcDesc` string passed in by the caller
- When you manually call `ReportInputError`, the caller passes in the `func` value. Non-API-layer code should pass a semantic description instead of `__func__`

### Check Item — Parameter Value Verification

(1) Avoid `std::string` concatenation for parameter values: this method creates temporary variables and enlarges the so file. Use the `RtFmtMsg` function (defined in `rt_log.h`) to pass formatted strings into macros instead

(2) Missing or duplicate ending period: when an external error code is passed in through structured parameter macros, whether the parameter needs an ending period depends on the ErrMessage template.

- A period exists **after `%s` in the template** → the passed parameter **does not add a period** (to avoid a double period "..")
- No period exists **after `%s` in the template**, and the parameter is a complete English sentence → **add a period**

## 3. Common Errors

### 3.1 Duplication Between WITH_FUNC and Manual __func__

```
// ✗ WITH_FUNC automatically adds __func__. Passing it manually again causes duplication → parameters=5, but EE1011 expects 4
RT_LOG_OUTER_MSG_WITH_FUNC(ErrorCode::EE1011, __func__, ver, "ver", "msg");
// ✓ Pass only the variable parameters → parameters=1+3=4
RT_LOG_OUTER_MSG_WITH_FUNC(ErrorCode::EE1011, ver, "ver", "msg");
```

### 3.2 NA vs N/A

```
"suggestion": { "Solution": "NA" }    // ✗ Use "N/A" instead
"suggestion": { "Solution": "N/A" }   // ✓
```

### 3.3 Duplicate Periods

```
// ✗ The last %s in the ErrMessage template of EE1011 is followed by a period. Adding a period to the reason parameter causes duplication
COND_RETURN_AND_MSG_OUTER(!trueStream->IsModelStream(), RT_ERROR_STREAM_MODEL,
    ErrorCode::EE1011, __func__, 0, "trueStream->modelNum",
    "The stream is not bound to a model.");

// ✓ Do not add a period to the reason parameter
COND_RETURN_AND_MSG_OUTER(!trueStream->IsModelStream(), RT_ERROR_STREAM_MODEL,
    ErrorCode::EE1011, __func__, 0, "trueStream->modelNum",
    "The stream is not bound to a model");
```

> Note: `COND_RETURN_AND_MSG_OUTER` expands to `RT_LOG_OUTER_MSG_IMPL` (which does not automatically add `__func__`). Therefore, manually passing `__func__` here is correct. This differs from the WITH_FUNC duplication problem in 3.1.

### 3.4 Inconsistent Numeric Words in Logs

In log and error message strings, replace the standalone word `zero` with `0`. Do not replace hyphenated compound words (`zero-size`, `non-zero`, `divide-by-zero`, and `zero-copy`) or technical terms (`zero copy`).

```text
// ✗ count is zero, greater than zero
// ✓ count is 0, greater than 0
// ✓ zero-size memcpy (hyphenated compound words are not replaced)
// ✓ zero copy task (technical terms are not replaced)
```

## 4. Source File Index

| File | Purpose |
|------|------|
| `src/runtime/core/inc/common/error_code_meta.h` | X-Macro error code metadata table `RUNTIME_ERROR_CODE_TABLE` (data source of GetParamNames / PrintErrMsgToLog) |
| `src/dfx/error_manager/error_code.json` | External error code metadata (data source of ATCReportErrMessage) |
| `src/runtime/core/inc/base.hpp` | Core macro definitions + `ErrorCodeProcess` template function |
| `src/runtime/core/inc/common/rt_log.h` | `ErrorCode` enum + declarations of `GetParamNames` / `PrintErrMsgToLog` / `RtFmtMsg` |
| `src/runtime/core/inc/common/error_message_manage.hpp` | `COND_*` wrapped macros + dedicated macros |
| `src/runtime/api/api_c.h` | API layer macros (including `COND_RETURN_EXT_ERRCODE_AND_MSG_OUTER`) |
| `src/runtime/core/src/common/rt_log.cc` | Implementations of `GetParamNames` + `PrintErrMsgToLog` + `DispatchErrMsg` |
