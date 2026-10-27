#!/usr/bin/env python3
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

"""Unpacking the same log twice must replace its previous output."""

import gzip
import importlib.util
import tempfile
import unittest
from pathlib import Path


def find_unzip_tool():
    for parent in Path(__file__).resolve().parents:
        candidate = parent / "src/dfx/log/syslog/scripts/unzip_tool.py"
        if candidate.is_file():
            return candidate
    raise RuntimeError("cannot locate unzip_tool.py")


class RepeatedLogUnpackTest(unittest.TestCase):
    def test_repeated_log_unpack_replaces_previous_output(self):
        spec = importlib.util.spec_from_file_location("runtime_log_unzip", find_unzip_tool())
        tool = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(tool)
        payload = b"first log line\nsecond log line\n"
        compressed = gzip.compress(payload, compresslevel=6, mtime=0)
        compressed = tool.GZIP_HEAD + compressed[len(tool.GZIP_HEAD):]
        chunks = compressed.split(tool.GZIP_HEAD)
        with tempfile.TemporaryDirectory(prefix="runtime-log-unpack-") as directory:
            target = Path(directory) / "runtime.log"
            tool.unzip_file(chunks, target)
            self.assertEqual(target.read_bytes(), payload)
            tool.unzip_file(chunks, target)
            self.assertEqual(target.read_bytes(), payload)


if __name__ == "__main__":
    unittest.main(verbosity=2)
