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

#ifndef CATLASS_LIBRARY_LIBRARY_UTILS_H
#define CATLASS_LIBRARY_LIBRARY_UTILS_H

#include "catlass/library/operation.h"

namespace Catlass {
namespace Library {


template <typename T> struct DataTypeMap {};

template <> struct DataTypeMap<uint8_t> {
    static DataType const typeId = DataType::U8;
};

template <> struct DataTypeMap<int8_t> {
    static DataType const typeId = DataType::Int8;
};

template <> struct DataTypeMap<int32_t> {
    static DataType const typeId = DataType::Int32;
};

template <> struct DataTypeMap<float16_t> {
    static DataType const typeId = DataType::Fp16;
};

template <> struct DataTypeMap<bfloat16_t> {
    static DataType const typeId = DataType::Bf16;
};

template <> struct DataTypeMap<float32_t> {
    static DataType const typeId = DataType::Fp32;
};

template <typename T> struct LayoutMap {};

template <> struct LayoutMap<Catlass::layout::RowMajor> {
    static LayoutType const typeId = LayoutType::RowMajor;
};

template <> struct LayoutMap<Catlass::layout::ColumnMajor> {
    static LayoutType const typeId = LayoutType::ColumnMajor;
};

template <> struct LayoutMap<Catlass::layout::nZ> {
    static LayoutType const typeId = LayoutType::nZ;
};

template <> struct LayoutMap<Catlass::layout::zN> {
    static LayoutType const typeId = LayoutType::zN;
};

template <> struct LayoutMap<Catlass::layout::zZ> {
    static LayoutType const typeId = LayoutType::zZ;
};

template <> struct LayoutMap<Catlass::layout::PaddingRowMajor> {
    static LayoutType const typeId = LayoutType::PaddingRowMajor;
};

template <> struct LayoutMap<Catlass::layout::PaddingColumnMajor> {
    static LayoutType const typeId = LayoutType::PaddingColumnMajor;
};

template <> struct LayoutMap<Catlass::layout::nN> {
    static LayoutType const typeId = LayoutType::nN;
};

template <typename Element, typename Layout>
TensorDescription MakeTensorDescription()
{
    TensorDescription desc;
    desc.element = DataTypeMap<Element>::typeId;
    desc.layout = LayoutMap<Layout>::typeId;
    return desc;
}
}
}

#endif // CATLASS_LIBRARY_LIBRARY_UTILS_H
