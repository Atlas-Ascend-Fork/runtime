# -----------------------------------------------------------------------------------------------------------
# Copyright (c) 2026 Huawei Technologies Co., Ltd.
# This program is free software, you can redistribute it and/or modify it under the terms and conditions of
# CANN Open Software License Agreement Version 2.0 (the "License").
# Please refer to the License for details. You may not use this file except in compliance with the License.
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
# INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
# See LICENSE in the root of the software repository for the full text of the License.
# -----------------------------------------------------------------------------------------------------------
find_package(Python3 3.8 REQUIRED COMPONENTS Interpreter)

# This Host target needs a working ctypes extension, without SDK Python paths.
# Keep every ABI assertion active, even if the newest installed Python is broken.
set(SLOG_PYTHON_CANDIDATES "${Python3_EXECUTABLE}")
foreach(SLOG_PYTHON_NAME IN ITEMS python3 python3.14 python3.13 python3.12 python3.11 python3.10 python3.9 python3.8)
    unset(SLOG_PYTHON_PROGRAM)
    unset(SLOG_PYTHON_PROGRAM CACHE)
    find_program(SLOG_PYTHON_PROGRAM NAMES "${SLOG_PYTHON_NAME}")
    if(SLOG_PYTHON_PROGRAM)
        list(APPEND SLOG_PYTHON_CANDIDATES "${SLOG_PYTHON_PROGRAM}")
    endif()
endforeach()
list(REMOVE_DUPLICATES SLOG_PYTHON_CANDIDATES)

unset(SLOG_PYTHON_EXECUTABLE)
foreach(SLOG_PYTHON_CANDIDATE IN LISTS SLOG_PYTHON_CANDIDATES)
    execute_process(
        COMMAND "${CMAKE_COMMAND}" -E env --unset=PYTHONHOME --unset=PYTHONPATH --unset=LD_LIBRARY_PATH
            "${SLOG_PYTHON_CANDIDATE}" -c "import ctypes; import sys; assert sys.version_info >= (3, 8)"
        RESULT_VARIABLE SLOG_PYTHON_PROBE_RESULT
        OUTPUT_QUIET
        ERROR_QUIET
    )
    if(SLOG_PYTHON_PROBE_RESULT STREQUAL "0")
        set(SLOG_PYTHON_EXECUTABLE "${SLOG_PYTHON_CANDIDATE}")
        break()
    endif()
endforeach()
if(NOT SLOG_PYTHON_EXECUTABLE)
    message(FATAL_ERROR "slog_python_ut requires a Python 3.8+ interpreter with a working ctypes module")
endif()
message(STATUS "slog_python_ut Python interpreter: ${SLOG_PYTHON_EXECUTABLE}")

add_custom_target(slog_python_ut
    COMMAND "${CMAKE_COMMAND}" -E env --unset=PYTHONHOME --unset=PYTHONPATH --unset=LD_LIBRARY_PATH
        "${SLOG_PYTHON_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/test_ascend_log.py"
    WORKING_DIRECTORY "${TOP_DIR}"
    COMMENT "Running AscendLog Python ABI unit tests"
    VERBATIM
)
