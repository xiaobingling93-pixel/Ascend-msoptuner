# -------------------------------------------------------------------------
# This file is part of the MindStudio project.
# Copyright (c) 2025 Huawei Technologies Co.,Ltd.
#
# MindStudio is licensed under Mulan PSL v2.
# You can use this software according to the terms and conditions of the Mulan PSL v2.
# You may obtain a copy of Mulan PSL v2 at:
#
#          http://license.coscl.org.cn/MulanPSL2
#
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
# EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
# MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
# See the Mulan PSL v2 for more details.
# -------------------------------------------------------------------------

if ("${LIBRARY_KERNELS}" STREQUAL "")
    message(FATAL_ERROR "LIBRARY_KERNELS is not allowed to be empty")
else()
    message(STATUS "LIBRARY_KERNELS=${LIBRARY_KERNELS}")
endif()

set(ARCH "AtlasA2")

find_package(Python COMPONENTS Interpreter REQUIRED)
execute_process(
    COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/scripts/code_generator.py
        --kernels ${LIBRARY_KERNELS}
        --workspace-dir ${CMAKE_CURRENT_BINARY_DIR}
        --arch ${ARCH}
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    RESULT_VARIABLE LIBRARY_CODE_GENERATION_RESULT
    OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/library_code_generation.log
    ERROR_FILE ${CMAKE_CURRENT_BINARY_DIR}/library_code_generation.log
)

if(NOT LIBRARY_CODE_GENERATION_RESULT EQUAL 0)
    message(FATAL_ERROR "Failed to generate catlass library operator code. "
                        "See details in ${CMAKE_CURRENT_BINARY_DIR}/library_code_generation.log")
endif()

file(GLOB_RECURSE LIBRARY_GENERATED_SRCS CONFIGURE_DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/generated/*.cpp)

message(STATUS "Catlass library operator code was generated successfully.")

list(APPEND LIBRARY_GENERATED_SRCS src/manifest.cpp)

set_source_files_properties(${LIBRARY_GENERATED_SRCS} PROPERTIES LANGUAGE ASCEND)

add_compile_options(
    $<$<COMPILE_LANGUAGE:ASCEND>:-Wno-macro-redefined>
    $<$<COMPILE_LANGUAGE:ASCEND>:-Wno-ignored-attributes>

    "SHELL:$<$<COMPILE_LANGUAGE:ASCEND>:-mllvm -cce-aicore-stack-size=0x8000>"
    "SHELL:$<$<COMPILE_LANGUAGE:ASCEND>:-mllvm -cce-aicore-function-stack-size=0x8000>"
    "SHELL:$<$<COMPILE_LANGUAGE:ASCEND>:-mllvm -cce-aicore-record-overflow=true>"
    "SHELL:$<$<COMPILE_LANGUAGE:ASCEND>:-mllvm -cce-aicore-addr-transform>"
    "SHELL:$<$<COMPILE_LANGUAGE:ASCEND>:-mllvm -cce-aicore-dcci-insert-for-scalar=false>"
)

add_compile_definitions(CATLASS_ARCH=2201)
add_compile_definitions(L2_CACHE_HINT)
add_compile_definitions(TILING_KEY_VAR)

add_library(kernels SHARED
    ${LIBRARY_GENERATED_SRCS}
    src/manifest.cpp
)

set(AICORE_ARCH dav-c220)
target_compile_options(kernels PRIVATE $<$<COMPILE_LANGUAGE:ASCEND>:--cce-aicore-arch=${AICORE_ARCH}>)

set_target_properties(kernels PROPERTIES POSITION_INDEPENDENT_CODE ON)

if(NOT DEFINED ENV{ASCEND_HOME_PATH})
    message(FATAL_ERROR "Cannot find ASCEND_HOME_PATH, please run set_env.sh.")
else()
    set(ASCEND_HOME_PATH $ENV{ASCEND_HOME_PATH})
endif()

target_include_directories(kernels PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CATLASS_INCLUDE_DIR}
    ${CATLASS_INCLUDE_DIR}/../examples/common
    ${_CMAKE_ASCEND_HOME_PATH}/include

    ${ASCEND_HOME_PATH}/include
)
install(TARGETS kernels
        DESTINATION lib64
        COMPONENT kernels)
