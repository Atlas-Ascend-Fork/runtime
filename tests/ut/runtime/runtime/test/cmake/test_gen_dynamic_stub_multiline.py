# -*- coding: utf-8 -*-
# -----------------------------------------------------------------------------------------------------------
# Copyright (c) 2026 Huawei Technologies Co., Ltd.
# This program is free software, you can redistribute it and/or modify it under the terms and conditions of
# CANN Open Software License Agreement Version 2.0 (the "License").
# Please refer to the License for details. You may not use this file except in compliance with the License.
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
# INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
# See LICENSE in the root of the software repository for the full text of the License.
# -----------------------------------------------------------------------------------------------------------
"""Host regressions for multiline ACL visibility declarations."""

import importlib.util
import os
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path


def find_generator_path():
    for parent in Path(__file__).resolve().parents:
        candidate = parent / "scripts/package/runtime/scripts/gen_dynamic_stub.py"
        if candidate.is_file():
            return candidate
    raise RuntimeError("cannot locate gen_dynamic_stub.py")


GENERATOR_PATH = find_generator_path()
REPO_ROOT = GENERATOR_PATH.parents[4]
SPEC = importlib.util.spec_from_file_location(
    "multiline_stub_generator", GENERATOR_PATH
)
GENERATOR = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(GENERATOR)

HEADER = """\
#pragma once
#define ACL_FUNC_VISIBILITY
using aclError = int;
using aclrtApiFunc = void (*)();
extern "C" {
ACL_FUNC_VISIBILITY aclError aclrtApiInjectionSetFuncImpl(const char* name, aclrtApiFunc func);
ACL_FUNC_VISIBILITY aclError
aclrtApiInjectionGetFuncImpl(const char* name, aclrtApiFunc* originFunc, aclrtApiFunc* currentFunc);
ACL_FUNC_VISIBILITY void aclFixtureVoidImpl(void);
}
"""
PROVIDER = """\
#include "acl_rt_impl.h"
#include <cstring>
void Original() {}
void Current() {}
extern "C" aclError aclrtApiInjectionGetFuncImpl(
    const char* name, aclrtApiFunc* originFunc, aclrtApiFunc* currentFunc)
{
    if (std::strcmp(name, "Host-query") != 0 || originFunc == nullptr || currentFunc == nullptr) {
        return 99;
    }
    *originFunc = Original;
    *currentFunc = Current;
    return 37;
}
"""
CALLER = """\
#include "acl_rt_impl.h"
int main()
{
    aclrtApiFunc original = nullptr;
    aclrtApiFunc current = nullptr;
    const aclError result = aclrtApiInjectionGetFuncImpl("Host-query", &original, &current);
    return (result == 37 && original != nullptr && current != nullptr && original != current) ? 0 : 1;
}
"""


class MultilineAclStubTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix="runtime-multiline-stub-")
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name).resolve()

    def test_actual_repository_header_retains_injection_getter(self):
        header = REPO_ROOT / "src/acl/aclrt_impl/acl_rt_impl.h"
        symbols = {entry.get("symbol") for entry in GENERATOR.collect_functions(header)}
        self.assertIn("aclrtApiInjectionGetFuncImpl", symbols)
        self.assertIn("aclrtApiInjectionSetFuncImpl", symbols)
        self.assertIn("aclAppLogImpl", symbols)

    def test_declaration_boundaries_preserve_separate_functions(self):
        header = self.root / "acl_rt_impl.h"
        header.write_text(HEADER, encoding="utf-8")
        entries = GENERATOR.collect_functions_from_visibility(header)
        self.assertEqual(
            [entry.get("symbol") for entry in entries],
            [
                "aclrtApiInjectionSetFuncImpl",
                "aclrtApiInjectionGetFuncImpl",
                "aclFixtureVoidImpl",
            ],
        )
        self.assertEqual(entries[1].get("call_args"), "(name, originFunc, currentFunc)")

    def run_checked(self, arguments):
        result = subprocess.run(arguments, capture_output=True, text=True, check=False)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        return result

    @unittest.skipUnless(
        os.name == "posix" and shutil.which("c++"), "POSIX Host C++ compiler required"
    )
    def test_generated_cli_stub_links_and_forwards_to_host_provider(self):
        (self.root / "acl_rt_impl.h").write_text(HEADER, encoding="utf-8")
        generated = self.root / "generated.cpp"
        self.run_checked(
            [
                sys.executable,
                str(GENERATOR_PATH),
                str(self.root),
                str(self.root),
                str(generated),
            ]
        )
        provider = self.root / "provider.cpp"
        provider.write_text(PROVIDER, encoding="utf-8")
        library_options = (
            ["-dynamiclib"] if sys.platform == "darwin" else ["-shared", "-fPIC"]
        )
        self.run_checked(
            [
                "c++",
                "-std=c++17",
                *library_options,
                str(provider),
                "-o",
                str(self.root / "libruntime.so"),
            ]
        )
        caller = self.root / "caller.cpp"
        caller.write_text(CALLER, encoding="utf-8")
        executable = self.root / "caller"
        link_options = [] if sys.platform == "darwin" else ["-ldl"]
        self.run_checked(
            [
                "c++",
                "-std=c++17",
                str(generated),
                str(caller),
                *link_options,
                "-o",
                str(executable),
            ]
        )
        self.run_checked([str(executable)])


if __name__ == "__main__":
    unittest.main()
