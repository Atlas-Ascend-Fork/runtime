#!/usr/bin/env python3
# Copyright (c) 2026 Huawei Technologies Co., Ltd.
# This program is free software, you can redistribute it and/or modify it under the terms and conditions of
# CANN Open Software License Agreement Version 2.0 (the "License").
# Please refer to the License for details. You may not use this file except in compliance with the License.
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
# INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
# See LICENSE in the root of the software repository for the full text of the License.

import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path


def find_generator():
    for parent in Path(__file__).resolve().parents:
        path = parent / "src/dfx/error_manager/stub/gen_stubapi.py"
        if path.is_file():
            return path
    raise RuntimeError("cannot locate error_manager stub generator")


GENERATOR = find_generator()
HEADER = "#include <stdint.h>\nint32_t example(int32_t value);\n"
TRAILERS = {
    "blank": "\n",
    "multiple_blanks": "\n\n\n",
    "spaces": "   \n",
    "tabs_without_newline": "\t\t",
    "line_comment": "// trailing comment\n",
    "line_comment_without_newline": "// trailing comment",
    "block_comment": "/* trailing comment */\n",
    "block_comment_without_newline": "/* trailing comment */",
    "multiline_block": "/* trailing\n * comment\n */\n",
    "define": "#define SENTINEL 1\n",
    "define_without_newline": "#define SENTINEL 1",
    "continued_define": "#define SENTINEL \\\n    1\n",
    "mixed": "\n// comment\n/* block */\n#define SENTINEL 1\n\n",
    "crlf_blanks": "\r\n\r\n",
    "crlf_comment": "// comment\r\n",
    "crlf_block": "/* comment\r\n */\r\n",
}


class ErrorManagerStubEofTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix="error-manager-stub-eof-")
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.input = self.root / "headers"
        self.output = self.root / "output"
        self.input.mkdir()
        self.output.mkdir()
        self.header = self.input / "err_msg.h"
        self.generated = self.output / "stub_err_msg.cc"

    def generate(self, header):
        self.header.write_bytes(header.encode("utf-8"))
        result = subprocess.run(
            [sys.executable, str(GENERATOR), str(self.input), str(self.output)],
            capture_output=True, text=True, check=False,
        )
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertTrue(self.generated.is_file())
        return self.generated.read_bytes()

    def test_valid_trailers_preserve_generated_source(self):
        expected = self.generate(HEADER)
        for name, trailer in TRAILERS.items():
            with self.subTest(trailer=name):
                self.assertEqual(self.generate(HEADER + trailer), expected)

    def test_comment_only_header_reaches_eof(self):
        for name, trailer in TRAILERS.items():
            with self.subTest(trailer=name):
                source = self.generate(trailer)
                self.assertNotIn(b"example(", source)

    def test_ignored_input_between_declarations_preserves_both_functions(self):
        header = HEADER + "\n// middle comment\n/* middle block */\n#define SENTINEL 1\n"
        source = self.generate(header + "int32_t second(int32_t value);\n")
        self.assertIn(b"int32_t example(int32_t value)", source)
        self.assertIn(b"int32_t second(int32_t value)", source)

    def test_unterminated_trailing_block_preserves_declarations(self):
        expected = self.generate(HEADER)
        for trailer in ["/* trailing", "/* trailing\n * comment"]:
            with self.subTest(trailer=trailer):
                self.assertEqual(self.generate(HEADER + trailer), expected)

    def test_unterminated_comment_only_header_reaches_eof(self):
        for trailer in ["/* trailing", "/* trailing\n * comment"]:
            with self.subTest(trailer=trailer):
                self.assertNotIn(b"example(", self.generate(trailer))

    def test_generated_stub_compiles_and_runs_on_host(self):
        compiler = shutil.which("clang++") or shutil.which("g++")
        self.assertIsNotNone(compiler, "Host C++ compiler required for generated stub validation")
        self.generate(HEADER)
        library = self.root / "stub.so"
        result = subprocess.run(
            [compiler, "-shared", "-fPIC", "-Wall", "-Werror", "-I", str(self.input),
             str(self.generated), "-o", str(library)],
            capture_output=True, text=True, check=False,
        )
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        # Exercise the compiled shared library through its public C++ declaration.
        # This avoids coupling a C++ generator test to the runner's Python/libffi ABI.
        consumer = self.root / "consumer.cpp"
        consumer.write_text('#include "err_msg.h"\nint main() { return example(19) == 0 ? 0 : 1; }\n')
        executable = self.root / "consumer"
        result = subprocess.run(
            [compiler, "-Wall", "-Werror", "-I", str(self.input),
             str(consumer), str(library), "-o", str(executable)],
            capture_output=True, text=True, check=False,
        )
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        result = subprocess.run([str(executable)], capture_output=True, text=True, check=False)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)


if __name__ == "__main__":
    unittest.main()
