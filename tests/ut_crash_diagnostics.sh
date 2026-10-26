#!/bin/bash
# -----------------------------------------------------------------------------------------------------------
# Copyright (c) 2025 Huawei Technologies Co., Ltd.
# This program is free software, you can redistribute it and/or modify it under the terms and conditions of
# CANN Open Software License Agreement Version 2.0 (the "License").
# Please refer to the License for details. You may not use this file except in compliance with the License.
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
# INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
# See LICENSE in the root of the software repository for the full text of the License.
# -----------------------------------------------------------------------------------------------------------

prepare_ut_crash_diagnostics() {
  local -a missing=()
  command -v gdb >/dev/null 2>&1 || missing+=(gdb)
  command -v python3 >/dev/null 2>&1 || missing+=(python3)
  if [[ ${#missing[@]} -gt 0 && "${UT_CRASH_AUTO_INSTALL:-1}" == 1 ]]; then
    local -a administrator=()
    if [[ $(id -u) -ne 0 ]]; then
      if command -v sudo >/dev/null 2>&1 && sudo -n true; then
        administrator=(sudo -n)
      else
        echo "WARNING: Cannot install ${missing[*]} without root or passwordless sudo." >&2
        return 1
      fi
    fi
    if ! command -v apt-get >/dev/null 2>&1; then
      echo "WARNING: Install ${missing[*]} in the UT image; apt-get is unavailable." >&2
      return 1
    fi
    echo "Installing Runtime UT crash diagnostics: ${missing[*]}"
    local -a bounded=()
    command -v timeout >/dev/null 2>&1 && bounded=(timeout --kill-after=5s 180s)
    local -a apt_options=(-o Dpkg::Lock::Timeout=60 -o Acquire::Retries=1
      -o Acquire::http::Timeout=30 -o Acquire::https::Timeout=30)
    if ! "${bounded[@]}" "${administrator[@]}" env DEBIAN_FRONTEND=noninteractive \
      apt-get "${apt_options[@]}" update ||
      ! "${bounded[@]}" "${administrator[@]}" env DEBIAN_FRONTEND=noninteractive \
      apt-get "${apt_options[@]}" install -y --no-install-recommends "${missing[@]}"; then
      echo "WARNING: Failed to install Runtime UT crash diagnostics dependencies." >&2
      return 1
    fi
    hash -r
  fi
  if ! command -v gdb >/dev/null 2>&1 || ! command -v python3 >/dev/null 2>&1; then
    echo "WARNING: gdb and python3 are required for crash-time stack collection." >&2
    return 1
  fi
  if ! [[ "${UT_CRASH_GDB_TIMEOUT:-60}" =~ ^[0-9]+$ ]] ||
    [[ "${UT_CRASH_GDB_TIMEOUT:-60}" -lt 1 || "${UT_CRASH_GDB_TIMEOUT:-60}" -gt 240 ]]; then
    echo "WARNING: UT_CRASH_GDB_TIMEOUT must be in 1..240 seconds." >&2
    return 1
  fi
}
