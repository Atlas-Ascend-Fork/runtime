# Runtime Architecture Documentation

This documentation set describes the CANN Runtime architecture design and is intended **for you if you want to contribute code to the Runtime**.

## Architecture Overview

| Document | Description |
|------|------|
| [architecture.md](architecture.md) | System architecture overview, which describes the overall Runtime design and core components |

## Module Architecture Documentation

| Document | Description |
|------|------|
| [modules/runtime/runtime.md](modules/runtime/runtime.md) | Runtime global management: singleton pattern and resource management |
| [modules/device/device.md](modules/device/device.md) | Device management: device initialization, state management, and error handling |
| [modules/stream/stream.md](modules/stream/stream.md) | Stream management: task queues and synchronization mechanisms |
| [modules/task/task.md](modules/task/task.md) | Task management: task types and execution flows |
| [modules/context/context.md](modules/context/context.md) | Context management: relationships with Device/Stream |
| [modules/memory/memory.md](modules/memory/memory.md) | Memory management: memory pools and allocation policies |
| [modules/kernel/kernel.md](modules/kernel/kernel.md) | Kernel management: binary loading and execution |
| [modules/event/event.md](modules/event/event.md) | Event management: synchronization mechanisms |

## Feature Documentation

| Document | Description |
|------|------|
| [features/aclgraph.md](features/aclgraph.md) | ACL Graph feature: stream capture and model building |
| [features/snapshot.md](features/snapshot.md) | Snapshot feature: process state backup and restore |
| [features/fusion.md](features/fusion.md) | Fusion feature: fused operator execution |

---

## How to Use These Documents

### Recommended Reading Order

1. **Beginners**: Read [architecture.md](architecture.md) first to understand the overall architecture.
2. **Module development**: Read the documentation for the module that interests you.
3. **Feature development**: Refer to the feature documentation in the features/ directory.

### Reading Paths for Different Roles

- **Runtime core developers**: architecture → runtime → device → stream → task
- **Driver adaptation developers**: architecture → device → stream
- **Performance optimization developers**: memory → stream → task
- **Feature developers**: architecture → the corresponding feature document

---

## Project Structure

```
runtime/
├── api/                    # API layer
│   ├── api.hpp             # Runtime API definitions
│   ├── api_c_*.cc          # C API implementations
│   └── impl/               # Internal API implementations
├── core/
│   ├── inc/                # Internal header files
│   └── src/                # Core implementations
│       ├── runtime.cc      # Runtime global management
│       ├── device/         # Device module
│       ├── stream/         # Stream module
│       ├── task/           # Task module
│       ├── context/        # Context module
│       ├── kernel/         # Kernel module
│       ├── event/          # Event module
│       ├── engine/         # Engine scheduling
│       ├── memory/         # Memory module
│       ├── profiler/       # Profiler performance analysis
│       ├── launch/         # Kernel Launch
│       ├── notify/         # Notify notifications
│       └── dfx/            # DFX functions
├── driver/                 # Driver adaptation layer
│   ├── v100/               # v100 driver
│   ├── v200/               # v200 driver
│   └── v201/               # v201 driver
├── feature/                # Feature implementations
│   ├── aclgraph/           # ACL Graph stream capture
│   ├── snapshot/           # Snapshot process snapshot
│   ├── model/              # Model management
│   ├── soma/               # SOMA feature
│   ├── ccu/                # CCU feature
│   ├── cntnotify/          # Count Notify
│   ├── xpu/                # XPU feature
│   ├── fusion/             # Fusion
│   ├── dqs/                # DQS feature
│   └── ffts/               # FFTS feature
├── config/                 # Hardware difference configurations
│   ├── as31xm1/            # AS31XM1 chip configuration
│   ├── bs9sx1a/            # BS9SX1A chip configuration
│   ├── 910_B_93/           # 910B chip configuration
│   └── ...                 # Other chip configurations
├── inc/                    # Public header files
│   ├── device/             # Device-related header files
│   └── sqe/                # SQE-related header files
└── cmake/                  # Build configuration
```

---

_This documentation follows the open source repository architecture documentation template format._
