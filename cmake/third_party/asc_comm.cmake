# -----------------------------------------------------------------------------------------------------------
# Copyright (c) 2026 Huawei Technologies Co., Ltd.
# This program is free software, you can redistribute it and/or modify it under the terms and conditions of
# CANN Open Software License Agreement Version 2.0 (the "License").
# Please refer to the License for details. You may not use this file except in compliance with the License.
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
# INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
# See LICENSE in the root of the software repository for the full text of the License.
# -----------------------------------------------------------------------------------------------------------

set(ASC_COMM_TAG_ID cacb3ec39b70552231f534727adf5519eafd732b)

set(ASC_COMM_SOURCE_DIR "" CACHE PATH "asc-comm source directory")
if(NOT ASC_COMM_SOURCE_DIR)
    set(_asc_comm_candidates
        "${RUNTIME_DIR}/../asc-comm"
        "${RUNTIME_DIR}/../asc/asc-comm"
    )
    foreach(_candidate IN LISTS _asc_comm_candidates)
        if(EXISTS "${_candidate}/src/aicpu/CMakeLists.txt")
            get_filename_component(ASC_COMM_SOURCE_DIR "${_candidate}" REALPATH)
            break()
        endif()
    endforeach()
endif()

if(NOT ASC_COMM_SOURCE_DIR AND EXISTS "${CANN_3RD_LIB_PATH}/asc-comm")
    get_filename_component(ASC_COMM_SOURCE_DIR "${CANN_3RD_LIB_PATH}/asc-comm" REALPATH)
    execute_process(
        COMMAND git checkout ${ASC_COMM_TAG_ID}
        WORKING_DIRECTORY ${ASC_COMM_SOURCE_DIR}
        RESULT_VARIABLE ASC_COMM_CHECKOUT_RESULT
        ERROR_VARIABLE ASC_COMM_CHECKOUT_ERROR
    )
    if(ASC_COMM_CHECKOUT_RESULT)
        message(FATAL_ERROR "asc-comm git checkout failed: ${ASC_COMM_CHECKOUT_ERROR}")
    endif()
endif()

if(NOT ASC_COMM_SOURCE_DIR)
    include(FetchContent)
    if(EXISTS "${CMAKE_BINARY_DIR}/_deps/asc_comm-subbuild")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/asc_comm-subbuild")
    endif()
    FetchContent_Declare(
        asc_comm
        GIT_REPOSITORY https://gitcode.com/cann/asc-comm.git
        GIT_TAG ${ASC_COMM_TAG_ID}
        GIT_PROGRESS TRUE
        SOURCE_DIR ${CANN_3RD_LIB_PATH}/asc-comm
    )
    FetchContent_GetProperties(asc_comm)
    if(NOT asc_comm_POPULATED)
        FetchContent_Populate(asc_comm)
    endif()
    set(ASC_COMM_SOURCE_DIR "${asc_comm_SOURCE_DIR}")
endif()

if(NOT ASC_COMM_SOURCE_DIR OR
    NOT EXISTS "${ASC_COMM_SOURCE_DIR}/src/aicpu/CMakeLists.txt")
    message(FATAL_ERROR "asc-comm source not found; set ASC_COMM_SOURCE_DIR")
endif()

get_filename_component(ASC_COMM_SOURCE_DIR "${ASC_COMM_SOURCE_DIR}" REALPATH)
message(STATUS "[asc-comm] found source dir: ${ASC_COMM_SOURCE_DIR}")

add_subdirectory("${ASC_COMM_SOURCE_DIR}/src/aicpu" "${CMAKE_BINARY_DIR}/asc-comm-build")
if(NOT TARGET asccomm_aicpu)
    message(FATAL_ERROR "asc-comm target asccomm_aicpu not found")
endif()
