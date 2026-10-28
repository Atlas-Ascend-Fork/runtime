# Add Batch and Operation Descriptions to ACL Graph Tasks

## Description

When inspecting an ACL Graph debug file, task types and IDs alone can make it difficult to tell which batch a task processes or what it does. This sample adds batch IDs and operation descriptions so that readers can identify the corresponding data processing steps in the graph.

The sample represents two batches using fixed byte values. Both batches share one 4096-byte Device buffer and run in order:

1. **Batch 0**: Fill every byte of the buffer with 17, then copy it to batch 0's separate output region.
2. **Batch 1**: Reuse the same buffer, fill every byte with 34, then copy it to batch 1's separate output region.

Each batch has a fill task and a copy task. The sample attaches a batch ID and operation name to each of these four tasks and exports `graph_task_annotations.json` for readers to inspect their purpose.

The program then executes the graph and reads back the results: all 4096 bytes of batch 0 must be 17, and all bytes of batch 1 must be 34. This also checks that reusing the shared buffer for the second batch preserves the first batch's saved output.

## Product Support

| Product | Supported |
| --- | --- |
| Atlas A2 series products | Yes |
| Atlas A3 series products | Yes |
| Ascend 950PR/Ascend 950DT | Yes |


## Compile and Run

Requires CMake, a C++17 compiler, Make, and an available supported Device. The program uses visible logical Device 0. Run `npu-smi info` first to confirm the product is supported.

```bash
cd ${git_clone_path}/example/2_advanced_features/model_ri/6_graph_task_annotation
# Replace ${install_root} with the CANN installation root.
export ASCEND_INSTALL_PATH=${install_root}/cann
source "${ASCEND_INSTALL_PATH}/set_env.sh"
bash run.sh
```

The script builds and runs `build/main`, exports `build/graph_task_annotations.json`, and verifies the output of both batches byte by byte. Program logs are printed to the terminal and saved to `output_msg.txt` in the sample directory. Any build, API, cleanup, or data verification failure produces a nonzero exit status. The program prints `Graph execution and data verification passed` only after all checks succeed.

Inspect the task annotations:

1. Open `chrome://tracing/` in Chrome and load `build/graph_task_annotations.json`.
2. Select a task and inspect `args.ExtendInfo` in its details. `batch_id` identifies the data batch, `op_name` names the operation, and `description` explains it.
3. For example, a task with `batch_id=1` and `op_name=ArchiveBatch` copies batch 1 to its own output region. That batch has `marker=34`. Use the task's `Model Id`, `Stream Id`, and `Task Id` to correlate it with other logs.

The annotation names map to these actions:

| `op_name` | `business_phase` | Action |
| --- | --- | --- |
| `FillBatchMarker` | `prepare` | Fill every byte of the shared buffer with the batch's fixed value |
| `ArchiveBatch` | `archive` | Copy the shared buffer to the batch's separate Device output region |

The program automatically checks the output data for both batches. Inspect the annotations using the steps above. The debug JSON shows graph structure; gaps and lengths on its timeline do not represent actual execution time.

## CANN RUNTIME API

The key functions and interfaces used in this sample are as follows:

- Initialization and resource management
    - `aclInit`, `aclFinalize`: Initialize and finalize the environment.
    - `aclrtSetDevice`, `aclrtResetDeviceForce`: Bind and release single-Device resources.
    - `aclrtMalloc`, `aclrtFree`: Allocate and release the reusable buffer and batch output regions.
    - `aclrtCreateStream`, `aclrtDestroyStream`: Create and destroy the task Stream.
- Capture and task annotation
    - `aclmdlRICaptureBegin`, `aclmdlRICaptureEnd`: Begin and end ACL Graph capture on one Stream.
    - `aclrtSetStreamAttribute`, `aclrtGetStreamAttribute`: Set and check the `ACL_STREAM_ATTR_CACHE_OP_INFO` operator information cache switch.
    - `aclrtCacheLastTaskOpInfo`: Cache the operator description for the last task submitted by the current thread for subsequent profiling data collection; the Host buffer size must be in `(0, 64KB]`. This sample describes the annotation name, data type, and element count.
    - `aclrtCacheLastTaskExtendInfo`: Cache UTF-8 JSON containing the batch ID and operation description for the same task. It is exported in `args.ExtendInfo`, and its size must be in `(0, 4KB]`. The sample passes the actual string byte count without a trailing null character.
- Batch processing and result verification
    - `aclrtMemset`: Initialize output to a value different from the expected results before capture.
    - `aclrtMemsetAsync`: Record the batch marker fill task.
    - `aclrtMemcpyAsync`: Record the task that copies the batch to its separate Device output region.
    - `aclmdlRIDebugJsonPrint`: Export debug JSON containing the business extensions.
    - `aclmdlRIExecuteAsync`, `aclrtSynchronizeStream`: Execute the graph and wait for completion.
    - `aclrtMemcpy`: Read back output to the Host and verify each batch marker byte by byte.
    - `aclmdlRIDestroy`: Destroy the model runtime instance and cached information before releasing buffers referenced by the graph.

Task submission and both cache calls run on the same Host thread with no intervening task submission. No synchronization occurs during capture. Device buffers and Host annotation strings remain valid until the model is destroyed.

## Sample Output

A successful run reports the export path and verification results for both batches.


```text
[INFO]  Exported annotated graph: graph_task_annotations.json
[INFO]  Batch 0 verified: 4096 bytes, marker=17
[INFO]  Batch 1 verified: 4096 bytes, marker=34
[INFO]  Graph execution and data verification passed
```
