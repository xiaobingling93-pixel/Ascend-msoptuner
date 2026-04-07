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


class KernelGroupFile:
    def __init__(self, file_name):
        self.file_name = file_name
        self.operation_headers = set()
        self.kernel_instance_headers = set()
        self.custom_common_decls = set()
        self.body_src = []

        self.header_template = """
{operation_headers}

{kernel_instance_headers}

namespace Catlass {{
namespace Library {{
using namespace Catlass;

{custom_common_decls}
"""

        self.tail = """
}
}
"""

    def add_headers(self, headers):
        self.operation_headers.add(headers)

    def add_instance(self, custom_header, custom_common_decls, body):
        self.kernel_instance_headers.add(custom_header)
        self.custom_common_decls.add(custom_common_decls)
        self.body_src.append(body)

    def write_in_dir(self, workspace_dir):
        operation_headers = ''
        for header in self.operation_headers:
            operation_headers += header + '\n'
        kernel_instance_headers = ''
        for header in self.kernel_instance_headers:
            kernel_instance_headers += header + '\n'
        custom_common_decls_src = ''
        for decl in self.custom_common_decls:
            custom_common_decls_src += decl + '\n'
        headers = self.header_template.format(
            operation_headers=operation_headers,
            kernel_instance_headers=kernel_instance_headers,
            custom_common_decls=custom_common_decls_src
        )

        path = os.path.join(workspace_dir, self.file_name)
        fd = os.open(path, os.O_CREAT | os.O_WRONLY, 0o640)
        with os.fdopen(fd, 'w') as f:
            f.write(headers)
            for body in self.body_src:
                f.write(body)
            f.write(self.tail)
