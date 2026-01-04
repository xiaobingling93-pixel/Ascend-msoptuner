#!/usr/bin/python3
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

import os
import sys
import logging
import subprocess
import multiprocessing
import argparse


def exec_cmd(cmd):
    result = subprocess.run(cmd, capture_output=False, text=True, timeout=3600)
    if result.returncode != 0:
        logging.error("execute command %s failed, please check the log", " ".join(cmd))
        sys.exit(result.returncode)


def execute_build(build_path, cmake_cmd, make_cmd):
    if not os.path.exists(build_path):
        os.makedirs(build_path, mode=0o755)
    os.chdir(build_path)
    exec_cmd(cmake_cmd)
    exec_cmd(make_cmd)


def execute_test(build_path, test_type):
    os.chdir(build_path)
    if test_type == "python":
        test_script_path = os.path.join(os.path.dirname(build_path), "test", "test_mstuner.py")
        if os.path.exists(test_script_path):
            os.chdir(os.path.dirname(test_script_path))
            exec_cmd([sys.executable, os.path.basename(test_script_path)])
        else:
            logging.error("Test script %s not found", test_script_path)
            sys.exit(1)


def is_build_complete(build_path):
    required_files = [
        os.path.join(build_path, "lib64", "libkernels.so"),
        os.path.join(build_path, "bin", "mstuner_catlass")
    ]
    for file_path in required_files:
        if not os.path.exists(file_path):
            return False
    return True


def create_arg_parser():
    parser = argparse.ArgumentParser(description='Build script with optional testing')
    parser.add_argument('command', nargs='*', default='[]', 
                       choices=['[]', 'local', 'test'],
                       help='Command to execute (python build.py [ |local|test]):\n'
                            '  (default): normal build\n'
                            '  local: local-only build without updating submodules\n'
                            '  test: build and run tests')
    parser.add_argument('-r', '--revision',
                        help="Build with specific revision or tag")
    return parser


if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    parser = create_arg_parser()
    args = parser.parse_args()

    current_dir = os.path.abspath(os.path.dirname(os.path.realpath(__file__)))
    os.chdir(current_dir)
    
    cpu_cores = multiprocessing.cpu_count()
    build_path = os.path.join(current_dir, "build")

    should_check_build = ('test' in args.command)
    skip_build = should_check_build and is_build_complete(build_path)

    cmake_cmd = ["cmake", "..", "-DBUILD_TESTS=ON"]
    make_cmd = ["make", "-j", str(cpu_cores)]

    if 'local' not in args.command:
        from download_dependencies import update_submodule
        update_submodule(args)

    if not skip_build:
        execute_build(build_path, cmake_cmd, make_cmd)
    else:
        logging.info("Build artifacts already exist, skipping build step.")

    if 'test' in args.command:
        execute_test(build_path, "python")
