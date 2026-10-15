# -----------------------------------------------------------------------------------------------------------
# Copyright (c) 2026 Huawei Technologies Co., Ltd.
# This program is free software, you can redistribute it and/or modify it under the terms and conditions of
# CANN Open Software License Agreement Version 2.0 (the "License").
# Please refer to the License for details. You may not use this file except in compliance with the License.
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
# INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
# See LICENSE in the root of the software repository for the full text of the License.
# -----------------------------------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.16.0)

set(ASCENDC_CMAKE_DIR $ENV{ASCENDC_CMAKE_DIR} CACHE PATH "AscendC CMake directory")
set(RUN_MODE "npu" CACHE STRING "cpu/sim/npu")
set(SOC_VERSION $ENV{SOC_VERSION} CACHE STRING "Ascend SoC version")
set(ASCEND_CANN_PACKAGE_PATH $ENV{ASCEND_HOME_PATH} CACHE PATH "CANN installation path")
string(TOLOWER "${SOC_VERSION}" SOC_VERSION_LOWER)
if(SOC_VERSION_LOWER MATCHES "^ascend(950|350)")
    set(CMAKE_ASC_ARCHITECTURES dav-3510)
elseif(SOC_VERSION_LOWER MATCHES "^ascend910(b|_93)")
    set(CMAKE_ASC_ARCHITECTURES dav-2201)
else()
    message(FATAL_ERROR "Unsupported SOC_VERSION: ${SOC_VERSION}")
endif()

list(APPEND CMAKE_MODULE_PATH "${ASCENDC_CMAKE_DIR}/asc_modules")
find_package(ASC REQUIRED)
project(Binary_Get_Function_Count_Sample LANGUAGES ASC C CXX)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type Release/Debug" FORCE)
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_LIST_DIR}/out" CACHE PATH "Install path" FORCE)

ascendc_fatbin_library(custom_kernels kernel/custom.cpp)
target_compile_options(custom_kernels PRIVATE
    $<$<COMPILE_LANGUAGE:ASC>:--npu-arch=${CMAKE_ASC_ARCHITECTURES}>
)

set(CANN_SEARCH_ROOTS
    "${ASCEND_CANN_PACKAGE_PATH}"
    "${ASCEND_CANN_PACKAGE_PATH}/runtime"
    "${ASCEND_CANN_PACKAGE_PATH}/aarch64-linux"
    "${ASCEND_CANN_PACKAGE_PATH}/x86_64-linux"
)

find_path(ACL_INCLUDE_DIR
    NAMES acl/acl.h
    PATHS ${CANN_SEARCH_ROOTS}
    PATH_SUFFIXES include
    REQUIRED
)

find_library(ACL_RT_LIBRARY
    NAMES acl_rt
    PATHS ${CANN_SEARCH_ROOTS}
    PATH_SUFFIXES lib64 devlib devlib/linux/aarch64 devlib/linux/x86_64
    REQUIRED
)

add_executable(binary_get_function_count main.cpp)

target_include_directories(binary_get_function_count PRIVATE
    "${ACL_INCLUDE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../.."
)

target_compile_options(binary_get_function_count PRIVATE
    -O2
    -Wall
    -Wextra
    -Werror
    -D_GLIBCXX_USE_CXX11_ABI=0
)

target_link_libraries(binary_get_function_count PRIVATE
    "${ACL_RT_LIBRARY}"
    dl
    pthread
)

install(TARGETS binary_get_function_count
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)
install(TARGETS custom_kernels LIBRARY DESTINATION "fatbin/custom_kernels")
