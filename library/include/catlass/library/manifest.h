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

#ifndef CATLASS_LIBRARY_MANIFEST_H
#define CATLASS_LIBRARY_MANIFEST_H

#include <vector>

#include "catlass/library/operation.h"

#include "catlass/status.hpp"

namespace Catlass {
namespace Library {

class Manifest {
public:
    Manifest() = default;

    Status Initialize();
    void Append(Operation *operation_ptr);
    std::vector<Operation *> const &GetOperations() const;

private:
    std::vector<Operation *> operationList_;
};

}
}

#endif // CATLASS_LIBRARY_MANIFEST_H
