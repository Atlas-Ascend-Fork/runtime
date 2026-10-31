# Runtime Error Message Development Guide

This directory is the unified specification source for Runtime/ACL error message rectification and review, shared by developers and AI agents. Maintain the rules for error codes, macros, error messages, and reporting boundaries in this directory first, to avoid interpretation drift after multiple skills copy the rules separately.

## Document Structure

| File | Purpose |
|------|------|
| [rectification-principles.md](rectification-principles.md) | Determining the rectification boundary, user errors/internal errors, parameter sources, the first occurrence site, defensive programming, repeated structured reporting, and print format specifications |
| [error-code-guide.md](error-code-guide.md) | Selecting Runtime EE and ACL EH error codes |
| [macro-selection-guide.md](macro-selection-guide.md) | Selecting ErrMsg external/internal error code reporting macros |
| [message-examples.md](message-examples.md) | Viewing ErrMsg message templates, Arglists, typical expressions, and message rectification examples |
| [review-checklist.md](review-checklist.md) | Reviewing whether ErrMsg modifications comply with the specifications, focusing on error_code.json / error_code_meta.h dual-source synchronization, macro parameter counts, error message syntax, and parameter values |

## How to Use

- When you determine whether rectification is needed, whether an error belongs to the first occurrence site, and whether reporting is repeated, or when you confirm the defensive programming and print format requirements, read `rectification-principles.md` first.
- When you select or review error codes, read `error-code-guide.md`. For ErrCode, ErrMessage, Arglist, and suggestion, `src/dfx/error_manager/error_code.json` is authoritative.
- When you select or review macros, read `macro-selection-guide.md`. Distinguish the printf-style parameters of the `_INNER` series from the structured parameters of the `_OUTER` series.
- When you optimize error messages, read `message-examples.md`, and combine the templates and Arglists in `error_code.json` with the print format specifications in `rectification-principles.md`.
- Before you commit or review ErrMsg modifications, read `review-checklist.md` for self-checking. Focus on confirming that `error_code.json` is synchronized with `error_code_meta.h`, that the number of `%s` placeholders matches the number of Arglist parameters, that macro invocations do not pass parameters repeatedly, and that the suggestion and ErrMessage texts meet the format requirements.

## Source of Truth

When a specification document is inconsistent with the code, the code takes precedence, and the specification document should be corrected accordingly. The key code sources include:

- `src/dfx/error_manager/error_code.json`
- `src/runtime/core/inc/common/error_code_meta.h`
- `src/runtime/core/inc/base.hpp`
- `src/runtime/core/inc/common/error_message_manage.hpp`
- `src/dfx/error_manager/error_manager.h`

## Maintenance Principles

- This directory carries the official specifications. Skills retain only the process and navigation and do not copy the complete rules.
- When you modify the specifications for error codes, macros, or messages, check whether related documents in this directory need to be updated at the same time. When you add or adjust error codes, focus on checking and updating `error_code.json`, `error_code_meta.h`, and `error-code-guide.md`. When you add or adjust reporting macros, focus on checking and updating `macro-selection-guide.md`.
- `review-checklist.md` targets review and self-check. When you add common problems, parameter calculation rules, or dual-source synchronization requirements, supplement this checklist accordingly.
- When you add or adjust ErrMsg call sites, do not modify business logic, return values, conditional judgments, or normal log levels unless the requirement explicitly requests it.
