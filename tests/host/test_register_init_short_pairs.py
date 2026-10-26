# Copyright (c) 2026 Huawei Technologies Co., Ltd.
# This program is free software, you can redistribute it and/or modify it under the terms and conditions of
# CANN Open Software License Agreement Version 2.0 (the "License").
# Please refer to the License for details. You may not use this file except in compliance with the License.
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
# INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
# See LICENSE in the root of the software repository for the full text of the License.

"""Host file regressions for incomplete SC_DBG_ADDR_H records."""

import importlib.util
import os
import shutil
import subprocess
import sys
import tempfile
import unittest
from itertools import product
from pathlib import Path

def find_generator_path():
    for parent in Path(__file__).resolve().parents:
        candidate = parent / "src/dfx/adump/generate_register_init.py"
        if candidate.is_file():
            return candidate
    raise RuntimeError("cannot locate generate_register_init.py")


SOURCE = find_generator_path()
SPEC = importlib.util.spec_from_file_location("register_init_short_pairs", SOURCE)
GENERATOR = importlib.util.module_from_spec(SPEC)
PROXY_KEYS = ("http_proxy", "https_proxy", "HTTP_PROXY", "HTTPS_PROXY")
SAVED_PROXY = {key: os.environ.get(key) for key in PROXY_KEYS}
sys.modules[SPEC.name] = GENERATOR
try:
    SPEC.loader.exec_module(GENERATOR)
finally:
    sys.modules.pop(SPEC.name)
    for key, value in SAVED_PROXY.items():
        if value is not None:
            os.environ[key] = value

DEBUG_BASE = 0x1234567876543210
LOW_LINE = "write SC_DBG_ADDR_L 0x2000 31:0 badbeef\n"
SHORT_HIGH_LINES = [
    "write SC_DBG_ADDR_H\n",
    "write SC_DBG_ADDR_H 0x2004\n",
    "write SC_DBG_ADDR_H 0x2004 31:0\n",
]


def normal_lines(start, stop):
    return [
        f"read NORMAL_{index} 0x{0x1000 + 4 * index:x} 31:0 0\n"
        for index in range(start, stop)
    ]


def valid_debug_lines():
    lines = []
    for index in range(4):
        address = DEBUG_BASE + index
        lines += [
            f"write SC_DBG_ADDR_L 0x2010 31:0 {address & 0xFFFFFFFF:x}\n",
            f"write SC_DBG_ADDR_H 0x2014 31:0 {address >> 32:x}\n",
        ]
    return lines


def expected_registers(file_type):
    normal = [
        {
            "name": f"NORMAL_{index}",
            "address": 0x1000 + 4 * index,
            "bit_width": 32,
            "type": f"RegisterType::{file_type}_OFFSET",
        }
        for index in range(8)
    ]
    debug = [
        {
            "name": "Debug",
            "address": DEBUG_BASE + index,
            "bit_width": 32,
            "type": f"RegisterType::{file_type}_DBG",
        }
        for index in range(4)
    ]
    return normal, debug


class RegisterInitShortPairTest(unittest.TestCase):
    def check_file(self, file_type, middle):
        with tempfile.TemporaryDirectory(prefix="runtime-reginfo-") as directory:
            path = Path(directory) / f"reginfo_{file_type}.txt"
            path.write_text(
                "".join(
                    normal_lines(0, 4)
                    + middle
                    + normal_lines(4, 8)
                    + valid_debug_lines()
                )
            )
            normal, debug, duplicate = GENERATOR.process_reginfo(path, file_type)
            expected_normal, expected_debug = expected_registers(file_type)
            self.assertEqual(normal, expected_normal)
            self.assertEqual(debug, expected_debug)
            self.assertEqual(duplicate, {"normal": [], "debug": [], "file": path.name})

    def test_short_high_lines_preserve_other_registers(self):
        for file_type, high in product(["AIC", "AIV"], SHORT_HIGH_LINES):
            with self.subTest(file_type=file_type, fields=len(high.split())):
                self.check_file(file_type, [LOW_LINE, high])

    def test_existing_incomplete_pair_handling(self):
        controls = [
            [],
            [LOW_LINE],
            [LOW_LINE, "\n"],
            [LOW_LINE, "write SC_DBG_OTHER 0x2004 31:0 12345678\n"],
            [LOW_LINE, "write SC_DBG_ADDR_H 0x2004 31:0 invalid_hex\n"],
        ]
        for file_type, middle in product(["AIC", "AIV"], controls):
            with self.subTest(file_type=file_type, middle=middle):
                self.check_file(file_type, middle)

    def test_cli_retains_valid_data_from_both_files(self):
        with tempfile.TemporaryDirectory(prefix="runtime-register-cli-") as directory:
            root = Path(directory)
            script = root / SOURCE.name
            shutil.copyfile(SOURCE, script)
            for file_type, high in zip(["AIC", "AIV"], SHORT_HIGH_LINES):
                content = (
                    normal_lines(0, 4)
                    + [LOW_LINE, high]
                    + normal_lines(4, 8)
                    + valid_debug_lines()
                )
                (root / f"reginfo_{file_type}.txt").write_text("".join(content))
            completed = subprocess.run(
                [sys.executable, str(script)],
                capture_output=True,
                text=True,
                timeout=10,
            )
            self.assertEqual(completed.returncode, 0, completed.stderr)
            output = (root / "output.cpp").read_text()
            self.assertIn("// Normal registers: 16 registers", output)
            self.assertIn("// Debug registers: 8 registers", output)
            for file_type in ["AIC", "AIV"]:
                self.assertIn(f"RegisterType::{file_type}_OFFSET", output)
                self.assertIn(f"RegisterType::{file_type}_DBG", output)
            self.assertEqual(output.count("{0x1000, 32, 1}"), 2)
            self.assertEqual(output.count("{0x1234567876543210, 32, 1}"), 2)
            self.assertNotIn("Error processing", completed.stderr)


if __name__ == "__main__":
    unittest.main(verbosity=2)
