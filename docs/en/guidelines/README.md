# Runtime R&D Specifications and Contribution Guide

This directory consolidates the software design template, coding guidelines, test case specifications, and code review rules of the Runtime repository. Developers and contributors in the repository use them as a unified reference during design, coding, testing, and review.

## Contents

| Document | Content | Applicable Scenario |
|------|------|----------|
| [design_document_template.md](design_document_template.md) | Runtime design document template, covering APIs, architecture, document synchronization, and DT check items | When you produce design schemes, API designs, or feature designs |
| [coding-guidelines.md](coding-guidelines.md) | Unified coding guidelines that you must follow when implementing Runtime code | Daily development, self-check, `/runtime-code-review`, and PR review |
| [ut-coding-guidelines.md](ut-coding-guidelines.md) | Mandatory specifications for Runtime UT code, supplementing constraints at the test implementation level | When you write, modify, or review UT code |
| [Runtime Error Message Development Guide](error_message_guide/README.md) | Unified specifications for Runtime/ACL error message rectification and review, covering error code selection, ErrMsg reporting macro selection, error message text, and reporting boundaries | When you add or rectify ErrMsg reporting, select EE/EH error codes, optimize error message text, or perform an ErrMsg self-check or review |
| [DT Case Development Guide](dt_guide/README.md) | Organization, onboarding process, and general specifications of UT/ST cases in the Runtime repository | When you add or modify tests |
| [How to Use pre-commit](pre-commit_guide.md) | Runtime pre-commit configuration and usage instructions, covering clang-format formatting and the OAT compliance check | Install and run it before you commit code |

If you need to supplement the Runtime test specifications, maintain them in this directory first. This approach prevents rules from being scattered across scripts, skills, and temporary documents.
