# Pre-commit Configuration Guide

## Overview

pre-commit is a Git hooks framework that automatically runs code checking and formatting tools during `git commit`. This project has configured the following checks:

| Hook | Function | Description |
|------|------|------|
| **clang-format** | C/C++ code formatting | Automatically formats code to keep the style consistent |
| **OAT Check** | Open-source compliance check | Detects license headers and forbids binary file commits |

## Environment Requirements

- **Git**: 2.0+
- **Python**: 3.8+
- **clang-format**: 14.0+ (code formatting)

## Installation Steps

### 1. Install pre-commit

```bash
# Method 1: Use pip
pip install pre-commit

# Method 2: Use the system package manager (Ubuntu/Debian)
sudo apt install pre-commit
```

### 2. Install Dependency Tools

```bash
# Ubuntu/Debian
sudo apt install clang-format

# macOS
brew install clang-format
```

### 3. Install Git Hooks in the Project Path

```bash
cd /path/to/runtime
pre-commit install
```

After the installation succeeds, the following information is displayed:
```
pre-commit installed at .git/hooks/pre-commit
```

## Usage

### Automatic Check (Recommended)

Each time you run `git commit`, pre-commit automatically runs the checks:

```bash
git add .
git commit -m "your commit message"
```

Example output:
```
clang-format.............................................................Passed
OAT Compliance Check (Python Edition).....................................Passed
```

### Running Checks Manually

```bash
# Run all checks
pre-commit run

# Run specific types of checks
pre-commit run clang-format
pre-commit run oat-check

# Check all files (not limited to the staging area)
pre-commit run --all-files
```

### Skipping Checks (Emergency Cases)

```bash
git commit --no-verify -m "emergency fix"
```

> **Note**: Use this option only in emergency cases. The normal development process must ensure that all checks pass.

## Check Item Descriptions

### 1. clang-format

This tool automatically formats C/C++ code according to the project `.clang-format` configuration:

- **Indentation**: 4 spaces
- **Column width**: 120 characters
- **Braces**: Line break for function definitions, same line for control statements
- **Pointer alignment**: Right-aligned (`int *ptr`)


### 2. OAT Compliance Check

OAT (Open Source Audit Tool) checks open-source compliance:

| Check Item | Description |
|--------|------|
| License header check | Ensures that source files contain the CANN License header |
| Binary file check | Forbids binary file commits |
| Archive file check | Forbids commits of archive files such as zip/tar |


OAT uses the remote Python hook provided by the [compliance](https://gitcode.com/HiAgent/compliance) repository. The version is fixed by `rev: v1.0.6` in `.pre-commit-config.yaml`. During the first run, pre-commit automatically clones the repository, installs OAT and its dependencies in an isolated Python virtual environment, and checks the passed-in files through `oat-precommit`.

The `OAT.xml` file in the repository root directory configures the compliance rules of this project. You do not need to copy or maintain local check scripts.

## FAQ

### Q1: The OAT Check Is Slow During the First Commit

**Cause**: The first run needs to download the remote hook and install the Python environment and dependencies. The environment must be able to access GitCode and Python package sources.

**Solution**: Wait for the first installation to complete. Subsequent commits reuse the environment cached by pre-commit.


## Related Documents

- [pre-commit official documentation](https://pre-commit.com/)
- [clang-format configuration](https://clang.llvm.org/docs/ClangFormatStyleOptions.html)
- [OAT remote hook](https://gitcode.com/HiAgent/compliance)
- [Guide for Integrating pre-commit into the Code Repository](https://gitcode.com/cann/infrastructure/blob/main/docs/SC/pre-commit/pre-commit%E9%85%8D%E7%BD%AE%E6%8C%87%E5%AF%BC%E4%B9%A6.md)
