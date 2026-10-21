/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 * This program is free software: you can redistribute it and/or modify it under the terms and conditions of
 * CANN Open Software License Agreement Version 2.0 (the "License").
 * Please refer to the License for details. You may not use this file except in compliance with the License.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 * See LICENSE in the root of the software repository for the full text of the License.
 */
#ifndef CCE_RUNTIME_CC_CRYPTO_H
#define CCE_RUNTIME_CC_CRYPTO_H

#include <cstdint>
#include <cstddef>

#include "runtime/rt_external_base.h"

namespace cce {
namespace runtime {

constexpr uint32_t CC_AES_128_KEY_SIZE = 16U;

enum class CC_CRYPTO_MODE : uint32_t {
    ENCRYPT_MODE = 0,
    DECRYPT_MODE = 1,
};

enum class CC_CRYPTO_ALG_TYPE : uint32_t {
    AES_128_GCM = 0,
};

enum class CRYPTO_KEY_DIRECTION : uint32_t {
    H2D = 0,
    D2H = 1,
};

// Ciphertext wire format header (Host encrypt output / AICPU decrypt input).
struct CCCipherTxtHeader {
    uint32_t version;
    uint32_t totalLen;
    uint32_t ivLen;
    uint8_t iv[32];
    uint32_t tagLen;
    uint8_t tag[32];
    uint32_t ciphertextLen;
};

struct CCCryptoKernelParam {
    uint64_t keyAddr;
    uint32_t keyLen;
    uint32_t mode;
    uint32_t algType;
    uint64_t taskQueueAddr;
};

struct CCLoadKeyKernelParam {
    uint16_t h2dSlotId;
    uint16_t d2hSlotId;
    uint32_t keyLen;
    uint64_t keyAddr;
};

int32_t GetKeyFromKernel(int32_t deviceId, CRYPTO_KEY_DIRECTION direction, uint8_t key[CC_AES_128_KEY_SIZE]);

class CCrypto {
public:
    CCrypto() = default;
    ~CCrypto();

    rtError_t InitKey(uint32_t deviceId);
    rtError_t ReleaseKey(uint32_t deviceId) const;

    rtError_t Encrypt(
        uint32_t deviceId, const uint8_t* plaintext, size_t ptLen, const uint8_t* aad, size_t aadLen,
        uint8_t* ciphertext, size_t* ctLen) const;
    rtError_t Decrypt(
        uint32_t deviceId, const uint8_t* ciphertext, size_t ctLen, const uint8_t* aad, size_t aadLen,
        uint8_t* plaintext, size_t* ptLen) const;

    rtError_t BuildDeviceCryptoParam(uint32_t deviceId, CC_CRYPTO_MODE mode, CCCryptoKernelParam* param) const;
    rtError_t BuildLoadKeyParam(CCLoadKeyKernelParam* param) const;

private:
    struct KeyCtx;
    KeyCtx* keyCtx_{nullptr};
};

} // namespace runtime
} // namespace cce

#endif // CCE_RUNTIME_CC_CRYPTO_H
