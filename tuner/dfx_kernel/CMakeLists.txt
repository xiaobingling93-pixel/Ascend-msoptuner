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


add_compile_definitions(TILING_KEY_VAR)
add_compile_options(--cce-aicore-arch=dav-c220)
file(GLOB DFX_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
set_source_files_properties(${DFX_SRC} PROPERTIES LANGUAGE ASCEND)
add_library(dfx_kernel STATIC ${DFX_SRC})
