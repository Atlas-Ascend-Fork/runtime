/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 * This program is free software, you can redistribute it and/or modify it under the terms and conditions of
 * CANN Open Software License Agreement Version 2.0 (the "License").
 * Please refer to the License for details. You may not use this file except in compliance with the License.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 * See LICENSE in the root of the software repository for the full text of the License.
 */
#include <cerrno>
#include <climits>
#include <cstdint>
#include <cstdlib>
#include <fcntl.h>
#include <poll.h>
#include <signal.h>
#include <sys/prctl.h>
#include <sys/socket.h>
#include <sys/syscall.h>
#include <time.h>
#include <ucontext.h>
#include <unistd.h>

namespace {
// This fixed-size packet is also decoded by run_with_crash_capture.py.
struct CrashEvent {
    int32_t pid;
    int32_t tid;
    int32_t signal;
    int32_t code;
    uint64_t address;
    uint64_t pc;
};
static_assert(sizeof(CrashEvent) == 32, "Crash notification wire format changed");
static_assert(__atomic_always_lock_free(sizeof(int), nullptr), "Signal guard must be lock-free");

constexpr int FATAL_SIGNALS[] = {SIGSEGV, SIGABRT, SIGBUS, SIGILL, SIGFPE, SIGSYS};
int g_channel = -1;
int g_waitMs = 70000;
pid_t g_owner = 0;
int g_notified = 0;

int64_t MonotonicMs()
{
    struct timespec now = {};
    if (clock_gettime(CLOCK_MONOTONIC, &now) != 0) {
        return -1;
    }
    return static_cast<int64_t>(now.tv_sec) * 1000 + now.tv_nsec / 1000000;
}

void WaitForCollector()
{
    const int64_t start = MonotonicMs();
    if (start < 0) {
        return;
    }
    struct pollfd descriptor = {g_channel, POLLIN, 0};
    while (true) {
        const int64_t now = MonotonicMs();
        if (now < 0 || now - start >= g_waitMs) {
            return;
        }
        const int ret = poll(&descriptor, 1, static_cast<int>(g_waitMs - (now - start)));
        // An acknowledgement, collector death (HUP), error, or timeout all release us.
        if (ret >= 0 || errno != EINTR) {
            return;
        }
    }
}

void CrashHandler(int signum, siginfo_t* info, void* context)
{
    const pid_t pid = getpid();
    const pid_t tid = static_cast<pid_t>(syscall(SYS_gettid));
    // Forked death-test children must not pause or report their expected crashes.
    if (pid == g_owner) {
        if (__atomic_exchange_n(&g_notified, 1, __ATOMIC_RELAXED) == 0) {
            CrashEvent event = {pid, tid, signum, info == nullptr ? 0 : info->si_code, 0, 0};
            if (info != nullptr && (signum == SIGSEGV || signum == SIGBUS)) {
                event.address = reinterpret_cast<uintptr_t>(info->si_addr);
            }
            if (context != nullptr) {
                const auto* registers = static_cast<const ucontext_t*>(context);
#if defined(__x86_64__)
                event.pc = static_cast<uint64_t>(registers->uc_mcontext.gregs[REG_RIP]);
#elif defined(__aarch64__)
                event.pc = static_cast<uint64_t>(registers->uc_mcontext.pc);
#else
                (void)registers;
#endif
            }
            if (send(g_channel, &event, sizeof(event), MSG_DONTWAIT | MSG_NOSIGNAL) == sizeof(event)) {
                WaitForCollector();
            }
        } else {
            WaitForCollector();
        }
    }

    // Queue the original signal for this thread, then return through its signal frame.
    // No allocation, symbolization, logging locks, or subprocess creation happens here.
    struct sigaction action = {};
    action.sa_handler = SIG_DFL;
    sigemptyset(&action.sa_mask);
    (void)sigaction(signum, &action, nullptr);
    (void)syscall(SYS_tgkill, pid, tid, signum);
}

int ParseDescriptor(const char* value)
{
    if (value == nullptr || *value == '\0') {
        return -1;
    }
    char* end = nullptr;
    errno = 0;
    const long descriptor = strtol(value, &end, 10);
    if (errno != 0 || *end != '\0' || descriptor < 3 || descriptor > INT_MAX) {
        return -1;
    }
    return static_cast<int>(descriptor);
}

__attribute__((constructor)) void InitializeCrashDiagnostics()
{
    // Direct execution and unrelated programs remain completely inactive.
    g_channel = ParseDescriptor(getenv("RUNTIME_UT_CRASH_FD"));
    int socketType = 0;
    socklen_t typeSize = sizeof(socketType);
    if (g_channel < 0 || getsockopt(g_channel, SOL_SOCKET, SO_TYPE, &socketType, &typeSize) != 0 ||
        socketType != SOCK_SEQPACKET) {
        return;
    }
    (void)fcntl(g_channel, F_SETFD, FD_CLOEXEC);
    g_owner = getpid();
    const int configuredWait = ParseDescriptor(getenv("RUNTIME_UT_CRASH_WAIT_MS"));
    if (configuredWait >= 1000 && configuredWait <= 300000) {
        g_waitMs = configuredWait;
    }

    // Yama mode 1 permits this parent and its debugger children, not arbitrary processes.
    const int ptraceError = prctl(PR_SET_PTRACER, getppid(), 0, 0, 0) == 0 ? 0 : errno;
    struct sigaction action = {};
    action.sa_sigaction = CrashHandler;
    action.sa_flags = SA_SIGINFO;
    sigemptyset(&action.sa_mask);
    for (const int signum : FATAL_SIGNALS) {
        sigaddset(&action.sa_mask, signum);
    }
    for (const int signum : FATAL_SIGNALS) {
        struct sigaction previous = {};
        // Do not replace a handler installed before this object's constructor.
        if (sigaction(signum, nullptr, &previous) == 0 && previous.sa_handler == SIG_DFL) {
            (void)sigaction(signum, &action, nullptr);
        }
    }
    const CrashEvent ready = {g_owner, 0, 0, ptraceError, 0, 0};
    (void)send(g_channel, &ready, sizeof(ready), MSG_DONTWAIT | MSG_NOSIGNAL);
}
} // namespace
