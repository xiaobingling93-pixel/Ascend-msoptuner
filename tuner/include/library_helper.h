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

#ifndef CATLASS_TUNER_LIBRARY_HELPER_H
#define CATLASS_TUNER_LIBRARY_HELPER_H

#include <unordered_map>
#include "catlass/library/operation.h"
#include "catlass/layout/matrix.hpp"

namespace Catlass {

class LibraryHelper {
public:
    using DataType = Library::DataType;
    using LayoutType = Library::LayoutType;

    static size_t GetDataTypeSize(DataType dataType);
    static size_t GetLayoutSize(LayoutType layoutType);
    static std::string_view GetDataTypeStr(DataType dataType);
    static std::string_view GetLayoutStr(LayoutType layoutType);
    static DataType GetDataTypeEnum(std::string_view str);
    static LayoutType GetLayoutEnum(std::string_view str);
    static void ConstructLayout(LayoutType layoutType, DataType dataType, uint32_t a, uint32_t b, uint8_t *data);
};

}
#endif // CATLASS_TUNER_LIBRARY_HELPER_H
