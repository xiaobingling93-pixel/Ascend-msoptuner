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

#ifndef CATLASS_TUNER_CATLASS_TUNER_H
#define CATLASS_TUNER_CATLASS_TUNER_H

#include <condition_variable>
#include <queue>
#include "catlass/library/manifest.h"
#include "profiler.h"
#include "metrics.h"
#include "op_launcher.h"

namespace Catlass {

class CatlassTuner {
public:
    explicit CatlassTuner(CommandLineParser parser);
    ~CatlassTuner();
    void Run();

private:
    bool InitOperators(OpConfigPool &pool);
    void UpdateMetrics(bool readAll = false);
    void Synchronize();
    OpRunStatus RunOp(const std::shared_ptr<OpConfig>& opConfig, Library::Operation *op, uint32_t aicCoreNum);

    aclrtStream stream_{nullptr};
    Library::Manifest manifest_{};
    CommandLineParser parser_{};
    ProfileDataHandler profileHandler_{};
    Metrics metrics_{};
    std::queue<std::vector<KernelType>> kernelsQueue_;
    int32_t deviceId_{0};
    std::vector<double> durations_{};
};

} // namespace Catlass
#endif // CATLASS_TUNER_CATLASS_TUNER_H
