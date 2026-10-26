# -----------------------------------------------------------------------------------------------------------
# Copyright (c) 2025 Huawei Technologies Co., Ltd.
# This program is free software, you can redistribute it and/or modify it under the terms and conditions of
# CANN Open Software License Agreement Version 2.0 (the "License").
# Please refer to the License for details. You may not use this file except in compliance with the License.
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
# INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
# See LICENSE in the root of the software repository for the full text of the License.
# -----------------------------------------------------------------------------------------------------------
add_subdirectory(runtime)
add_subdirectory(runtime_c/testcase)
#add_subdirectory(driver-stub)
# Link the lightweight handler into every Runtime UT executable, including platform
# subdirectories. It activates only when the native supervisor passes a channel.
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_library(runtime_ut_crash_handler OBJECT diagnostics/crash_handler.cc)
    function(enable_runtime_ut_crash_diagnostics directory)
        get_property(targets DIRECTORY "${directory}" PROPERTY BUILDSYSTEM_TARGETS)
        foreach(target IN LISTS targets)
            get_target_property(type "${target}" TYPE)
            if(type STREQUAL "EXECUTABLE")
                target_sources("${target}" PRIVATE $<TARGET_OBJECTS:runtime_ut_crash_handler>)
            endif()
        endforeach()
        get_property(children DIRECTORY "${directory}" PROPERTY SUBDIRECTORIES)
        foreach(child IN LISTS children)
            enable_runtime_ut_crash_diagnostics("${child}")
        endforeach()
    endfunction()
    enable_runtime_ut_crash_diagnostics("${CMAKE_CURRENT_SOURCE_DIR}")
endif()
