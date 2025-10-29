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

#ifndef CATLASS_TUNER_DEVICE_MEMORY_MANAGER_H
#define CATLASS_TUNER_DEVICE_MEMORY_MANAGER_H

#include <memory>
#include <vector>
#include <algorithm>
#include <cstdint>
#include "log.h"
#include "m_t_var.h"

#include <acl/acl.h>
#include <runtime/rt_ffts.h>

namespace Catlass {

#define ACL_CHECK(status, func)                                                 \
    do {                                                                        \
        aclError err = status;                                                  \
        if (err != ACL_SUCCESS) {                                               \
            LOGE("%s:%d call " func "failed: %d", __FILE__, __LINE__, err);     \
        }                                                                       \
    } while (0)

// Macro function for unwinding rt errors.
#define RT_CHECK(status, func)                                                               \
    do {                                                                                     \
        rtError_t error = status;                                                            \
        if (error != RT_ERROR_NONE) {                                                        \
            LOGE("%s:%d call " func " rtError: %d", __FILE__, __LINE__, error);              \
        }                                                                                    \
    } while (0)

struct DeviceMemoryParam {
    void **addr;
    size_t size;
};

class DeviceMemoryManager {
public:
    static DeviceMemoryManager& Instance()
    {
        static DeviceMemoryManager t;
        return t;
    }

    DeviceMemoryManager(const DeviceMemoryManager&) = delete;
    DeviceMemoryManager& operator=(const DeviceMemoryManager&) = delete;
    DeviceMemoryManager(DeviceMemoryManager&&) = delete;
    DeviceMemoryManager& operator=(DeviceMemoryManager&&) = delete;

    inline uint64_t GetFftsAddr()
    {
        uint32_t fftsLen{0};
        if (fftsAddr_ == 0) {
            RT_CHECK(rtGetC2cCtrlAddr(&fftsAddr_, &fftsLen), "rtGetC2cCtrlAddr");
        }
        return fftsAddr_;
    }

    inline bool FreeWorkspace()
    {
        if (Free(workspace_)) {
            workspace_ = nullptr;
            workspaceSize_ = 0;
            return true;
        }
        return false;
    }

    bool FillDeviceData(void* dst, size_t size, void* host) const;
    aclrtStream Initialize(int32_t deviceId);
    void Finalize();
    bool MallocArguments(std::vector<DeviceMemoryParam> &params);
    bool MallocWorkspace(DeviceMemoryParam &param);
    bool ClearL2Cache(uint32_t blockDim);
    bool InitCacheClear();
    aclError SetCacheClearTiling(uint64_t clearSizePerCore);

private:
    struct CacheClear {
        void *buffer{nullptr};
        void *tilingSize{nullptr};
        void *flushBuffer{nullptr};
        std::vector<void*> cmoBuffers{};
        uint64_t cacheSize{};
    };

    DeviceMemoryManager() = default;
    ~DeviceMemoryManager()
    {
        Finalize();
    }

    inline uint64_t Align(uint64_t size) const { return ((size + 63) / 64) * 64; }

    bool Expand(void** addr, uint64_t &size, uint64_t target);
    bool Free(void* addr);

    void *arg_{nullptr};
    uint64_t argSize_{0};
    void *workspace_{nullptr};
    uint64_t workspaceSize_{0};
    aclrtStream stream_{nullptr};
    CacheClear cacheClear_{};
    uint64_t fftsAddr_{0};
    int32_t deviceId_{0};
};

} // namespace Catlass
#endif // CATLASS_TUNER_DEVICE_MEMORY_MANAGER_H
