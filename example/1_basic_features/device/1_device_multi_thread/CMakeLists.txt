# -----------------------------------------------------------------------------------------------------------
# Copyright (c) 2025 Huawei Technologies Co., Ltd.
# This program is free software, you can redistribute it and/or modify it under the terms and conditions of
# CANN Open Software License Agreement Version 2.0 (the "License").
# Please refer to the License for details. You may not use this file except in compliance with the License.
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
# INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
# See LICENSE in the root of the software repository for the full text of the License.
# -----------------------------------------------------------------------------------------------------------

# CMake lowest version requirement
cmake_minimum_required(VERSION 3.16.0)

# Project information
set(ASCENDC_CMAKE_DIR $ENV{ASCENDC_CMAKE_DIR} CACHE PATH "AscendC CMake directory")
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
project(Runtime_Sample LANGUAGES ASC CXX)

set(RUN_MODE "npu" CACHE STRING "run mode: npu")
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type Release/Debug (default Debug)" FORCE)
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_LIST_DIR}/out" CACHE STRING "path for install()" FORCE)


include_directories(${ASCEND_CANN_PACKAGE_PATH}/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/../../..)

link_directories(${ASCEND_CANN_PACKAGE_PATH}/lib64)

ascendc_library(kernels STATIC
    ../../../kernel_func/kernel_add.cpp
)
target_compile_options(kernels PRIVATE
    $<$<COMPILE_LANGUAGE:ASC>:--npu-arch=${CMAKE_ASC_ARCHITECTURES}>
)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE
    kernels pthread
)
