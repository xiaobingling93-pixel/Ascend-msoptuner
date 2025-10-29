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

cmake_minimum_required(VERSION 3.22)
project(mstuner NONE)
get_filename_component(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} ABSOLUTE)
set(PROJECT_BUILD_DIR "${CMAKE_BINARY_DIR}" CACHE PATH "Root build directory")
if(
    (CMAKE_INSTALL_PREFIX STREQUAL "/usr/local") 
    OR (CMAKE_INSTALL_PREFIX STREQUAL "/usr") 
    OR (NOT CMAKE_INSTALL_PREFIX)
)
    set(CMAKE_INSTALL_PREFIX "${ROOT_DIR}/output" CACHE STRING "Installation directory" FORCE)
    message(STATUS "No valid install prefix selected, defaulting to ${CMAKE_INSTALL_PREFIX}")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BUILD_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BUILD_DIR}/lib64)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BUILD_DIR}/lib64)

if(NOT DEFINED LIBRARY_KERNELS)
  set(LIBRARY_KERNELS "basic_matmul")
endif()
option(BUILD_TESTS "Build test binaries" OFF)

if(BUILD_TESTS)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(ASCEND_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/test/catlass_test/catlass/cmake/modules)
    list(APPEND CMAKE_MODULE_PATH ${ASCEND_CMAKE_PATH})
    set(CATLASS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test/catlass_test/catlass/include)
endif()

enable_language(ASCEND CXX)

if(NOT DEFINED CMAKE_BUILD_TYPE OR NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE "Release")
endif()


add_subdirectory(library)
add_subdirectory(tuner)
