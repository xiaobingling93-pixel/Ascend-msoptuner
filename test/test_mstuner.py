
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

import os
import subprocess
import shutil
import unittest


class MsTunerCatlassTest(unittest.TestCase):

    CATLASS_OUTPUT_BINARY_PATH = os.path.join(os.path.dirname(
        os.path.abspath(__file__)),"..", "build", "bin"
    )
    CATLASS_OUTPUT_LIB_PATH = os.path.join(os.path.dirname(
        os.path.abspath(__file__)), "..","build", "lib64"
    )
    MSTUNER_TEST_TEMP_PATH = os.path.join(os.path.dirname(
        os.path.abspath(__file__)), "mstuner_test_temp"
    )

    @classmethod
    def setUpClass(cls):
        # create temp dir for mstuner_test
        if not os.path.exists(MsTunerCatlassTest.MSTUNER_TEST_TEMP_PATH):
            os.mkdir(MsTunerCatlassTest.MSTUNER_TEST_TEMP_PATH)

        # add ./output/lib64 to LD_LIBRARY_PATH
        if 'LD_LIBRARY_PATH' in os.environ:
            os.environ['LD_LIBRARY_PATH'] = MsTunerCatlassTest.CATLASS_OUTPUT_LIB_PATH + \
                ':' + os.environ['LD_LIBRARY_PATH']
        else:
            os.environ['LD_LIBRARY_PATH'] = MsTunerCatlassTest.CATLASS_OUTPUT_LIB_PATH

    @classmethod
    def tearDownClass(cls):
        # remove temp dir for mstuner_test
        if os.path.exists(MsTunerCatlassTest.MSTUNER_TEST_TEMP_PATH):
            shutil.rmtree(MsTunerCatlassTest.MSTUNER_TEST_TEMP_PATH, ignore_errors=True)


    def compile_lib_catlass_kernels(self, kernel_name: str):
        """编译指定CatLASSS内核库"""
        macro_str = '-DCATLASS_LIBRARY_KERNELS=' + kernel_name
        
        # 获取项目根目录（test/在项目根目录下）
        project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

        build_sh_path = os.path.join(
            project_root,
            'test',
            'catlass_test',
            'catlass',
            'scripts',
            'build.sh'
        )
        build_dir = os.path.join(project_root)
        if not os.path.exists(build_sh_path):
            raise FileNotFoundError(f"Build script not found at: {build_sh_path}")
        if not os.path.exists(build_dir):
            os.makedirs(build_dir, exist_ok=True)

        compile_cmd = [
            'bash',
            build_sh_path,
            '--clean',
            macro_str,
            'mstuner_catlass'
        ]
        
        try:
            result = subprocess.run(
                compile_cmd,
                cwd=build_dir,
                capture_output=True,
                text=True,
                timeout=600
            )
            if result.returncode != 0:
                print(f"Build failed with output:\n{result.stdout}\nError:\n{result.stderr}")
            return result
            
        except subprocess.TimeoutExpired as e:
            print(f"Build timed out after {e.timeout} seconds")
            raise


    def run_one_case(self, case):
        case_name = case[0]
        case_args = case[1:]
        csv_file_name = case_name + '.csv'
        csv_file_path = os.path.join(MsTunerCatlassTest.MSTUNER_TEST_TEMP_PATH, csv_file_name)

        result = self.compile_lib_catlass_kernels(case_name)
        if len(result.stdout) != 0:
            self.assertIn("No npu-smi detected", result.stdout)
            return
        self.assertEqual(
            result.returncode, 0,
            f'build libcatlass_kernels.so for {case_name} failed: {result.stderr}'
        )

    # add custom test cases below
    mstuner_cases = [
        ['00_basic_matmul', '--m=256', '--n=512', '--k=1024'],
        ['02_grouped_matmul_slice_m', '--m=512', '--n=1024', '--k=2048', '--group_count=128'],
        ['06_optimized_matmul_padding_ab', '--m=555', '--n=322', '--k=1111'],
        ['06_optimized_matmul_padding_a_only', '--m=655', '--n=256', '--k=1111'],
        ['06_optimized_matmul_padding_b_only', '--m=555', '--n=322', '--k=1024'],
        ['06_optimized_matmul_without_padding', '--m=512', '--n=256', '--k=1024'],
        ['08_grouped_matmul', '--m=512', '--n=1024', '--k=2048', '--group_count=128'],
    ]

    def test_all_cases(self):
        for case in self.mstuner_cases:
            self.run_one_case(case)


if __name__ == '__main__':
    unittest.main()