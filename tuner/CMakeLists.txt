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


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../library/include)

if(NOT DEFINED ENV{ASCEND_HOME_PATH})
    message(FATAL_ERROR "Cannot find ASCEND_HOME_PATH, please run set_env.sh.")
else()
    set(ASCEND_HOME_PATH $ENV{ASCEND_HOME_PATH})
    include_directories(
        ${ASCEND_HOME_PATH}/include
        ${ASCEND_HOME_PATH}/include/aclnn
        ${ASCEND_HOME_PATH}/include/experiment/runtime
        ${ASCEND_HOME_PATH}/include/experiment/msprof
        ${ASCEND_HOME_PATH}/pkg_inc/runtime
        ${ASCEND_HOME_PATH}/pkg_inc/profiling
        ${ASCEND_HOME_PATH}/pkg_inc
        ${CATLASS_INCLUDE_DIR}
        ${CATLASS_INCLUDE_DIR}/../examples/common
    )
    link_directories(
        ${ASCEND_HOME_PATH}/lib64
        ${ASCEND_HOME_PATH}/lib64/../devlib
    )
endif()
add_subdirectory(dfx_kernel)
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(mstuner_catlass ${SOURCES})

add_dependencies(mstuner_catlass
    kernels
    dfx_kernel
)

target_link_libraries(mstuner_catlass PRIVATE
    stdc++fs
    pthread
    tiling_api
    platform
    c_sec
    ascendcl
    ascend_hal
    unified_dlog
    profapi
    dl
    runtime
    ${PROJECT_BUILD_DIR}/lib64/libkernels.so
    dfx_kernel
)

install(TARGETS mstuner_catlass
        DESTINATION bin
        COMPONENT mstuner_catlass)
