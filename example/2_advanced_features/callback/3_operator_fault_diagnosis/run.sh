#!/bin/bash
# -----------------------------------------------------------------------------------------------------------
# Copyright (c) 2026 Huawei Technologies Co., Ltd.
# This program is free software, you can redistribute it and/or modify it under the terms and conditions of
# CANN Open Software License Agreement Version 2.0 (the "License").
# Please refer to the License for details. You may not use this file except in compliance with the License.
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
# INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
# See LICENSE in the root of the software repository for the full text of the License.
# -----------------------------------------------------------------------------------------------------------

set -euo pipefail
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

if [[ -z "${ASCEND_INSTALL_PATH:-}" || ! -f "${ASCEND_INSTALL_PATH}/set_env.sh" ||
      ! -f "${ASCEND_INSTALL_PATH}/include/acl/acl.h" ||
      ! -f "${ASCEND_INSTALL_PATH}/lib64/libacl_rt.so" ]]; then
    echo "[ERROR] Set ASCEND_INSTALL_PATH to a complete CANN Toolkit installation." >&2
    exit 1
fi

# The CANN environment script may read unset shell variables.
set +u
source "${ASCEND_INSTALL_PATH}/set_env.sh"
set -u
if [[ -z "${SOC_VERSION:-}" || ! -f "${ASCENDC_CMAKE_DIR:-}/ascendc.cmake" ||
      ! -f "${ASCENDC_CMAKE_DIR:-}/asc_modules/FindASC.cmake" ]]; then
    echo "[ERROR] Set SOC_VERSION and ASCENDC_CMAKE_DIR for the selected Device and CANN Toolkit." >&2
    exit 1
fi

cd "${SCRIPT_DIR}"
mkdir -p build
cd build
cmake .. -DASCEND_CANN_PACKAGE_PATH="${ASCEND_INSTALL_PATH}" \
    -DASCENDC_CMAKE_DIR="${ASCENDC_CMAKE_DIR}" -DSOC_VERSION="${SOC_VERSION}"
make -j"$(nproc)"
./main
