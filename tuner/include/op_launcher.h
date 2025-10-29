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

#ifndef CATLASS_TUNER_OP_RUNNER_H
#define CATLASS_TUNER_OP_RUNNER_H

#include "op_config.h"

namespace Catlass {

enum class OpRunStatus : uint32_t {
    SUCCESS = 0,
    FAILED,
    FATAL,
};

enum class KernelType : uint32_t {
    CACHE_CLEAR = 0,
    OPERATOR,
};

class OpLauncher {
public:
    explicit OpLauncher(const std::shared_ptr<OpConfig>& opConfig, Library::Operation *op, uint32_t aicCoreNum)
        : opConfig_(opConfig), op_(op), aicCoreNum_(aicCoreNum) {}
    OpRunStatus operator()(void* stream, int times = 1, bool sync = true);
    OpRunStatus Init();

private:

    const std::shared_ptr<OpConfig>& opConfig_;
    Library::Operation *op_;
    uint8_t *workspace_{nullptr};
    uint32_t aicCoreNum_;
};

} // namespace Catlass
#endif // CATLASS_TUNER_OP_RUNNER_H
