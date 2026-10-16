#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# -----------------------------------------------------------------------------------------------------------
# Copyright (c) 2025 Huawei Technologies Co., Ltd.
# This program is free software, you can redistribute it and/or modify it under the terms and conditions of
# CANN Open Software License Agreement Version 2.0 (the "License").
# Please refer to the License for details. You may not use this file except in compliance with the License.
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
# INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
# See LICENSE in the root of the software repository for the full text of the License.
# -----------------------------------------------------------------------------------------------------------

"""Host output files must have matching element counts before comparison."""

import importlib.util
from pathlib import Path

import numpy as np
import pytest

ROOT = Path(__file__).resolve().parents[6]
VERIFY_SCRIPTS = [
    "example/2_advanced_features/kernel/0_launch_kernel/scripts/verify_result.py",
    "example/3_memory_advanced/managed_memory/0_uvm_allocate/scripts/verify_result.py",
]


@pytest.mark.parametrize("script", VERIFY_SCRIPTS)
@pytest.mark.parametrize("output_values,golden_values", [
    ([1.0], [1.0, 1.0, 1.0]),
    ([1.0, 1.0, 1.0], [1.0]),
    ([], []),
    ([1.0, 2.0], [1.0, 2.0]),
    ([1.0, 3.0], [1.0, 2.0]),
])
def test_sample_verifier_requires_equal_nonempty_lengths(tmp_path, script, output_values, golden_values):
    spec = importlib.util.spec_from_file_location("runtime_sample_verifier", ROOT / script)
    verifier = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(verifier)
    output, golden = tmp_path / "output.bin", tmp_path / "golden.bin"
    np.asarray(output_values, dtype=np.float16).tofile(output)
    np.asarray(golden_values, dtype=np.float16).tofile(golden)
    expected = bool(golden_values) and output_values == golden_values
    assert bool(verifier.verify_result(output, golden)) is expected
