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

import sys
import logging
import argparse
from manifest import Manifest
import search_space # critical for operation registry
import search_space_config

LOGGER = logging.getLogger(__name__)


def main():
    parser = argparse.ArgumentParser(description='code generator cmdline parser')
    parser.add_argument(
        '--kernels',
        type=str,
        default='00_basic_matmul',
        help="Filter kernels by the specified kernel list(comma delimited)",
    )
    parser.add_argument(
        '--workspace-dir',
        type=str,
        help="Workspace directory",
    )
    parser.add_argument(
        '--arch',
        type=str,
        default='AtlasA2',
        help="Target ascend hardware architectures",
    )

    logging.basicConfig(level=logging.INFO)
    args = parser.parse_args()

    LOGGER.debug(f'args.kernels={args.kernels}')
    LOGGER.debug(f'args.workspace_dir={args.workspace_dir}')
    LOGGER.debug(f'args.arch={args.arch}')

    manifest = Manifest(args)
    manifest.generate_code()

    return 0


if __name__ == "__main__":
    sys.exit(main())
