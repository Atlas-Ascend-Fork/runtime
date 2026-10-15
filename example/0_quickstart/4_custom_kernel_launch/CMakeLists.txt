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
project(Custom_Kernel_Launch_Sample LANGUAGES ASC CXX)


set(RUN_MODE "npu" CACHE STRING "run mode: npu")
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type Release/Debug (default Debug)" FORCE)


include_directories(${ASCEND_CANN_PACKAGE_PATH}/include)
link_directories(${ASCEND_CANN_PACKAGE_PATH}/lib64)

ascendc_library(custom_kernel STATIC vector_add_kernel.cpp)
target_compile_options(custom_kernel PRIVATE
    $<$<COMPILE_LANGUAGE:ASC>:--npu-arch=${CMAKE_ASC_ARCHITECTURES}>
)

add_executable(main main.cpp)

target_include_directories(main PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)

target_compile_options(main PRIVATE
    -O2 -std=c++17 -D_GLIBCXX_USE_CXX11_ABI=0 -Wall -Werror
)

target_link_libraries(main PRIVATE
    custom_kernel
    ${ASCEND_CANN_PACKAGE_PATH}/lib64/libacl_rt.so
)
