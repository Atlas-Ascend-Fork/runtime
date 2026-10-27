#!/usr/bin/env python3
# Copyright (c) 2026 Huawei Technologies Co., Ltd.
# This program is free software, you can redistribute it and/or modify it under the terms and conditions of
# CANN Open Software License Agreement Version 2.0 (the "License").
# Please refer to the License for details. You may not use this file except in compliance with the License.
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
# INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
# See LICENSE in the root of the software repository for the full text of the License.

import subprocess
import sys
import tempfile
import unittest
from pathlib import Path


def find_generator_path():
    for parent in Path(__file__).resolve().parents:
        generator = parent / "cmake/stub/h2c.py"
        if generator.is_file():
            return generator
    raise RuntimeError("cannot locate cmake/stub/h2c.py")


GENERATOR_PATH = find_generator_path()


class H2cDefaultOutputTest(unittest.TestCase):
    def setUp(self):
        self.temp_dir = tempfile.TemporaryDirectory(prefix="runtime-h2c-")
        self.addCleanup(self.temp_dir.cleanup)
        self.root = Path(self.temp_dir.name)
        self.inputs = self.root / "input headers"
        self.inputs.mkdir()
        self.first = self.inputs / "driver.h"
        self.second = self.inputs / "extra.h"
        self.first.write_text("int drvExample(int value);\n", encoding="utf-8")
        self.second.write_text("int drvExtra(void);\n", encoding="utf-8")

    def run_generator(self, headers, output_args):
        result = subprocess.run(
            [sys.executable, str(GENERATOR_PATH), "-i", *map(str, headers), *output_args],
            cwd=self.root, text=True, capture_output=True, check=False,
        )
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)

    def assert_generated(self, output, include_extra=False):
        self.assertTrue(output.is_file())
        content = output.read_text(encoding="utf-8")
        self.assertIn('#include "driver.h"', content)
        self.assertIn("int drvExample(int value)", content)
        self.assertIn("return 0;", content)
        if include_extra:
            self.assertIn('#include "extra.h"', content)
            self.assertIn("int drvExtra(void)", content)
        self.assertFalse((self.inputs / "driver.c").exists())

    def test_omitted_output_uses_header_name_in_working_directory(self):
        self.run_generator([self.first], [])
        self.assert_generated(self.root / "driver.c")

    def test_multiple_headers_use_first_processed_header_name(self):
        self.run_generator([self.first, self.second], [])
        self.assert_generated(self.root / "driver.c", include_extra=True)
        self.assertFalse((self.root / "extra.c").exists())

    def test_bare_output_option_uses_default_name(self):
        self.run_generator([self.first], ["-o"])
        self.assert_generated(self.root / "driver.c")

    def test_skipped_non_header_does_not_determine_output_name(self):
        self.run_generator([self.inputs / "notes.txt", self.first], [])
        self.assert_generated(self.root / "driver.c")
        self.assertFalse((self.root / "notes.txt").exists())

    def test_explicit_relative_output_preserves_multi_header_content(self):
        self.run_generator([self.first, self.second], ["-o", "explicit output.c"])
        self.assert_generated(self.root / "explicit output.c", include_extra=True)
        self.assertFalse((self.root / "driver.c").exists())

    def test_explicit_absolute_output_is_preserved(self):
        output_dir = self.root / "output directory"
        output_dir.mkdir()
        output = output_dir / "absolute.c"
        self.run_generator([self.first], ["-o", str(output)])
        self.assert_generated(output)
        self.assertFalse((self.root / "driver.c").exists())


if __name__ == "__main__":
    unittest.main()
