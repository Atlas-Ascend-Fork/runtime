#!/usr/bin/env python3
# Copyright (c) 2026 Huawei Technologies Co., Ltd.
# This program is free software, you can redistribute it and/or modify it under the terms and conditions of
# CANN Open Software License Agreement Version 2.0 (the "License").
# Please refer to the License for details. You may not use this file except in compliance with the License.
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
# INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
# See LICENSE in the root of the software repository for the full text of the License.
"""Host regression tests for the Python/native logging boundary, without an SDK.

The small C library implements the public variadic ABI and captures formatted
output. It is a test double, not the deployed libascendalog.so. Unsafe raw format
strings are rejected before reading any absent argument on the old Python code.
"""

import json
import os
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path


C_SOURCE = r"""
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static char message[8192];
static char format[8192];
static int32_t module_id;
static int32_t log_level;
static int32_t event_enabled;
static int rejected;
static int calls;

static int IsZeroArgumentFormat(const char *fmt)
{
    for (const char *ptr = fmt; *ptr != '\0'; ++ptr) {
        if (*ptr == '%') {
            if (ptr[1] != '%') {
                return 0;
            }
            ++ptr;
        }
    }
    return 1;
}

void DlogRecordForC(int32_t module, int32_t level, const char *fmt, ...)
{
    module_id = module;
    log_level = level;
    ++calls;
    (void)snprintf(format, sizeof(format), "%s", fmt);
    if (strcmp(fmt, "%s") != 0 && !IsZeroArgumentFormat(fmt)) {
        rejected = 1;
        return; /* Never consume missing varargs in baseline tests. */
    }
    va_list args;
    va_start(args, fmt);
    (void)vsnprintf(message, sizeof(message), fmt, args);
    va_end(args);
}

void DlogSetlevelForC(int32_t module, int32_t level, int32_t event)
{
    module_id = module;
    log_level = level;
    event_enabled = event;
    ++calls;
}

void ResetCapture(void)
{
    message[0] = '\0';
    format[0] = '\0';
    module_id = 0;
    log_level = 0;
    event_enabled = 0;
    rejected = 0;
    calls = 0;
}

const char *CapturedMessage(void) { return message; }
const char *CapturedFormat(void) { return format; }
int32_t CapturedModule(void) { return module_id; }
int32_t CapturedLevel(void) { return log_level; }
int32_t CapturedEvent(void) { return event_enabled; }
int CapturedRejected(void) { return rejected; }
int CapturedCalls(void) { return calls; }
"""


CHILD = r"""
import ctypes
import importlib.util
import json
import sys

spec = importlib.util.spec_from_file_location("ascend_log_under_test", sys.argv[1])
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
logger = module.LOGGER
native = logger.log
assert native is not None, "test native library was not loaded"
native.CapturedMessage.restype = ctypes.c_char_p
native.CapturedFormat.restype = ctypes.c_char_p
results = []
for case in json.loads(sys.stdin.read()):
    native.ResetCapture()
    if case.get("disabled"):
        logger.log = None
    if case["method"] == "set_level":
        logger.set_level(case["module"], case["level"], case["event"])
    else:
        getattr(logger, case["method"])(case["module"], case["text"])
    logger.log = native
    results.append({
        "message": native.CapturedMessage().decode("utf-8"),
        "format": native.CapturedFormat().decode("utf-8"),
        "module": native.CapturedModule(),
        "level": native.CapturedLevel(),
        "event": native.CapturedEvent(),
        "rejected": native.CapturedRejected(),
        "calls": native.CapturedCalls(),
    })
argtypes = native.DlogRecordForC.argtypes
print(json.dumps({
    "results": results,
    "fixed_argument_types": argtypes == [ctypes.c_int, ctypes.c_int, ctypes.c_char_p],
    "void_return_type": native.DlogRecordForC.restype is None,
}, ensure_ascii=False))
"""


LEVELS = {"debug": 0, "info": 1, "warn": 2, "error": 3, "event": 16}


def find_source():
    override = os.environ.get("ASCEND_LOG_SOURCE")
    if override:
        return Path(override)
    for parent in Path(__file__).resolve().parents:
        source = parent / "src/dfx/log/python/AscendLog.py"
        if source.is_file():
            return source
    raise RuntimeError("cannot locate AscendLog.py")


class AscendLogTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        compiler = shutil.which("cc") or shutil.which("clang") or shutil.which("gcc")
        if compiler is None:
            raise RuntimeError("these Host ABI tests require a C compiler")
        cls.temp_dir = tempfile.TemporaryDirectory(prefix="ascend-log-abi-")
        cls.addClassCleanup(cls.temp_dir.cleanup)
        cls.library_dir = Path(cls.temp_dir.name)
        source = cls.library_dir / "capture.c"
        source.write_text(C_SOURCE, encoding="utf-8")
        command = [compiler, "-std=c99", "-Wall", "-Wextra", "-Werror"]
        command += ["-dynamiclib"] if sys.platform == "darwin" else ["-shared", "-fPIC"]
        command += [str(source), "-o", str(cls.library_dir / "libascendalog.so")]
        subprocess.run(command, check=True, capture_output=True, text=True, timeout=60)

    def run_cases(self, cases):
        environment = os.environ.copy()
        environment.pop("PYTHONHOME", None)
        environment.pop("PYTHONPATH", None)
        library_paths = [str(self.library_dir)]
        if environment.get("LD_LIBRARY_PATH"):
            library_paths.append(environment["LD_LIBRARY_PATH"])
        environment["LD_LIBRARY_PATH"] = os.pathsep.join(library_paths)
        result = subprocess.run(
            [sys.executable, "-c", CHILD, str(find_source())],
            input=json.dumps(cases, ensure_ascii=False),
            capture_output=True,
            text=True,
            env=environment,
            check=False,
            timeout=30,
        )
        self.assertEqual(result.returncode, 0, result.stderr)
        return json.loads(result.stdout)

    def check_messages(self, texts):
        cases = [
            {"method": method, "module": 57, "text": text}
            for method in LEVELS for text in texts
        ]
        results = self.run_cases(cases)["results"]
        self.assertEqual(len(results), len(cases))
        for case, result in zip(cases, results):
            with self.subTest(method=case["method"], text=case["text"]):
                self.assertEqual(result["rejected"], 0, "raw format reached native boundary")
                self.assertEqual(result["message"], case["text"].split("\0", 1)[0])
                self.assertEqual(result["module"], 57)
                self.assertEqual(result["level"], LEVELS[case["method"]])
                self.assertEqual(result["calls"], 1)

    def test_percent_pairs_are_literal_content(self):
        self.check_messages(["progress=100%%", "%%%%", "ratio %% done", "中文%%🧪"])

    def test_format_tokens_are_literal_content(self):
        self.check_messages(["value=%s", "value=%d", "value=%n", "percent=100%"])

    def test_ordinary_content_and_c_string_boundary(self):
        self.check_messages(["", "plain message", "中文 café 🧪\nline 2", "x" * 4096, "before\0after"])

    def test_module_and_level_routing(self):
        cases = [
            {"method": method, "module": module, "text": "routing"}
            for method in LEVELS for module in [8, 33, 57]
        ]
        for case, result in zip(cases, self.run_cases(cases)["results"]):
            with self.subTest(method=case["method"], module=case["module"]):
                self.assertEqual(result["module"], case["module"])
                self.assertEqual(result["level"], LEVELS[case["method"]])
                self.assertEqual(result["message"], "routing")
                self.assertEqual(result["calls"], 1)

    def test_native_format_and_variadic_prototype(self):
        cases = [{"method": method, "module": 8, "text": "ordinary"} for method in LEVELS]
        output = self.run_cases(cases)
        for case, result in zip(cases, output["results"]):
            with self.subTest(method=case["method"]):
                self.assertEqual(result["format"], "%s")
                self.assertEqual(result["message"], "ordinary")
        self.assertTrue(output["fixed_argument_types"])
        self.assertTrue(output["void_return_type"])

    def test_disabled_logger_is_noop(self):
        cases = [
            {"method": method, "module": 8, "text": "value=%s", "disabled": True}
            for method in LEVELS
        ]
        for case, result in zip(cases, self.run_cases(cases)["results"]):
            with self.subTest(method=case["method"]):
                self.assertEqual(result["calls"], 0)
                self.assertEqual(result["message"], "")

    def test_set_level_is_unchanged(self):
        cases = [
            {"method": "set_level", "module": 8, "level": level, "event": event}
            for level in [0, 1, 2, 3, 4, 16] for event in [0, 1]
        ]
        for case, result in zip(cases, self.run_cases(cases)["results"]):
            with self.subTest(level=case["level"], event=case["event"]):
                self.assertEqual(result["module"], 8)
                self.assertEqual(result["level"], case["level"])
                self.assertEqual(result["event"], case["event"])
                self.assertEqual(result["calls"], 1)


if __name__ == "__main__":
    unittest.main(verbosity=2)
