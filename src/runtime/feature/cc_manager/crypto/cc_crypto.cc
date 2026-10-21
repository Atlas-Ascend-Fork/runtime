/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 * This program is free software, you can redistribute it and/or modify it under the terms and conditions of
 * CANN Open Software License Agreement Version 2.0 (the "License").
 * Please refer to the License for details. You may not use this file except in compliance with the License.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 * See LICENSE in the root of the software repository for the full text of the License.
 */
#include "cc_crypto.h"

#include <atomic>
#include <cstring>
#include <memory>
#include <mutex>

#include "aes_gcm.h"
#include "base.hpp"
#include "common/internal_error_define.hpp"
#include "npu_driver.hpp"
#include "driver.hpp"
#include "openssl_loader.h"
#include "runtime.hpp"
#include "type_def.h"

namespace cce {
namespace runtime {

namespace {
constexpr uint32_t AICC_CIPHER_VERSION = 1U;

// device 侧密钥区（dev_key_addr）布局：[0,16)=H2D 密钥，[16,32)=D2H 密钥；
// 由 AICPU 填充算子写入，加解密算子按 mode 偏移取用（keyAddr + mode*AES_128_KEY_SIZE）
constexpr uint32_t AICC_DEV_KEY_REGION_SIZE = 2U * cc_crypto_impl::AES_128_KEY_SIZE;

struct IvCtx {
    uint8_t base[cc_crypto_impl::GCM_IV_BASE_SIZE] = {0};
    uint32_t counter = 0U;
    std::mutex mtx;
    std::atomic<uint64_t> totalBytes{0};
};

int32_t aes128GcmGetIv(IvCtx& ivCtx, uint8_t iv[cc_crypto_impl::AES_GCM_IV_SIZE])
{
    if (iv == nullptr) {
        return -1;
    }
    std::lock_guard<std::mutex> lk(ivCtx.mtx);
    if (ivCtx.counter >= cc_crypto_impl::GCM_IV_COUNTER_MAX) {
        auto& ssl = OpenSSLLoader::Instance();
        if (!ssl.Ready() || ssl.Api.RandBytes == nullptr) {
            return -1;
        }
        if (ssl.Api.RandBytes(ivCtx.base, static_cast<int>(cc_crypto_impl::GCM_IV_BASE_SIZE)) != 1) {
            return -1;
        }
        ivCtx.counter = 0U;
    }
    (void)memcpy_s(iv, cc_crypto_impl::AES_GCM_IV_SIZE, ivCtx.base, cc_crypto_impl::GCM_IV_BASE_SIZE);
    const uint32_t seq = ivCtx.counter;
    ivCtx.counter = seq + 1U;
    iv[cc_crypto_impl::GCM_IV_BASE_SIZE + 0U] = static_cast<uint8_t>((seq >> 24U) & 0xFFU);
    iv[cc_crypto_impl::GCM_IV_BASE_SIZE + 1U] = static_cast<uint8_t>((seq >> 16U) & 0xFFU);
    iv[cc_crypto_impl::GCM_IV_BASE_SIZE + 2U] = static_cast<uint8_t>((seq >> 8U) & 0xFFU);
    iv[cc_crypto_impl::GCM_IV_BASE_SIZE + 3U] = static_cast<uint8_t>(seq & 0xFFU);
    return 0;
}

int32_t InitIvBase(IvCtx* ivCtx)
{
    if (ivCtx == nullptr) {
        return -1;
    }
    auto& ssl = OpenSSLLoader::Instance();
    if (!ssl.Ready() || ssl.Api.RandBytes == nullptr) {
        return -1;
    }
    std::lock_guard<std::mutex> lk(ivCtx->mtx);
    if (ssl.Api.RandBytes(ivCtx->base, static_cast<int>(cc_crypto_impl::GCM_IV_BASE_SIZE)) != 1) {
        return -1;
    }
    ivCtx->counter = 0U;
    ivCtx->totalBytes.store(0U);
    return 0;
}

} // namespace

extern "C" int halGetSlotKey(uint32_t device_id, uint32_t slot, uint8_t* key, uint32_t* key_len)
{
    // placeholder slot key for bring-up; replace with real driver implementation once ready.
    (void)device_id;
    if ((key == nullptr) || (key_len == nullptr)) {
        return -1;
    }
    uint8_t fill = 0U;
    if (slot == 1U) {
        fill = 0x11U;
    } else if (slot == 2U) {
        fill = 0x12U;
    } else {
        return -1;
    }
    (void)memset_s(key, 16U, fill, 16U); // 16 slot key len
    *key_len = 16U;
    return 0;
}

int32_t GetKeyFromKernel(
    int32_t deviceId, CRYPTO_KEY_DIRECTION direction, uint8_t key[cc_crypto_impl::AES_128_KEY_SIZE])
{
    if (deviceId < 0 || key == nullptr) {
        return -1;
    }
    uint32_t slot = 0U;
    if (direction == CRYPTO_KEY_DIRECTION::H2D) {
        slot = 1U;
    } else if (direction == CRYPTO_KEY_DIRECTION::D2H) {
        slot = 2U;
    } else {
        return -1;
    }
    uint32_t keyLen = 0U;
    if (halGetSlotKey(static_cast<uint32_t>(deviceId), slot, key, &keyLen) != 0) {
        return -1;
    }
    if (keyLen != cc_crypto_impl::AES_128_KEY_SIZE) {
        return -1;
    }
    return 0;
}

struct CCrypto::KeyCtx {
    std::atomic<bool> is_init{false};
    uint8_t host_key_H2D[cc_crypto_impl::AES_128_KEY_SIZE] = {0};
    uint8_t host_key_D2H[cc_crypto_impl::AES_128_KEY_SIZE] = {0};
    IvCtx ivH2D;
    std::atomic<uint64_t> totalBytesD2H{0};
    uint64_t dev_key_addr = 0; // device 侧密钥区地址（32B：H2D|D2H，AICPU 填充算子写入）
};

CCrypto::~CCrypto()
{
    if (keyCtx_ != nullptr) {
        if (keyCtx_->is_init) {
            (void)memset_s(
                keyCtx_->host_key_H2D, cc_crypto_impl::AES_128_KEY_SIZE, 0, cc_crypto_impl::AES_128_KEY_SIZE);
            (void)memset_s(
                keyCtx_->host_key_D2H, cc_crypto_impl::AES_128_KEY_SIZE, 0, cc_crypto_impl::AES_128_KEY_SIZE);
            if (keyCtx_->dev_key_addr != 0U) {
                (void)Runtime::Instance()
                    ->driverFactory_.GetDriver(NPU_DRIVER)
                    ->DevMemFree(ValueToPtr(keyCtx_->dev_key_addr), 0U);
                keyCtx_->dev_key_addr = 0U;
            }
            keyCtx_->is_init = false;
        }
        delete keyCtx_;
        keyCtx_ = nullptr;
    }
}

rtError_t CCrypto::InitKey(uint32_t deviceId)
{
    if (!OpenSSLLoader::Instance().Init()) {
        RT_LOG(RT_LOG_ERROR, "CCrypto InitKey openssl loader not ready, deviceId=%u", deviceId);
        return RT_ERROR_CC_CRYPTO_FAILED;
    }
    if (keyCtx_ == nullptr) {
        keyCtx_ = new (std::nothrow) KeyCtx();
        if (keyCtx_ == nullptr) {
            RT_LOG(RT_LOG_ERROR, "CCrypto InitKey alloc KeyCtx failed, deviceId=%u", deviceId);
            return RT_ERROR_CC_CRYPTO_FAILED;
        }
    }
    int32_t ret = GetKeyFromKernel(static_cast<int32_t>(deviceId), CRYPTO_KEY_DIRECTION::H2D, keyCtx_->host_key_H2D);
    if (ret != 0) {
        RT_LOG(RT_LOG_ERROR, "CCrypto InitKey get H2D key failed, deviceId=%u, ret=%d", deviceId, ret);
        return RT_ERROR_CC_CRYPTO_FAILED;
    }
    ret = GetKeyFromKernel(static_cast<int32_t>(deviceId), CRYPTO_KEY_DIRECTION::D2H, keyCtx_->host_key_D2H);
    if (ret != 0) {
        RT_LOG(RT_LOG_ERROR, "CCrypto InitKey get D2H key failed, deviceId=%u, ret=%d", deviceId, ret);
        return RT_ERROR_CC_CRYPTO_FAILED;
    }
    if (InitIvBase(&keyCtx_->ivH2D) != 0) {
        RT_LOG(RT_LOG_ERROR, "CCrypto InitKey gen IV base failed, deviceId=%u", deviceId);
        return RT_ERROR_CC_CRYPTO_FAILED;
    }
    keyCtx_->totalBytesD2H.store(0U);
    if (keyCtx_->dev_key_addr != 0U) {
        (void)Runtime::Instance()
            ->driverFactory_.GetDriver(NPU_DRIVER)
            ->DevMemFree(ValueToPtr(keyCtx_->dev_key_addr), deviceId);
        keyCtx_->dev_key_addr = 0U;
    }
    void* devKeyBuf = nullptr;
    Driver* const driver = Runtime::Instance()->driverFactory_.GetDriver(NPU_DRIVER);
    const uint64_t alignSize = (((AICC_DEV_KEY_REGION_SIZE + 0x1FU) >> 5U) << 5U);
    const uint64_t drvFlag = NpuDriver::BuildDevMemAllocFlag(deviceId, MODULEID_RUNTIME, false, false, true);
    const rtError_t merr = driver->DevMemAllocWithFlag(&devKeyBuf, alignSize, RT_MEMORY_HBM, drvFlag);
    if (merr != RT_ERROR_NONE || devKeyBuf == nullptr) {
        RT_LOG(RT_LOG_ERROR, "CC Crypto InitKey alloc device key mem failed, deviceId=%u, ret=%#x", deviceId, merr);
        RT_LOG_OUTER_MSG_IMPL(
            ErrorCode::EE1023, "Alloc device memory for the encryption and decryption keys",
            "Device memory is insufficient");
        return RT_ERROR_CC_CRYPTO_FAILED;
    }
    keyCtx_->dev_key_addr = PtrToValue(devKeyBuf);
    keyCtx_->is_init = true;
    RT_LOG(RT_LOG_INFO, "CCrypto InitKey ok, deviceId=%u", deviceId);
    return RT_ERROR_NONE;
}

rtError_t CCrypto::ReleaseKey(uint32_t deviceId) const
{
    (void)deviceId;
    if (keyCtx_ == nullptr) {
        return RT_ERROR_NONE;
    }
    if (!keyCtx_->is_init) {
        return RT_ERROR_NONE;
    }
    (void)memset_s(keyCtx_->host_key_H2D, cc_crypto_impl::AES_128_KEY_SIZE, 0, cc_crypto_impl::AES_128_KEY_SIZE);
    (void)memset_s(keyCtx_->host_key_D2H, cc_crypto_impl::AES_128_KEY_SIZE, 0, cc_crypto_impl::AES_128_KEY_SIZE);
    if (keyCtx_->dev_key_addr != 0U) {
        (void)Runtime::Instance()
            ->driverFactory_.GetDriver(NPU_DRIVER)
            ->DevMemFree(ValueToPtr(keyCtx_->dev_key_addr), deviceId);
    }
    keyCtx_->dev_key_addr = 0U;
    keyCtx_->is_init = false;
    RT_LOG(RT_LOG_INFO, "CCrypto ReleaseKey ok, deviceId=%u", deviceId);
    return RT_ERROR_NONE;
}

rtError_t CCrypto::Encrypt(
    uint32_t deviceId, const uint8_t* plaintext, size_t ptLen, const uint8_t* aad, size_t aadLen, uint8_t* ciphertext,
    size_t* ctLen) const
{
    (void)deviceId;
    if (plaintext == nullptr || ciphertext == nullptr || ctLen == nullptr) {
        return RT_ERROR_INVALID_VALUE;
    }
    if (aad == nullptr && aadLen > 0) {
        return RT_ERROR_INVALID_VALUE;
    }
    if (keyCtx_ == nullptr) {
        return RT_ERROR_CC_KEY_NOT_INITIALIZED;
    }
    if (!keyCtx_->is_init) {
        return RT_ERROR_CC_KEY_NOT_INITIALIZED;
    }

    uint8_t iv[cc_crypto_impl::AES_GCM_IV_SIZE];
    if (aes128GcmGetIv(keyCtx_->ivH2D, iv) != 0) {
        RT_LOG(RT_LOG_ERROR, "CCrypto Encrypt gen IV failed, deviceId=%u", deviceId);
        return RT_ERROR_CC_CRYPTO_FAILED;
    }
    uint8_t* enc_body = ciphertext + sizeof(CCCipherTxtHeader);
    uint8_t tag_buf[cc_crypto_impl::GCM_TAG_SIZE];
    size_t enc_len = 0;
    int32_t ret = cc_crypto_impl::aes128_gcm_encrypt(
        keyCtx_->host_key_H2D, iv, plaintext, ptLen, aad, aadLen, enc_body, &enc_len, tag_buf);
    if (ret != 0) {
        RT_LOG(RT_LOG_ERROR, "CCrypto Encrypt aes128_gcm_encrypt failed, deviceId=%u, ret=%d", deviceId, ret);
        return RT_ERROR_CC_CRYPTO_FAILED;
    }
    keyCtx_->ivH2D.totalBytes.fetch_add(static_cast<uint64_t>(ptLen));

    CCCipherTxtHeader* hdr = PtrToPtr<uint8_t, CCCipherTxtHeader>(ciphertext);
    hdr->version = AICC_CIPHER_VERSION;
    hdr->totalLen = static_cast<uint32_t>(sizeof(CCCipherTxtHeader)) + static_cast<uint32_t>(enc_len);
    hdr->ivLen = cc_crypto_impl::AES_GCM_IV_SIZE;
    (void)memcpy_s(hdr->iv, sizeof(hdr->iv), iv, cc_crypto_impl::AES_GCM_IV_SIZE);
    hdr->tagLen = cc_crypto_impl::GCM_TAG_SIZE;
    (void)memcpy_s(hdr->tag, sizeof(hdr->tag), tag_buf, cc_crypto_impl::GCM_TAG_SIZE);
    hdr->ciphertextLen = static_cast<uint32_t>(enc_len);

    *ctLen = sizeof(CCCipherTxtHeader) + enc_len;
    return RT_ERROR_NONE;
}

rtError_t CCrypto::Decrypt(
    uint32_t deviceId, const uint8_t* ciphertext, size_t ctLen, const uint8_t* aad, size_t aadLen, uint8_t* plaintext,
    size_t* ptLen) const
{
    (void)deviceId;
    if (ciphertext == nullptr || plaintext == nullptr || ptLen == nullptr) {
        return RT_ERROR_INVALID_VALUE;
    }
    if (aad == nullptr && aadLen > 0) {
        return RT_ERROR_INVALID_VALUE;
    }
    if (ctLen < sizeof(CCCipherTxtHeader)) {
        return RT_ERROR_INVALID_VALUE;
    }
    if (keyCtx_ == nullptr) {
        return RT_ERROR_CC_KEY_NOT_INITIALIZED;
    }
    if (!keyCtx_->is_init) {
        return RT_ERROR_CC_KEY_NOT_INITIALIZED;
    }

    const CCCipherTxtHeader* hdr = PtrToPtr<uint8_t, const CCCipherTxtHeader>(ciphertext);
    if (hdr->totalLen != ctLen) {
        return RT_ERROR_INVALID_VALUE;
    }
    size_t enc_len = ctLen - sizeof(CCCipherTxtHeader);
    if (enc_len != hdr->ciphertextLen) {
        return RT_ERROR_INVALID_VALUE;
    }

    const uint8_t* iv = hdr->iv;
    const uint8_t* tag = hdr->tag;
    const uint8_t* enc_body = ciphertext + sizeof(CCCipherTxtHeader);
    size_t dec_len = 0;
    int32_t ret = cc_crypto_impl::aes128_gcm_decrypt(
        keyCtx_->host_key_D2H, iv, enc_body, enc_len, aad, aadLen, plaintext, &dec_len, tag);
    if (ret != 0) {
        RT_LOG(RT_LOG_ERROR, "CCrypto Decrypt aes128_gcm_decrypt failed, deviceId=%u, ret=%d", deviceId, ret);
        if (ret == cc_crypto_impl::AUTH_TAG_VERIFY_FAILED) {
            return RT_ERROR_CC_TAG_VERIFY_FAILED;
        }
        return RT_ERROR_CC_CRYPTO_FAILED;
    }
    *ptLen = dec_len;
    keyCtx_->totalBytesD2H.fetch_add(static_cast<uint64_t>(dec_len));
    return RT_ERROR_NONE;
}

rtError_t CCrypto::BuildDeviceCryptoParam(uint32_t deviceId, CC_CRYPTO_MODE mode, CCCryptoKernelParam* param) const
{
    (void)deviceId;
    if (param == nullptr) {
        return RT_ERROR_INVALID_VALUE;
    }
    if (keyCtx_ == nullptr) {
        return RT_ERROR_CC_KEY_NOT_INITIALIZED;
    }
    if (!keyCtx_->is_init) {
        return RT_ERROR_CC_KEY_NOT_INITIALIZED;
    }
    // 单把密钥长度；AICPU 算子按 mode 取 keyAddr + mode*keyLen 处的方向密钥
    param->keyLen = cc_crypto_impl::AES_128_KEY_SIZE;
    param->mode = static_cast<uint32_t>(mode);
    param->algType = static_cast<uint32_t>(CC_CRYPTO_ALG_TYPE::AES_128_GCM);
    param->keyAddr =
        keyCtx_->dev_key_addr + (mode == CC_CRYPTO_MODE::ENCRYPT_MODE ? cc_crypto_impl::AES_128_KEY_SIZE : 0);
    return RT_ERROR_NONE;
}

rtError_t CCrypto::BuildLoadKeyParam(CCLoadKeyKernelParam* param) const
{
    if (param == nullptr) {
        return RT_ERROR_INVALID_VALUE;
    }
    if (keyCtx_ == nullptr) {
        return RT_ERROR_CC_KEY_NOT_INITIALIZED;
    }

    if (!keyCtx_->is_init || keyCtx_->dev_key_addr == 0U) {
        return RT_ERROR_CC_KEY_NOT_INITIALIZED;
    }

    param->h2dSlotId = 1U;
    param->d2hSlotId = 2U;
    param->keyAddr = keyCtx_->dev_key_addr;
    param->keyLen = cc_crypto_impl::AES_128_KEY_SIZE;
    return RT_ERROR_NONE;
}

} // namespace runtime
} // namespace cce
