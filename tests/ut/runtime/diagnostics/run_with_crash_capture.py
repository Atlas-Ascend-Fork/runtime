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

"""Run UT natively; collect stacks on fatal signals or before terminating a timed-out UT."""

import argparse
import json
import os
from pathlib import Path
import selectors
import signal
import socket
import struct
import subprocess
import sys
import tempfile
import time


EVENT = struct.Struct("=iiiiQQ")


class Cancelled(Exception):
    def __init__(self, signum):
        self.signum = signum


def cancel(signum, _frame):
    signal.signal(signal.SIGTERM, signal.SIG_IGN)
    signal.signal(signal.SIGINT, signal.SIG_IGN)
    raise Cancelled(signum)


def terminate_group(process, signum=signal.SIGTERM):
    if process.poll() is not None:
        return
    try:
        os.killpg(process.pid, signum)
        process.wait(timeout=2)
    except ProcessLookupError:
        pass
    except subprocess.TimeoutExpired:
        os.killpg(process.pid, signal.SIGKILL)
        process.wait()


def capture_stack(process, event, args):
    directory = Path(tempfile.mkdtemp(prefix=Path(args.command[0]).name + ".", dir=args.report_dir))
    metadata = {
        "pid": process.pid, "executable": os.path.realpath(args.command[0]),
        "command": args.command,
    }
    if event is None:
        metadata.update(reason="timeout", ut_timeout=args.ut_timeout, expected_exit_code=124)
        metadata_file = "timeout.json"
        header = f"UT timeout: PID={process.pid}; limit={args.ut_timeout}s"
        print(f"\n{header}; collecting stacks before termination", flush=True)
        print(f"UT timeout diagnostics: {directory}", flush=True)
    else:
        pid, tid, signum, code, address, pc = event
        metadata.update(
            reason="signal", pid=pid, tid=tid, signal=signum,
            signal_name=signal.Signals(signum).name, si_code=code,
            fault_address=hex(address), original_pc=hex(pc), expected_exit_code=128 + signum,
        )
        metadata_file = "crash.json"
        header = (f"Original signal: {metadata['signal_name']}; crash TID: {tid}; "
                  f"original PC: {hex(pc)}; fault address: {hex(address)}")
        print(f"\nUT crash: {metadata['signal_name']} PID={pid} TID={tid} "
              f"PC={hex(pc)} address={hex(address)}", flush=True)
        print(f"UT crash diagnostics: {directory}", flush=True)
    debugger = [
        "gdb", "-q", "-nx", "-batch",
        "-iex", "set auto-load off", "-iex", "set debuginfod enabled off",
        "-ex", "set pagination off", "-ex", f"attach {process.pid}",
        "-ex", "info threads", "-ex", "thread apply all bt full",
        "-ex", "info registers", "-ex", "info sharedlibrary", "-ex", "detach",
    ]
    environment = os.environ.copy()
    environment.pop("LD_PRELOAD", None)
    debugger_process = None
    try:
        with (directory / "stack.log").open("w") as output:
            output.write(header + "\n")
            output.flush()
            debugger_process = subprocess.Popen(debugger, stdout=output, stderr=subprocess.STDOUT,
                                                env=environment, start_new_session=True)
            try:
                metadata["gdb_exit_code"] = debugger_process.wait(timeout=args.gdb_timeout)
            except subprocess.TimeoutExpired:
                metadata["gdb_exit_code"] = 124
                output.write("\nWARNING: GDB stack collection timed out.\n")
    except OSError as error:
        metadata["gdb_exit_code"] = 127
        metadata["gdb_error"] = str(error)
    finally:
        if debugger_process is not None:
            terminate_group(debugger_process, signal.SIGKILL)
        (directory / metadata_file).write_text(json.dumps(metadata, indent=2) + "\n")
        if (directory / "stack.log").exists():
            with (directory / "stack.log").open(errors="replace") as output:
                for line in output:
                    print(line, end="")
        if metadata.get("gdb_exit_code") != 0:
            print("WARNING: GDB could not collect a complete stack; preserving the UT failure.",
                  file=sys.stderr, flush=True)


