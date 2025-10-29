#!/usr/bin/env python3
# -*- coding: utf-8 -*-
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

import library
import search_space
from manifest import OperationRegistry


"""
If more customization of search space configuration is required, you
need unregister this configuration by COMMENTING this line below:

@OperationRegistry.register_high_priority('00_basic_matmul')

More customizable configurations are provided in search_space.py
in form of functions that are marked by @OperationRegistry.register
e.g. register_gemm_00_basic_matmul_operation
Pruning strategies and parameter combination strategies are customizable.
"""


@OperationRegistry.register_high_priority('00_basic_matmul')
def register(manifest):
    config = search_space.SearchSpaceConfiguration(
        kernel_type='00_basic_matmul',

        data_type_a=library.DataType.fp16,
        data_type_b=library.DataType.fp16,
        data_type_c=library.DataType.fp16,

        layout_a=library.LayoutType.RowMajor,
        layout_b=library.LayoutType.RowMajor,
        layout_c=library.LayoutType.RowMajor,

        l1_tile_m_range=(32, 128),  # min and max of a range are set here
        l1_tile_n_range=(128, 256),
        l1_tile_k_range=(128, 256),

        block_swizzle='Gemm::Block::GemmIdentityBlockSwizzle<3, 0>',
    )

    search_space.register_custom_kernel(config, manifest)
