/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 * This program is free software; you can redistribute it and/or modify it under the terms and conditions of
 * CANN Open Software License Agreement Version 2.0 (the "License").
 * Please refer to the License for details. You may not use this file except in compliance with the License.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 * See LICENSE in the root of the software repository for the full text of the License.
 */
#include "aes_gcm.h"

#include "openssl_loader.h"

namespace cce {
namespace runtime {
namespace cc_crypto_impl {

constexpr int32_t AICC_CRYPTO_NULLPTR = -1;
constexpr int32_t AICC_CRYPTO_CTX_FAILURE = -2;
constexpr int32_t AICC_CRYPTO_INIT_FAILURE = -3;
constexpr int32_t AICC_CRYPTO_ENC_FAILURE = -4;
constexpr int32_t AICC_CRYPTO_DEC_FAILURE = -5;
constexpr int32_t AICC_CRYPTO_AUTH_FAILURE = -6;
constexpr int32_t AICC_CRYPTO_FAILURE = -7;

int32_t aes128_gcm_encrypt(
    const uint8_t* key, const uint8_t* iv, const uint8_t* plaintext, size_t plaintext_len, const uint8_t* aad,
    size_t aad_len, uint8_t* ciphertext, size_t* ciphertext_len, const uint8_t* tag)
{
    if (key == nullptr || iv == nullptr || plaintext == nullptr || ciphertext == nullptr || ciphertext_len == nullptr ||
        tag == nullptr) {
        return AICC_CRYPTO_NULLPTR;
    }
    if (aad == nullptr && aad_len > 0) {
        return AICC_CRYPTO_NULLPTR;
    }

    auto& ssl = OpenSSLLoader::Instance();
    if (!ssl.Ready()) {
        return AICC_CRYPTO_CTX_FAILURE;
    }

    EVP_CIPHER_CTX* ctx = ssl.Api.CipherCtxNew();
    if (ctx == nullptr) {
        return AICC_CRYPTO_CTX_FAILURE;
    }

    int32_t ret = AICC_CRYPTO_FAILURE;
    int len = 0;
    size_t total = 0;

    do {
        if (ssl.Api.EncInit(ctx, ssl.Api.Aes128Gcm(), nullptr, nullptr, nullptr) != 1) {
            ret = AICC_CRYPTO_INIT_FAILURE;
            break;
        }
        if (ssl.Api.CtxCtrl(ctx, EVP_CTRL_GCM_SET_IVLEN, static_cast<int>(AES_GCM_IV_SIZE), nullptr) != 1) {
            ret = AICC_CRYPTO_AUTH_FAILURE;
            break;
        }
        if (ssl.Api.EncInit(ctx, nullptr, nullptr, key, iv) != 1) {
            ret = AICC_CRYPTO_INIT_FAILURE;
            break;
        }
        if (aad_len > 0) {
            int aad_out = 0;
            if (ssl.Api.EncUpdate(ctx, nullptr, &aad_out, aad, static_cast<int>(aad_len)) != 1) {
                ret = AICC_CRYPTO_ENC_FAILURE;
                break;
            }
        }
        if (ssl.Api.EncUpdate(ctx, ciphertext, &len, plaintext, static_cast<int>(plaintext_len)) != 1) {
            ret = AICC_CRYPTO_ENC_FAILURE;
            break;
        }
        total = static_cast<size_t>(len);
        if (ssl.Api.EncFinal(ctx, ciphertext + total, &len) != 1) {
            ret = AICC_CRYPTO_ENC_FAILURE;
            break;
        }
        total += static_cast<size_t>(len);

        if (ssl.Api.CtxCtrl(ctx, EVP_CTRL_GCM_GET_TAG, static_cast<int>(GCM_TAG_SIZE), const_cast<uint8_t*>(tag)) !=
            1) {
            ret = AICC_CRYPTO_AUTH_FAILURE;
            break;
        }

        *ciphertext_len = total;
        ret = 0;
    } while (false);

    ssl.Api.CipherCtxFree(ctx);
    return ret;
}

int32_t aes128_gcm_decrypt(
    const uint8_t* key, const uint8_t* iv, const uint8_t* ciphertext, size_t ciphertext_len, const uint8_t* aad,
    size_t aad_len, uint8_t* plaintext, size_t* plaintext_len, const uint8_t* tag)
{
    if (key == nullptr || iv == nullptr || ciphertext == nullptr || plaintext == nullptr || plaintext_len == nullptr ||
        tag == nullptr) {
        return AICC_CRYPTO_NULLPTR;
    }
    if (aad == nullptr && aad_len > 0) {
        return AICC_CRYPTO_NULLPTR;
    }

    auto& ssl = OpenSSLLoader::Instance();
    if (!ssl.Ready()) {
        return AICC_CRYPTO_CTX_FAILURE;
    }

    EVP_CIPHER_CTX* ctx = ssl.Api.CipherCtxNew();
    if (ctx == nullptr) {
        return AICC_CRYPTO_CTX_FAILURE;
    }

    int32_t ret = AICC_CRYPTO_FAILURE;
    int len = 0;
    size_t total = 0;

    do {
        if (ssl.Api.DecInit(ctx, ssl.Api.Aes128Gcm(), nullptr, nullptr, nullptr) != 1) {
            ret = AICC_CRYPTO_INIT_FAILURE;
            break;
        }
        if (ssl.Api.CtxCtrl(ctx, EVP_CTRL_GCM_SET_IVLEN, static_cast<int>(AES_GCM_IV_SIZE), nullptr) != 1) {
            ret = AICC_CRYPTO_AUTH_FAILURE;
            break;
        }
        if (ssl.Api.DecInit(ctx, nullptr, nullptr, key, iv) != 1) {
            ret = AICC_CRYPTO_INIT_FAILURE;
            break;
        }
        if (aad_len > 0) {
            int aad_out = 0;
            if (ssl.Api.DecUpdate(ctx, nullptr, &aad_out, aad, static_cast<int>(aad_len)) != 1) {
                ret = AICC_CRYPTO_DEC_FAILURE;
                break;
            }
        }
        if (ssl.Api.DecUpdate(ctx, plaintext, &len, ciphertext, static_cast<int>(ciphertext_len)) != 1) {
            ret = AICC_CRYPTO_DEC_FAILURE;
            break;
        }
        total = static_cast<size_t>(len);

        if (ssl.Api.CtxCtrl(ctx, EVP_CTRL_GCM_SET_TAG, static_cast<int>(GCM_TAG_SIZE), const_cast<uint8_t*>(tag)) !=
            1) {
            ret = AICC_CRYPTO_AUTH_FAILURE;
            break;
        }
        if (ssl.Api.DecFinal(ctx, plaintext + total, &len) != 1) {
            ret = AUTH_TAG_VERIFY_FAILED;
            break;
        }
        total += static_cast<size_t>(len);

        *plaintext_len = total;
        ret = 0;
    } while (false);

    ssl.Api.CipherCtxFree(ctx);
    return ret;
}

} // namespace cc_crypto_impl
} // namespace runtime
} // namespace cce
