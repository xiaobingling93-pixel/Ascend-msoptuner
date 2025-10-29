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

#ifndef CATLASS_TUNER_LOG_H
#define CATLASS_TUNER_LOG_H

#include <string>
#include <unordered_map>
#include <cstdio>

#define LOG(__level, __msg, ...) printf(__level __msg "\n", ##__VA_ARGS__)
#define LOGI(__msg, ...) LOG("[INFO ] ", __msg, ##__VA_ARGS__)
#define LOGW(__msg, ...) LOG("[WARN ] ", __msg, ##__VA_ARGS__)
#define LOGE(__msg, ...) LOG("[ERROR] ", __msg, ##__VA_ARGS__)
#define LOGM(__msg, ...) LOG("", __msg, ##__VA_ARGS__)

inline const std::unordered_map<char, std::string>& GetInvalidChars()
{
    static const std::unordered_map<char, std::string> INVALID_CHAR = {
        {'\n', "\\n"}, {'\f', "\\f"}, {'\r', "\\r"}, {'\b', "\\b"},
        {'\t', "\\t"}, {'\v', "\\v"}, {'\u007F', "\\u007F"}
    };
    return INVALID_CHAR;
}

inline std::string ReplaceInvalidChars(const std::string &str)
{
    auto &invalidChars = GetInvalidChars();
    std::string replaced;
    for (auto c : str) {
        auto it = invalidChars.find(c);
        replaced += it != invalidChars.cend() ? it->second : std::string{c};
    }
    return replaced;
}

#endif // CATLASS_TUNER_LOG_H
