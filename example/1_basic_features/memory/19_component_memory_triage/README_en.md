# 19_component_memory_triage

## Description

This sample helps operators investigate component memory usage on a single device. It reads component names, current usage, and historical peaks, applies per-component thresholds, and prints a report sorted by current usage in descending order.

The default current-usage limit is 64 MiB and the peak limit is 128 MiB. If any component reaches the current limit, the report prioritizes the component with the largest current usage. Otherwise, if a peak reaches the peak limit, it recommends reviewing the component with the largest peak. If neither limit is reached, it prints `WITHIN_BUDGET`. Runtime arguments can adjust these limits. A diagnostic recommendation does not indicate a program failure.

The sample checks the returned count, component names, current usage against peaks, and descending current usage. When the query array is full, it increases the requested count and fetches a new snapshot, up to 256 entries. If the array remains full, it fails without printing a complete report. This is a sample capacity guard, not an API limit on the number of components.

Counters use bytes, while threshold arguments use MiB (1 MiB = 1048576 bytes). These statistics do not represent free allocatable memory and do not establish the exact change from an application allocation, the time of a peak, or a memory leak.

## Product Support

| Product | Supported |
| --- | --- |
| A2 (Atlas A2 series products) | Yes |
| A3 (Atlas A3 series products) | Yes |
| A5 (Ascend 950PR/Ascend 950DT) | No |


## Compile and Run

Install CANN, prepare a supported device, set the actual installation path, and run:

```bash
export ASCEND_INSTALL_PATH=<CANN-installation-directory>
cd <runtime-repository>/example/1_basic_features/memory/19_component_memory_triage
bash run.sh
```

The script loads the CANN environment, builds in `build/`, and runs on visible device 0. The optional arguments are the current-usage limit followed by the peak limit, both positive decimal integers in MiB. If only the first argument is supplied, the peak limit retains its default value.

```bash
bash run.sh 1 128
bash run.sh 64 1
```

On the tested system, where component usage was about 28 MiB, these commands printed `CURRENT_PRESSURE` and `HISTORICAL_PEAK`, respectively. The actual decision depends on the runtime snapshot; adjust thresholds using the reported values to reproduce it. Invalid arguments, query failures, invalid data, and cleanup failures produce a nonzero exit code without a success marker.

## CANN RUNTIME API

The key features and interfaces used in this sample are:

- Initialization and single-device binding:
  - `aclInit`: Initializes the runtime configuration.
  - `aclrtSetDevice`: Binds visible device 0.
- Component memory investigation:
  - `aclrtGetMemUsageInfo`: Queries component names, current usage, and peaks to determine investigation priorities. (Supported on A2 and A3; unsupported on A5.)
- Resource cleanup:
  - `aclrtResetDevice`: Releases resources for the bound device.
  - `aclFinalize`: Finalizes the runtime.

## Sample Output

The following is a successful run with the default limits, excluding build logs. Component names, counts, and counters vary by environment.

```text
[INFO]  Complete component snapshot: device=0 components=... capacity=8
[INFO]  Verified component names, current <= peak, and descending current usage
[INFO]  Per-component limits: current=67108864 bytes peak=134217728 bytes
[INFO]  Component[0] RUNTIME current=... bytes peak=... bytes
[INFO]  Triage: WITHIN_BUDGET; all reported components are below both limits
[INFO]  Component memory triage succeeded
```
