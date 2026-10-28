/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 * This program is free software; you can redistribute it and/or modify it under the terms and conditions of
 * CANN Open Software License Agreement Version 2.0 (the "License").
 * Please refer to the License for details. You may not use this file except in compliance with the License.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 * See LICENSE in the root of the software repository for the full text of the License.
 */
#include "openssl_loader.h"

#include <cstring>
#include <dlfcn.h>

#include "base.hpp"
#include "type_def.h"

namespace cce {
namespace runtime {

namespace {
constexpr const char* AICC_CRYPTO_OPENSSL_LIB_DEFAULT = "libcrypto.so.3";
// OpenSSL 3.x 版本号格式 0xMNN00PPSL（major/minor/fix/status），3.5.4 = 0x30500040
constexpr const char* AICC_CRYPTO_OPENSSL_MIN_VERSION = "3.5.4";
constexpr unsigned long AICC_CRYPTO_OPENSSL_MIN_VERSION_NUM = 0x30500040UL;

bool ResolveAll(void* handle, OpenSSLLoader& loader)
{
    auto dls = [handle](const char* name) -> void* {
        (void)dlerror();
        return dlsym(handle, name);
    };
#define OPENSSL_API_ASSIGN(member, type, sym) loader.Api.member = PtrToFunctionPtr<void, OpenSSLApi::type>(dls(sym));
    OPENSSL_API_TABLE(OPENSSL_API_ASSIGN)
#undef OPENSSL_API_ASSIGN
    return loader.Api.Complete();
}
} // namespace

OpenSSLLoader& OpenSSLLoader::Instance()
{
    static OpenSSLLoader inst;
    return inst;
}

OpenSSLLoader::~OpenSSLLoader()
{
    if (handle_ != nullptr) {
        dlclose(handle_);
        handle_ = nullptr;
    }
    inited_ = false;
}

bool OpenSSLLoader::Init() noexcept
{
    std::call_once(once_, [this]() {
        const char* path = AICC_CRYPTO_OPENSSL_LIB_DEFAULT;
        // RTLD_LOCAL：libcrypto 符号不进入全局符号表，避免与宿主进程链接的其他版本 OpenSSL 冲突
        // 无路径的 soname 由动态链接器按 DT_RPATH -> LD_LIBRARY_PATH -> DT_RUNPATH -> ld.so.cache -> 默认目录
        // 解析，因此可通过 LD_LIBRARY_PATH 指定 OpenSSL 所在目录
        void* h = dlopen(path, static_cast<int>(RTLD_LAZY) | static_cast<int>(RTLD_LOCAL));
        if (h == nullptr) {
            RT_LOG(RT_LOG_ERROR, "OpenSSLLoader dlopen %s failed: %s", path, dlerror());
            inited_ = false;
            return;
        }
        if (!ResolveAll(h, *this)) {
            RT_LOG(RT_LOG_ERROR, "OpenSSLLoader dlsym incomplete: %s", dlerror());
            dlclose(h);
            inited_ = false;
            return;
        }
        const unsigned long versionNum = Api.VersionNum();
        if (versionNum < AICC_CRYPTO_OPENSSL_MIN_VERSION_NUM) {
            RT_LOG(
                RT_LOG_ERROR, "OpenSSLLoader version 0x%lx of %s below minimum 0x%lx", versionNum, path,
                AICC_CRYPTO_OPENSSL_MIN_VERSION_NUM);
            dlclose(h);
            inited_ = false;
            return;
        }
        handle_ = h;
        inited_ = true;
        RT_LOG(RT_LOG_INFO, "OpenSSLLoader loaded %s ok, version 0x%lx", path, versionNum);
    });
    if (!inited_) {
        RT_LOG_OUTER_MSG_WITH_FUNC_DESC(
            ErrorCode::EE1016, "Loading the OpenSSL library",
            RtFmtMsg(
                "Confidential computing requires OpenSSL %s or later. Please install or upgrade OpenSSL, or add the "
                "directory containing libcrypto.so.3 to LD_LIBRARY_PATH",
                AICC_CRYPTO_OPENSSL_MIN_VERSION));
    }
    return inited_;
}

bool OpenSSLLoader::Ready() const noexcept { return handle_ != nullptr && inited_ && Api.Complete(); }

} // namespace runtime
} // namespace cce
