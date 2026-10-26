/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 * This program is free software, you can redistribute it and/or modify it under the terms and conditions of
 * CANN Open Software License Agreement Version 2.0 (the "License").
 * Please refer to the License for details. You may not use this file except in compliance with the License.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 * See LICENSE in the root of the software repository for the full text of the License.
 *
 * AES-128-GCM algorithm wrappers (internal, adapted from AX_runtime_host).
 */
#ifndef CCE_RUNTIME_AES_GCM_HPP
#define CCE_RUNTIME_AES_GCM_HPP

#include <cstdint>
#include <cstddef>

namespace cce {
namespace runtime {
namespace cc_crypto_impl {

// AES-128 密钥长度（字节）
constexpr uint32_t AES_128_KEY_SIZE = 16U;
// GCM IV 长度（字节）
constexpr uint32_t AES_GCM_IV_SIZE = 12U;
// IV 随机基址长度（字节）
constexpr uint32_t GCM_IV_BASE_SIZE = 8U;
// IV 计数器长度（字节）
constexpr uint32_t GCM_IV_COUNTER_SIZE = 4U;
// IV 计数器上限（达到后重新生成随机 base，避免 32 位回绕导致 IV 重用）
constexpr uint32_t GCM_IV_COUNTER_MAX = 0xFFFFFFFFU;
// GCM 认证标签长度（字节）
constexpr uint32_t GCM_TAG_SIZE = 16U;
// GCM 附加认证数据（AAD）最大长度（字节）
constexpr uint32_t GCM_AAD_MAX_SIZE = 32U;
// 驱动侧密钥槽位 ID：1 = H2D 加密密钥，2 = D2H 解密密钥（halGetSlotKey 的 slot 入参）
constexpr uint32_t KEY_SLOT_H2D = 1U;
constexpr uint32_t KEY_SLOT_D2H = 2U;
// 驱动侧槽位密钥最大长度（字节）
constexpr uint32_t SLOT_KEY_MAX_SIZE = 64U;

// 加解密操作失败返回值
constexpr int32_t CRYPTO_FAILURE = -1;
// GCM tag 校验失败
constexpr int32_t AUTH_TAG_VERIFY_FAILED = -8;

/// AES-128-GCM 加密
/// @param key            16 字节密钥
/// @param iv             12 字节初始向量
/// @param plaintext      待加密明文
/// @param plaintext_len  明文长度
/// @param aad            附加认证数据（参与 tag 计算与校验，不加密），可为 nullptr
/// @param aad_len        AAD 长度（字节），0 表示无 AAD
/// @param ciphertext     加密后密文输出（长度同 plaintext_len）
/// @param ciphertext_len 输出实际密文长度
/// @param tag            输出 16 字节认证标签（注意：签名中为 const，实现为输出，内部 const_cast 写入）
/// @return 0 成功，负值失败
int32_t aes128_gcm_encrypt(
    const uint8_t* key, const uint8_t* iv, const uint8_t* plaintext, size_t plaintext_len, const uint8_t* aad,
    size_t aad_len, uint8_t* ciphertext, size_t* ciphertext_len, const uint8_t* tag);

/// AES-128-GCM 解密
/// @param key             16 字节密钥
/// @param iv              12 字节初始向量
/// @param ciphertext      待解密密文
/// @param ciphertext_len  密文长度
/// @param aad             附加认证数据（参与 tag 校验，不加密），可为 nullptr
/// @param aad_len         AAD 长度（字节），0 表示无 AAD
/// @param plaintext       解密后明文输出
/// @param plaintext_len   输出实际明文长度
/// @param tag             16 字节认证标签，用于校验
/// @return 0 成功，负值失败（含标签校验失败）
int32_t aes128_gcm_decrypt(
    const uint8_t* key, const uint8_t* iv, const uint8_t* ciphertext, size_t ciphertext_len, const uint8_t* aad,
    size_t aad_len, uint8_t* plaintext, size_t* plaintext_len, const uint8_t* tag);

} // namespace cc_crypto_impl
} // namespace runtime
} // namespace cce

#endif // CCE_RUNTIME_AES_GCM_HPP