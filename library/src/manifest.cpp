/* -------------------------------------------------------------------------
 * This file is part of the MindStudio project.
 * Copyright (c) 2025 Huawei Technologies Co.,Ltd.
 *
 * MindStudio is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *
 *          http://license.coscl.org.cn/MulanPSL2
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 * ------------------------------------------------------------------------- */

#include "catlass/library/manifest.h"

namespace Catlass {
namespace Library {

using namespace Catlass;

void RegisterAllKernels(Manifest &manifest);

Status Manifest::Initialize()
{
    RegisterAllKernels(*this);
    return Status::kSuccess;
}

void Manifest::Append(Operation *op)
{
    operationList_.emplace_back(op);
}

std::vector<Operation *> const &Manifest::GetOperations() const
{
    return operationList_;
}

}
}