def supervise(args):
    parent, child = socket.socketpair(socket.AF_UNIX, socket.SOCK_SEQPACKET)
    environment = os.environ.copy()
    environment["RUNTIME_UT_CRASH_FD"] = str(child.fileno())
    environment["RUNTIME_UT_CRASH_WAIT_MS"] = str((args.gdb_timeout + 10) * 1000)
    if args.preload:
        environment["LD_PRELOAD"] = args.preload
    else:
        environment.pop("LD_PRELOAD", None)
    process = None
    pid_descriptor = None
    notified = False
    crash_signal = None
    ready = False
    deadline = time.monotonic() + args.ut_timeout if args.ut_timeout else None
    try:
        process = subprocess.Popen(args.command, env=environment, pass_fds=(child.fileno(),),
                                   start_new_session=True)
        child.close()
        with selectors.DefaultSelector() as selector:
            selector.register(parent, selectors.EVENT_READ, "notification")
            if hasattr(os, "pidfd_open"):
                try:
                    pid_descriptor = os.pidfd_open(process.pid)
                    selector.register(pid_descriptor, selectors.EVENT_READ, "exit")
                except OSError:
                    pass
            while process.poll() is None:
                remaining = None if deadline is None else max(0, deadline - time.monotonic())
                if remaining == 0:
                    if crash_signal is not None:
                        print("WARNING: UT did not exit after crash collection; terminating it and "
                              "preserving its original crash result.", file=sys.stderr, flush=True)
                        terminate_group(process)
                        return 128 + crash_signal
                    print(f"ERROR: UT timed out after {args.ut_timeout}s", file=sys.stderr, flush=True)
                    try:
                        capture_stack(process, None, args)
                    except OSError as error:
                        print(f"WARNING: Could not save timeout diagnostics: {error}",
                              file=sys.stderr, flush=True)
                    finally:
                        terminate_group(process)
                    return 124
                wait = remaining if pid_descriptor is not None else min(remaining or 0.5, 0.5)
                for key, _mask in selector.select(wait):
                    if key.data != "notification":
                        continue
                    try:
                        packet = parent.recv(EVENT.size)
                    except ConnectionResetError:
                        # The UT may exit without consuming the acknowledgement.
                        packet = b""
                    if not packet:
                        selector.unregister(parent)
                        continue
                    if len(packet) != EVENT.size:
                        continue
                    event = EVENT.unpack(packet)
                    if event[0] != process.pid:
                        continue
                    if event[2] == 0:
                        ready = True
                        if event[3]:
                            print(f"WARNING: UT PR_SET_PTRACER failed with errno {event[3]}; "
                                  "GDB attach may be denied.", file=sys.stderr, flush=True)
                    elif not notified:
                        notified = True
                        crash_signal = event[2]
                        try:
                            capture_stack(process, event, args)
                        except OSError as error:
                            print(f"WARNING: Could not save crash diagnostics: {error}",
                                  file=sys.stderr, flush=True)
                        finally:
                            # Release the bounded wait in the crashing thread, even on failure.
                            try:
                                parent.send(b"done")
                            except OSError:
                                pass
                        # Diagnosis has its own budget; do not overwrite the signal with a timeout.
                        deadline = time.monotonic() + 10
        result = process.wait()
        if not ready:
            print("WARNING: UT crash handler was not initialized; rebuild the Runtime UT executable.",
                  file=sys.stderr, flush=True)
        return 128 - result if result < 0 else result
    finally:
        child.close()
        parent.close()
        if pid_descriptor is not None:
            os.close(pid_descriptor)
        if process is not None:
            terminate_group(process)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--report-dir", required=True)
    parser.add_argument("--ut-timeout", type=int, default=0)
    parser.add_argument("--gdb-timeout", type=int, default=60)
    parser.add_argument("--preload", default="")
    parser.add_argument("command", nargs=argparse.REMAINDER)
    args = parser.parse_args()
    if args.command[:1] == ["--"]:
        args.command = args.command[1:]
    if not args.command or args.ut_timeout < 0 or not 1 <= args.gdb_timeout <= 240:
        parser.error("a command, nonnegative UT timeout, and GDB timeout in 1..240 seconds are required")
    Path(args.report_dir).mkdir(parents=True, exist_ok=True)
    signal.signal(signal.SIGTERM, cancel)
    signal.signal(signal.SIGINT, cancel)
    try:
        return supervise(args)
    except Cancelled as error:
        # Further termination signals should not interrupt cleanup.
        signal.signal(signal.SIGTERM, signal.SIG_IGN)
        signal.signal(signal.SIGINT, signal.SIG_IGN)
        return 128 + error.signum
    except OSError as error:
        print(f"ERROR: Cannot start UT: {error}", file=sys.stderr)
        return 127


if __name__ == "__main__":
    sys.exit(main())
