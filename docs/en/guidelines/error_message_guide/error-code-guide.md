# Runtime Error Code Usage Specifications (EE/EH Series)

## Overview

CANN Runtime has two layers of error codes: **the EE series** (Runtime core layer, `src/runtime/`) and **the EH series** (ACL external API layer, `src/acl/`). Error code selection must follow the scenario priority, and using fallback codes at will is prohibited. Currently, only external user errors are analyzed.

**Core usage principles**:

1. **Determine the layer**: Code in `src/runtime/` → EE; code in `src/acl/` → EH
2. **Determine the scenario**: Select the optimal error code according to the decision tree. When selecting, confirm that the predefined suggestion of the code provides practical guidance for the current scenario. If the suggestion does not match the scenario, select a more appropriate error code. Do not use fallback codes unless the error really cannot be classified
3. **⛔ Prohibited codes**: EE1001/EH0001/EH0002 are only for fallback use. Runtime/ACL should not add new invocations of them
4. **Pre-use check**: Before each use of this specification, compare against `src/dfx/error_manager/error_code.json` to check whether any EE/EH error codes are added or modified (ErrCode, ErrMessage, Arglist). If there are changes:
   - Temporarily analyze, summarize, and update the changed content into the corresponding scenarios of this document only **during the current invocation**
   - After the current invocation is complete, **restore the document to its existing rules** and delete the temporary update content
   - Purpose: Ensure that the standardization of this document is not broken by a single change. New codes should be officially incorporated after review
5. **Post-use check**: After selecting an error code, check against the "Common Errors" section one by one to confirm that you do not fall into known pitfalls

**Annotation notes**: ⛔ = fallback code (do not add new invocations); 🔸 = defined but not actually used in the source code; ⭐ = code preferred among similar scenarios.

## EE Error Code Overview Table

| ErrCode | errTitle (Category) | Arglist | ErrMessage | suggestion | Usage Scenario | Usage Example | Screen Output | Description |
|---------|---------------|---------|------------|------------|---------|---------|---------|------|
| EE1001 ⛔ | Invalid input parameter · Invalid_Argument (fallback) | `extend_info` | `The argument is invalid. Reason: %s` | Cause: N/A.<br>Solution: 1. Check the input parameter range of the function. 2. Check the function invocation relationship. | ⛔ Called only in the macro ERROR_RETURN_WITH_EXT_ERRCODE as the fallback of the rt API layer. Do not add new invocations in other scenarios. | / | `The argument is invalid. Reason: kernel does not have param info. ErrorCode=EE1001.` | ⛔ Called only in the macro ERROR_RETURN_WITH_EXT_ERRCODE as the fallback of the rt API layer. Do not add new invocations in other scenarios. |
| EE1002 | Execution error · Stream_Synchronize_Timeout | `extend_info` | `Stream synchronization timeout. %s` | Cause: 1. The timeout interval may be improperly set.<br>Solution: 1. Check whether the timeout interval is properly set. 2. Check whether the network is normal. | Stream synchronization timeout | `stream_c.cc:232`<br>`COND_RETURN_AND_MSG_OUTER(error == RT_ERROR_STREAM_SYNC_TIMEOUT, error, ErrorCode::EE1002, "DataDumpLoadInfoTask synchronize");` | `Stream synchronization timeout. DataDumpLoadInfoTask synchronize. ErrorCode=EE1002.` | Dedicated to stream synchronization timeout |
| EE1003 ⭐ | Invalid input parameter · Invalid_Argument | `func, value, param, expect` | `%s failed because value %s for parameter %s is invalid. Expected value: %s.` | Cause: N/A.<br>Solution: 1. Check the input parameter range of the function. 2. Check the function invocation relationship. | The parameter value is invalid + the parameter name and value are printable + the expected value can be provided | `runtime.cc:4674`<br>`RT_LOG_OUTER_MSG_WITH_FUNC_DESC(ErrorCode::EE1003, "Obtaining the logical device ID based on the user device ID", userDevId, "userDevId", "[0, " + std::to_string(userDeviceCnt) + ")");` | `Obtaining the logical device ID based on the user device ID failed because value 8 for parameter userDevId is invalid. Expected value: [0, 4). ErrorCode=EE1003.` | ⭐ Preferred general-purpose code; prefer the `_WITH_DESC` variant to pass a semantic function description |
| EE1004 ⭐ | Invalid input parameter · Null_Pointer | `func, param` | `%s failed because %s cannot be a NULL pointer.` | Cause: N/A.<br>Solution: Try again with a correct pointer argument. | NULL pointer | `kernel_utils.cc:213`<br>`COND_RETURN_AND_MSG_OUTER((kernel == nullptr), RT_ERROR_INVALID_VALUE, ErrorCode::EE1004, "rtModelTaskSetParams", "params->kernelTaskParams->funcHandle");` | `rtModelTaskSetParams failed because params->kernelTaskParams->funcHandle cannot be a NULL pointer. ErrorCode=EE1004.` | ⭐ Dedicated code for null pointers |
| EE1005 | Not supported · Not_Supported | `func` | `The current system or device does not support %s.` | None | A complete feature is not supported by the chip | `api_impl.cc:4310`<br>`if (!IS_SUPPORT_CHIP_FEATURE(dev->GetChipType(), RtOptionalFeatureType::RT_FEATURE_MODEL_ABORT)) { RT_LOG_OUTER_MSG_WITH_FUNC_DESC(ErrorCode::EE1005, "Aborting the model running instance"); return RT_ERROR_FEATURE_NOT_SUPPORT; }` | `The current system or device does not support Aborting the model running instance. ErrorCode=EE1005.` | Only the chip layer does not support a complete feature; prefer the `_WITH_FUNC_DESC` variant to pass a semantic function description |
| EE1006 | Not supported · Not_Supported | `func, type, reason` | `%s failed. %s is not supported. Reason: %s.` | Cause: N/A.<br>Solution: N/A. | A configuration parameter of a non-complete feature is not supported (a non-complete feature means not a complete rt/rts API) | `api_error.cc:1171`<br>`COND_RETURN_AND_MSG_OUTER((stm != nullptr) && ((stm->Flags() & RT_STREAM_AICPU) != 0U), RT_ERROR_STREAM_INVALID, ErrorCode::EE1006, "Synchronizing a stream", "Stream flags value " + std::to_string(stm->Flags()), "The current stream is used to carry AI CPU scheduling tasks and does not support stream synchronization");` | `Synchronizing a stream failed. Stream flags value 4 is not supported. Reason: The current stream is used to carry AI CPU scheduling tasks and does not support stream synchronization. ErrorCode=EE1006.` | ① If the problem can be resolved by upgrading the version, or the non-support is caused by version incompatibility, specify the supported software version information in Reason;<br>② If the problem cannot be resolved by upgrading, Reason can state the principle of non-support, the supported operations, or the details of the non-support. For the func parameter, prefer a semantic description |
| EE1007 | Resource error · Bind_Stream | `id, reason` | `Failed to bind stream (stream_id=%s). Reason: %s.` | Cause: N/A.<br>Solution: Unbind the stream from the already bound model and then rebind it to the current model. | Failed to bind a stream to a model | `model.cc:400`<br>`if (streamIn->IsModelStream()) { RT_LOG_OUTER_MSG_IMPL(ErrorCode::EE1007, streamId, RtFmtMsg("The current stream has been bound to a model (model_id=%u) and cannot be bound to the input model (model_id=%u)", streamIn->Model_()->Id_(), Id_())); return RT_ERROR_STREAM_MODEL; }` | `Failed to bind stream (stream_id=15). Reason: The current stream has been bound to a model (model_id=1) and cannot be bound to the input model (model_id=2). ErrorCode=EE1007.` | Dedicated to stream binding failures |
| EE1009 | Execution error · Model | `id, reason` | `Failed to execute model (model_id=%s). Reason: %s.` | Cause: N/A.<br>Solution: N/A. | Model execution failure | `capture_model.cc:490`<br>`COND_RETURN_AND_MSG_OUTER(streamNum == 0U, RT_ERROR_INVALID_VALUE, ErrorCode::EE1009, std::to_string(Id_()), "The current aclgraph model running instance neither contains any executable task nor contains any executable stream");` | `Failed to execute model (model_id=1). Reason: The current aclgraph model running instance neither contains any executable task nor contains any executable stream. ErrorCode=EE1009.` | id is the model ID |
| EE1010 | Execution error · Invalid_Context | `func, object, extend_info` | `%s execution failed because %s does not belong to the current context. Extended information: %s.` | Cause: N/A.<br>Solution: N/A. | A stream/event does not belong to the current context | `error_message_manage.hpp:197`<br>`COND_RETURN_AND_MSG_INVALID_CONTEXT_STREAM(curStm, curCtx, RT_ERROR_STREAM_CONTEXT);` // Internal expansion: `RT_LOG_OUTER_MSG_IMPL(ErrorCode::EE1010, __func__, "stream", extendInfo);` | `rtKernelLaunch execution failed because stream does not belong to the current context. Extended information: stream_id=15, stream_ctx=0x7f..., cur_ctx=0x7f.... ErrorCode=EE1010.` | extend_info outputs resource IDs and context pointers to help locate ownership relationships |
| EE1011 | Invalid input parameter · Invalid_Argument | `func, value, param, reason` | `%s failed. Value %s for parameter %s is invalid. Reason: %s.` | Cause: N/A.<br>Solution: 1. Check the input parameter range of the function. 2. Check the function invocation relationship. | The expected value cannot be provided, the invalid value + reason can be provided, and "for parameter %s" reads naturally | `api_impl.cc:478`<br>`kernel = Runtime::Instance()->KernelLookup(stubFunc); COND_RETURN_AND_MSG_OUTER(kernel == nullptr, RT_ERROR_KERNEL_NULL, ErrorCode::EE1011, __func__, static_cast<const char_t *>(stubFunc), "stubFunc", "The corresponding kernel cannot be found through stubFunc. The specified function address is invalid or the kernel status is abnormal");` | `rtKernelLaunch failed. Value "kernel_Add" for parameter stubFunc is invalid. Reason: The corresponding kernel cannot be found through stubFunc. The specified function address is invalid or the kernel status is abnormal. ErrorCode=EE1011.` | Adding "parameter" reads naturally → EE1011; adding "parameter" is redundant → EE1012 |
| EE1012 | Invalid input parameter · Invalid_Argument | `func, value, param, reason` | `%s failed. Value %s for %s is invalid. Reason: %s.` | Cause: N/A.<br>Solution: N/A. | The expected value cannot be provided, the invalid value + reason can be provided, and adding "parameter" is redundant | `api_impl.cc:4777`<br>`COND_RETURN_AND_MSG_OUTER(inNotify->CheckIpcNotifyDevId() != RT_ERROR_NONE, RT_ERROR_INVALID_VALUE, ErrorCode::EE1012, __func__, dev->Id_(), "current deviceId", "The current device cannot deliver Notify Wait, the corresponding Notify Wait must be delivered on the device that creates the IPC Notify");` | `rtNotifyWait failed. Value 0 for current deviceId is invalid. Reason: The current device cannot deliver Notify Wait, the corresponding Notify Wait must be delivered on the device that creates the IPC Notify. ErrorCode=EE1012.` | Same Arglist as EE1011. Only the template differs: EE1011 has "for parameter", and EE1012 has only "for" |
| EE1013 | Resource error · Insufficient_Host_Memory | `buf_size, alloc_interface` | `Failed to allocate %s bytes of host memory via %s to Runtime.` | Cause: Allocation failed due to insufficient host memory.<br>Solution: Ensure that there is sufficient memory available. You can stop unnecessary processes to free up memory. | Failed to allocate host memory | `ffts_task.cc:236`<br>`RT_LOG_OUTER_MSG_IMPL(ErrorCode::EE1013, std::to_string(sizeof(std::vector<rtFftsPlusTaskErrInfo_t>)), "new");` | `Failed to allocate 4096 bytes of host memory via new to Runtime. ErrorCode=EE1013.` | The default memory unit is bytes; alloc_interface is the name of the allocation API (such as new/malloc) |
| EE1014 | Execution error · File_Parse | `reason` | `Failed to parse the binary file of the operator. Reason: %s.` | Cause: 1. The binary file of the operator is damaged. 2. The build parameter is incorrect.<br>Solution: Rebuild and load the binary file of the operator. | Operator ELF bin parsing failure caused by a damaged operator binary file or invalid build parameters | `elf.cc:215`<br>`RT_LOG_OUTER_MSG_IMPL(ErrorCode::EE1014, "The value " + std::to_string(size) + " of e_shentsize or the value " + std::to_string(num) + " of e_shnum in the operator binary ELF file header is incorrect. The expected value complies the following rule: both e_shentsize and e_shnum are not 0, and the product of the values of e_shnum and e_shentsize cannot be greater than the maximum value of uint64_t");` | `Failed to parse the binary file of the operator. Reason: The value 2048 of e_shentsize or the value 0 of e_shnum in the operator binary ELF file header is incorrect. The expected value complies the following rule: both e_shentsize and e_shnum are not 0, and the product of the values of e_shnum and e_shentsize cannot be greater than the maximum value of uint64_t. ErrorCode=EE1014.` | Reason must describe in detail why the file parsing fails |
| EE1015 | Not supported · Incorrect_Driver_Version | `func, reason` | `%s failed. Reason: The driver version capability is insufficient. %s` | Cause: N/A.<br>Solution: Upgrade the driver software version. | The driver version is incorrect, and upgrading the driver version resolves the problem | `runtime.cc:2114`<br>`COND_RETURN_AND_MSG_OUTER(tsdOpenNetService_ == nullptr, RT_ERROR_DRV_TSD_ERR, ErrorCode::EE1015, "Starting the HCCP process", "Symbol TsdOpenNetService not found in libtsdclient.so.");` | `Starting the HCCP process failed. Reason: The driver version capability is insufficient. Symbol TsdOpenNetService not found in libtsdclient.so. ErrorCode=EE1015.` | If you need to report an errmsg when a driver symbol does not exist, use this error code; for the func parameter, prefer a semantic description |
| EE1016 | Not supported · Not_Supported | `func, reason` | `%s failed. Reason: %s.` | Cause: N/A.<br>Solution: N/A. | ① Intrinsic non-support: a certain type of operation is not supported in a certain state or scenario, for example, ModelUpdate is not supported by non-ACL Graph models, and changing the stop-on-failure mode from stop to continue is not supported;<br>② A complete feature is not supported (a complete feature means a complete rt/rts API) | ① Intrinsic non-support example 1: `api_impl.cc:1904`<br>`COND_RETURN_AND_MSG_OUTER((curStm->GetFailureMode() == STOP_ON_FAILURE) && (failmode == CONTINUE_ON_FAILURE), RT_ERROR_FEATURE_NOT_SUPPORT, ErrorCode::EE1016, "Setting the stream error reporting mode", RtFmtMsg("Changing stream %u from stop mode to continue mode is not supported", curStm->Id_()));`<br>② Intrinsic non-support example 2: `COND_RETURN_AND_MSG_OUTER(mdl->GetModelType() != RT_MODEL_CAPTURE_MODEL, RT_ERROR_FEATURE_NOT_SUPPORT, ErrorCode::EE1016, "Updating the model running instance", "Non ACL Graph mode is not supported");`<br>③ Complete feature not supported example (dedicated macro for capture mode checks): `api_impl.cc:2674`<br>`CHECK_CAPTURE_MODE_SUPPORT_AND_RETURN_WITH_DESC(curCtx, "Synchronous memory copy");` | ① Intrinsic non-support example 1: `Setting the stream error reporting mode failed. Reason: Changing stream 15 from stop mode to continue mode is not supported. ErrorCode=EE1016.`<br>② Intrinsic non-support example 2: `Updating the model running instance failed. Reason: Non ACL Graph mode is not supported. ErrorCode=EE1016.`<br>③ Complete feature not supported example: `Synchronous memory copy failed. Reason: the operation has been converted to a synchronous operation. Operation not permitted when a stream is capturing and the specified capture mode is not relaxed. ErrorCode=EE1016.` | ① Intrinsic non-support → emphasize which operation is not supported in which state or scenario;<br>② Complete feature not supported → state the principle of non-support, the supported operations, or the details of the non-support. For the func parameter, prefer a semantic description; in capture mode scenarios, use the dedicated macro `CHECK_CAPTURE_MODE_SUPPORT_AND_RETURN_WITH_DESC` |
| EE1017 | Invalid input parameter · Invalid_Argument | `func, param, reason` | `%s failed. Parameter %s is invalid. Reason: %s.` | Cause: N/A.<br>Solution: N/A. | The specific parameter value cannot be provided | `stream_c.cc:903`<br>`RT_LOG_OUTER_MSG_WITH_FUNC_DESC(ErrorCode::EE1017, "Writing data to the specified memory", "addr", "address is not aligned by awsize");` | `Writing data to the specified memory failed. Parameter addr is invalid. Reason: address is not aligned by awsize. ErrorCode=EE1017.` | Also usable when the relationship between two or more user parameters is not satisfied, for example, user parameters A and B do not satisfy A < B. The specific parameter values and the parameter relationship are presented in Reason. For the func parameter, prefer a semantic description |
| EE1018 | Invalid input parameter · API_Call_Sequence | `func, reason` | `%s failed. Reason: %s.` | Cause: N/A.<br>Solution: N/A. | Incorrect API call sequence | `runtime.cc:3667`<br>`RT_LOG_OUTER_MSG_WITH_FUNC_DESC(ErrorCode::EE1018, "Starting profiling analysis", "profiler is already enabled, cannot set repeatedly");` | `Starting profiling analysis failed. Reason: profiler is already enabled, cannot set repeatedly. ErrorCode=EE1018.` | Reason should clarify the correct call sequence; for the func parameter, prefer a semantic description |
| EE1019 | Execution error · Execution_Error | `func, reason` | `%s failed. Reason: %s.` | Cause: N/A.<br>Solution: 1. Reduce the number of tasks delivered to the same stream. 2. Use multiple streams to submit tasks in parallel. | Failed to deliver stream tasks, including scenarios where the stream task queue is full and no reclaim mechanism exists (such as persistent stream and bound stream) | `stream_xpu.cc:105`<br>`RT_LOG_OUTER_MSG_IMPL(ErrorCode::EE1019, "Adding task to stream", "Stream task public buffer is full");` | `Adding task to stream failed. Reason: Stream task public buffer is full. ErrorCode=EE1019.` | When the stream task queue is full and no reclaim mechanism exists (for example, persistent stream and bound stream cannot reclaim tasks), use EE1019 to report an external error. Do not only print a normal log or use EE9999 |
| EE1020 | Other · Standard function failure | `func1, func2, ret_code, reason, extend_info` | `%s failed. Reason: Standard function %s failed. [Errno %s] %s. %s` | Cause: N/A.<br>Solution: N/A. | Standard library function failure, such as memcpy_s | ① `task_to_sqe.cc:99`<br>`const errno_t ret = memcpy_s(...); COND_RETURN_AND_MSG_OUTER(ret != EOK, RT_ERROR_SEC_HANDLE, ErrorCode::EE1020, __func__, "memcpy_s", std::to_string(ret), strerror(ret), "src=..., dest=..., dest_max=..., count=...");`<br>② User input parameter example: `api_c.cc:3999`<br>`const errno_t ret = memcpy_s(&data, sizeof(data), userdata, static_cast<size_t>(length)); if (ret != EOK) { std::stringstream ss; ss << std::hex << "dest=0x" << RtPtrToValue(&data) << ", userdata=0x" << RtPtrToValue(userdata) << std::dec << ", destMax=" << sizeof(data) << ", length=" << length << "."; RT_LOG_OUTER_MSG_IMPL(ErrorCode::EE1020, __func__, "memcpy_s", std::to_string(ret).c_str(), strerror(ret), ss.str().c_str()); }` | `TaskToSqe failed. Reason: Standard function memcpy_s failed. [Errno 22] Invalid argument. src=... ErrorCode=EE1020.`<br>②`rtsProfTrace failed. Reason: Standard function memcpy_s failed. [Errno 22] Invalid argument. dest=0x7f..., userdata=0x7f..., destMax=48, length=64. ErrorCode=EE1020.` | If the parameters are passed in by the user, extend_info should print the parameter names of the external input parameters and the corresponding values or addresses, instead of printing only the default src, dst, and so on. Print addresses in hexadecimal format |
| EE1021 | Resource error · Resource_Error | `resource_type, api` | `The runtime module failed to create host %s through API %s.` | Cause: Failed to create resources such as semaphores, locks, or threads due to insufficient system resources.<br>Solution: Stop unnecessary threads and ensure that the required resource is available. | Failed to create a thread/lock/semaphore | `stars_engine.cc:171`<br>`const rtError_t error = mmSemInit(&recycleThreadSem_, 0U); if (error != RT_ERROR_NONE) { RT_LOG_OUTER_MSG_IMPL(ErrorCode::EE1021, "semaphore", "sem_init"); return RT_ERROR_MEMORY_ALLOCATION; }` | `The runtime module failed to create host semaphore through API sem_init. ErrorCode=EE1021.` | / |
| EE1022  | Invalid input parameter · Invalid_Argument (multiple parameters) | `func, values, params, reason` | `%s failed. Values %s for parameters %s are invalid. Reason: %s.` | Cause: N/A.<br>Solution: 1. Check the input parameter value ranges of the function. 2. Check the function invocation relationship. | Multiple parameters are invalid at the same time | `api_error_aclgraph.cc:64`<br>`COND_RETURN_AND_MSG_OUTER((status == nullptr) && (captureMdl == nullptr), RT_ERROR_INVALID_VALUE, ErrorCode::EE1022, __func__, "nullptr and nullptr", "status and captureMdl", "Parameters status and captureMdl cannot both be nullptr");` | `aclmdlRICaptureGetInfo failed. Values nullptr and nullptr for parameters status and captureMdl are invalid. Reason: Parameters status and captureMdl cannot both be nullptr. ErrorCode=EE1022.` | Multiple parameters are invalid at the same time. |
| EE1023 | Resource error · Resource_Error | `func, reason` | `%s failed. Reason: %s.` | Cause: N/A<br>Solution: N/A | Insufficient NPU hardware scheduling resources | `stream_jetty_context.cc:62`<br>`RT_LOG_OUTER_MSG_IMPL(ErrorCode::EE1023, "Expanding the capacity", "There are too many asynchronous copy tasks. 1. If the value of numBatches for aclrtMemcpyBatchAsync is too large, reduce the value of numBatches. 2. If the value of height for aclrtMemcpy2dAsync is too large, reduce the value of height");` | `Expanding the capacity failed. Reason: There are too many asynchronous copy tasks. 1. If the value of numBatches for aclrtMemcpyBatchAsync is too large, reduce the value of numBatches. 2. If the value of height for aclrtMemcpy2dAsync is too large, reduce the value of height. ErrorCode=EE1023.` | / |
| EE1025 | Initialization error · Initialization_Error | `library_name, reason` | `Failed to load dynamic library %s. Reason: %s.` | Cause: N/A.<br>Solution: 1. Use the correct dynamic library path. 2. Ensure that the required dynamic library has been correctly installed. | Failed to load a dynamic library or resolve a required symbol | `runtime_keeper.cc:189`<br>`RT_LOG_OUTER_MSG_IMPL(ErrorCode::EE1025, libSoName.c_str(), dlError);` | `Failed to load dynamic library libruntime_v100.so. Reason: /usr/local/Ascend/cann-9.2.0/lib64/libruntime_v100.so: undefined symbol: ConstructRuntimeImpl. ErrorCode=EE1025.` | `library_name` is filled in by the call site with the specific dynamic library name, and `reason` preferably uses the reason returned by the dynamic loader. |
| EE1026 | Execution error · Execution_Error_Event_Synchronize_Timeout | `event_id, extend_info` | `Event (event_id=%s) synchronization timeout. %s` | Cause: 1. Tasks submitted before the last Event Record take a long time to execute, fail to be executed, or have unsolved dependency relationships. 2. The synchronization timeout interval is less than the time required for completing tasks submitted before the last Event Record. 3. For IPC Event, the peer process or device stops running.<br>Solution: 1. Check whether tasks submitted before the last Event Record fail to be executed or have unsolved dependency relationships. 2. Extend the synchronization timeout interval through an event timeout interval configuration API (for example, aclrtSynchronizeEventWithTimeout). 3. For IPC Event, ensure that the peer process and device are running properly. | Event synchronization timeout | `api_impl.cc:2380`<br>`COND_RETURN_AND_MSG_OUTER(error == RT_ERROR_EVENT_SYNC_TIMEOUT, error, ErrorCode::EE1026, evt->EventId_(), RtFmtMsg("A timeout occurred when waiting for task execution before Event Record. The timeout interval is %d ms, device_id=%u.", timeout, evt->Device_()->Id_()));` | `Event (event_id=5) synchronization timeout. A timeout occurred when waiting for task execution before Event Record. The timeout interval is 1000 ms, device_id=0. ErrorCode=EE1026.` | Dedicated to Event synchronization timeout, not for Stream synchronization timeout |
| EE2002 | Configuration and environment error · Invalid_Environment_Variable | `value, env, expect` | `Value %s for environment variable %s is invalid. Expected value: %s.` | Cause: N/A.<br>Solution: Reset the environment variable by referring to the Environment Variable Reference. | Invalid environment variable value | `runtime.cc:1135`<br>`MM_SYS_GET_ENV(MM_ENV_LD_LIBRARY_PATH, getPath); if (getPath == nullptr) { RT_LOG_OUTER_MSG_IMPL(ErrorCode::EE2002, "NULL", "LD_LIBRARY_PATH", "a valid path containing \"runtime/lib64\""); return RT_ERROR_INVALID_VALUE; }` | `Value NULL for environment variable LD_LIBRARY_PATH is invalid. Expected value: a valid path containing "runtime/lib64". ErrorCode=EE2002.` | / |
| EE4001 🔸 | Execution error · Model_Binding | `extend_info` | `Failed to bind the stream to the model. %s` | Cause: The stream has been bound to another model.<br>Solution: Remove the repeated binding operation on the stream from the code. | Failed to bind a stream to a model | 🔸 Not used in the mainline | / | 🔸 Not used in the mainline |
| EE4002 🔸 | Execution error · Model_Unbinding | `extend_info` | `Failed to unbind the stream from the model. %s` | Cause: 1. The stream to be unbound is not bound to the model. 2. The model is running.<br>Solution: 1. Check the code to ensure that the stream to be unbound is bound to the model. 2. Ensure that the model is not running. | Failed to unbind a stream from a model | 🔸 Not used in the mainline | 🔸 Not used in the mainline | 🔸 Not used in the mainline |
| EE4004 🔸 | Execution error · Profiling_Enable | `extend_info` | `Failed to enable profiling. %s` | Cause: N/A.<br>Solution: Do not enable profiling repeatedly. | Profiling is enabled repeatedly | 🔸 Not used in the mainline | 🔸 Not used in the mainline | 🔸 Not used in the mainline |

## EH Error Code Overview Table

| ErrCode | errTitle (Category) | Arglist | ErrMessage | suggestion | Usage Scenario | Usage Example | Screen Output | Description |
|---------|---------------|---------|------------|------------|---------|---------|---------|------|
| EH0001 ⛔ | Invalid input parameter · Invalid_Argument (fallback) | `value, param, reason` | `Value %s for %s is invalid. Reason: %s.` | Cause: N/A.<br>Solution: N/A. | ⛔ Fallback only; do not add new invocations | N/A | `Value 1024 for offset+count is invalid. Reason: must be <= symbolSize. ErrorCode=EH0001.` | ⛔ Fallback only; do not add new invocations |
| EH0002 ⛔ | Invalid input parameter · Null_Pointer (without function name) | `param` | `Argument %s must not be null.` | Cause: N/A.<br>Solution: Try again with a correct pointer argument. | ⛔ Do not add new invocations; prefer EH0008 | `kernel.cpp:218`<br>`acl::AclErrorLogManager::ReportInputError("EH0002", {"param"}, {"dptr and size"});` | `Argument dptr and size must not be null. ErrorCode=EH0002.` | ⛔ Without the function name. Prefer EH0008 for new code. |
| EH0003 | Configuration and environment error · Invalid_Path | `path, reason` | `Path %s is invalid. Reason: %s.` | Cause: N/A.<br>Solution: N/A. | The file path itself is invalid | `acl_rt_impl_base.cpp:176`<br>`if (mmRealPath(configPath, realPath, MMPA_MAX_PATH) != EN_OK) { acl::AclErrorLogManager::ReportInputError(acl::INVALID_PATH_MSG, {"path", "reason"}, {configPath, formatErrMsg.c_str()}); return ACL_ERROR_INVALID_FILE; }` | `Path /usr/local/Ascend/ascend-toolkit/latest/acl.json is invalid. Reason: No such file or directory. ErrorCode=EH0003.` | ⚠️ EH0003 = invalid path; EH0004 = invalid content. |
| EH0004 | Configuration and environment error · File_Operation | `path, reason` | `File %s is invalid. Reason: %s.` | Cause: N/A.<br>Solution: N/A. | The file content is invalid | `acl.cpp:403`<br>`if (!aclInitJsonHash.empty() && currentHash != aclInitJsonHash) { acl::AclErrorLogManager::ReportInputError(acl::INVALID_FILE_MSG, {"path", "reason"}, {configPath, errMsg.c_str()}); return ACL_ERROR_INVALID_PARAM; }` | `File /home/user/acl_init2.json is invalid. Reason: config content differs from the first aclInit config file path: /home/user/acl_init.json. ErrorCode=EH0004.` | ⚠️ EH0004 = invalid content; EH0003 = invalid path. |
| EH0005 🔸 | Invalid input parameter · AIPP-specific | `param, reason` | `AIPP argument %s is invalid. Reason: %s.` | Cause: N/A.<br>Solution: N/A. | Invalid AIPP parameter | 🔸 Not actually used in the source code | N/A | 🔸 AIPP-specific code, reserved and unused. |
| EH0006 | Not supported · Not_Supported | `feature, reason` | `%s is not supported. Reason: %s.` | N/A | Not supported for non-chip reasons | `tensor_data_transfer.cpp:926`<br>`if (dataset->freeSelf) { acl::AclErrorLogManager::ReportInputError(acl::UNSUPPORTED_FEATURE_MSG, {"feature", "reason"}, {__func__, "item cannot be added because internal item already exists"}); return ACL_ERROR_FEATURE_UNSUPPORTED; }` | `acltdtAddDataItem is not supported. Reason: item cannot be added because internal item already exists. ErrorCode=EH0006.` | Not supported due to the chip → EH0011; not supported due to non-chip reasons → EH0006 |
| EH0007 ⭐ | Invalid input parameter · Invalid_Argument | `func, value, param, expect` | `%s failed because value %s for parameter %s is invalid. Expected value: %s.` | Cause: N/A.<br>Solution: 1. Check the input parameter range of the function. 2. Check the function invocation relationship. | The invalid value can be output + the parameter name is printable + the expected value can be provided | `memory.cpp:191`<br>`acl::AclErrorLogManager::ReportInputError(acl::INVALID_VALUE_MSG, {"func", "value", "param", "expect"}, {"Memory copy type conversion", acl::GetMemcpyKindDesc(kind), "kind", "ACL_MEMCPY_HOST_TO_DEVICE(1) or ..."});` | `Memory copy type conversion failed because value ACL_MEMCPY_HOST_TO_HOST for parameter kind is invalid. Expected value: ACL_MEMCPY_HOST_TO_DEVICE(1) or ... ErrorCode=EH0007.` | ⭐ Preferred code at the ACL layer; for non-API-layer code, prefer a semantic description for the func parameter |
| EH0008 ⭐ | Invalid input parameter · Null_Pointer (with function name) | `func, param` | `%s failed because %s cannot be a NULL pointer.` | Cause: N/A.<br>Solution: Try again with a correct pointer argument. | NULL pointer with the function name | `memory.cpp:217`<br>`ACL_REQUIRES_NOT_NULL_WITH_INPUT_REPORT_AND_FUNC_DESC(dst, "Checking the synchronous memory copy parameter validity");` | `Checking the synchronous memory copy parameter validity failed because dst cannot be a NULL pointer. ErrorCode=EH0008.` | ⭐ Dedicated error code for null pointers; non-API-layer code should prefer the `_AND_FUNC_DESC` variant |
| EH0009 | Invalid input parameter · Invalid_Argument | `func, value, param, reason` | `%s failed. Value %s for parameter %s is invalid. Reason: %s.` | Cause: N/A.<br>Solution: 1. Check the input parameter range of the function. 2. Check the function invocation relationship. | The expected value cannot be provided, but the specific invalid value + reason can be provided | `memory.cpp:231`<br>`acl::AclErrorLogManager::ReportInputError(acl::INVALID_PARAM_REASON_MSG, {"func", "value", "param", "reason"}, {"Checking the synchronous memory copy parameter validity", widthVal.c_str(), "width", errMsg.c_str()});` | `Checking the synchronous memory copy parameter validity failed. Value 2048 for parameter width is invalid. Reason: must be less than spitch and dpitch, spitch=1024, dpitch=1024. ErrorCode=EH0009.` | If the specific invalid value can be provided → EH0009; otherwise → EH0012; for non-API-layer code, prefer a semantic description for the func parameter |
| EH0010 | Resource error · Insufficient_Host_Memory | `buf_size, alloc_interface` | `Failed to allocate %s bytes of host memory via %s to ACL.` | Cause: Allocation failed due to insufficient host memory.<br>Solution: Ensure that there is sufficient memory available. You can stop unnecessary processes to free up memory. | Failed to allocate host memory at the ACL layer | `json_parser.cpp:125`<br>`acl::AclErrorLogManager::ReportInputError(acl::ALLOC_MEMORY_FAILED_MSG, {"buf_size", "alloc_interface"}, {lengthVal.c_str(), "new"});` | `Failed to allocate 1024 bytes of host memory via new to ACL. ErrorCode=EH0010.` | The default memory unit is bytes; alloc_interface is the name of the allocation API (such as new/malloc) |
| EH0011 | Not supported · Not_Supported (chip) | `func` | `The current system or device does not support %s.` | None | Not supported due to the chip | `device.cpp:80`<br>`if (strncmp(socVersion.c_str(), "Ascend910", ...) != 0) { acl::AclErrorLogManager::ReportInputError(acl::UNSUPPORTED_SYSTEM_MSG, {"func"}, {"aclrtSetDeviceWithoutTsdVXX, only Ascend 910 chips are supported"}); return ACL_ERROR_API_NOT_SUPPORT; }` | `The current system or device does not support aclrtSetDeviceWithoutTsdVXX, only Ascend 910 chips are supported. ErrorCode=EH0011.` | No reason field |
| EH0012 | Invalid input parameter · Invalid_Argument | `func, param, reason` | `%s failed. Parameter %s is invalid. Reason: %s.` | Cause: N/A.<br>Solution: N/A. | The specific parameter value cannot be provided | `allocator.cpp:157`<br>`const auto iter = g_AllocatorDesMap.find(stream); if (iter == g_AllocatorDesMap.end()) { acl::AclErrorLogManager::ReportInputError(acl::INVALID_PARAM_NO_VALUE_MSG, {"func", "param", "reason"}, {__func__, "stream", "The stream is not registered with any allocator"}); return ACL_ERROR_INVALID_PARAM; }` | `aclrtGetAllocator failed. Parameter stream is invalid. Reason: The stream is not registered with any allocator. ErrorCode=EH0012.` | Also usable when the relationship between two or more user parameters is not satisfied, for example, user parameters A and B do not satisfy A < B. The specific parameter values and the parameter relationship are presented in Reason |
| EH0013 | Other · Standard function failure | `func1, func2, ret_code, reason, extend_info` | `%s failed. Reason: Standard function %s failed. [Errno %s] %s. %s` | Cause: N/A.<br>Solution: N/A. | Standard library function failure at the ACL layer | ① `queue.cpp:38`<br>`const auto ret = memcpy_s(...); if (ret != EOK) { ... acl::AclErrorLogManager::ReportInputError(acl::STANDARD_FUNC_FAILED_MSG, {"func1", "func2", "ret_code", "reason", "extend_info"}, {"Parameter copy", "memcpy_s", retVal.c_str(), strerror(ret), extendInfo.c_str()}); }`<br>② User input parameter example: `memory.cpp:1581`<br>`const auto ret = memcpy_s(dataPtr, size, srcAddr, size); if (ret != EOK) { std::stringstream ss; ss << std::hex << "src=0x" << reinterpret_cast<uintptr_t>(srcAddr) << ", dataPtr=0x" << reinterpret_cast<uintptr_t>(dataPtr) << std::dec << ", size=" << size << ", count=" << size << "."; acl::AclErrorLogManager::ReportInputError(acl::STANDARD_FUNC_FAILED_MSG, {"func1", "func2", "ret_code", "reason", "extend_info"}, {funcName.c_str(), "memcpy_s", retVal.c_str(), strerror(ret), extendInfo.c_str()}); }` | `Parameter copy failed. Reason: Standard function memcpy_s failed. [Errno 22] Invalid argument. src=... ErrorCode=EH0013.`<br>②`aclrtGetBufUserData failed. Reason: Standard function memcpy_s failed. [Errno 22] Invalid argument. src=0x7f..., dataPtr=0x7f..., size=4096, count=4096. ErrorCode=EH0013.` | If the parameters are passed in by the user, extend_info should print the parameter names of the external input parameters and the corresponding values or addresses, instead of printing only the default src, dst, and so on. Print addresses in hexadecimal format. For the func1 parameter, prefer a semantic description |
| EH0014 | Invalid input parameter · Null_Pointer (multiple pointers NULL at the same time) | `func, param` | `%s failed because %s cannot be NULL pointers at the same time.` | Cause: N/A.<br>Solution: Try again with correct pointer arguments. | Multiple pointers are NULL at the same time | `kernel.cpp:216`<br>`if ((dptr == nullptr) && (size == nullptr)) { acl::AclErrorLogManager::ReportInputError(acl::INVALID_NULL_POINTER_AT_SAME_TIME_MSG, {"func", "param"}, {"aclrtBinaryGetGlobal", "dptr and size"}); return ACL_ERROR_INVALID_PARAM; }` | `aclrtBinaryGetGlobal failed because dptr and size cannot be NULL pointers at the same time. ErrorCode=EH0014.` | Multiple pointers are NULL at the same time. |

## Easily Confused Error Codes 1: Invalid Argument

### EE Layer Selection Decision Tree

```
Invalid input parameter?
  ├─ Are multiple parameters invalid at the same time (at least 2 parameters are NULL or invalid at the same time)?
  │     ├─ Yes → EE1022 (dedicated to multiple invalid parameters)
  │     └─ No → Is a single parameter a NULL pointer?
  │           ├─ Yes → ⭐ EE1004 (dedicated to null pointers, preferred)
  │           └─ No → Can an exact expected value be provided?
  │                 ├─ Yes → ⭐ EE1003 (preferred general-purpose code)
  │                 └─ No → The expected value cannot be provided, but can Reason explain the cause?
  │                       ├─ Yes → Does the Reason description read naturally in the "for parameter %s" context?
  │                       │     ├─ Yes → EE1011 ("...for parameter %s is invalid. Reason: %s")
  │                       │     └─ No → EE1012 ("...for %s is invalid. Reason: %s", omitting "parameter")
  │                       └─ No → The specific input value and expected value of the parameter cannot be provided?
  │                             ├─ Yes → EE1017
  │                             └─ No → ⛔ EE1001 (called only in the macro ERROR_RETURN_WITH_EXT_ERRCODE as the fallback of the rt API layer. EE1001 should not be triggered in other Runtime scenarios)
```

#### EE1011 vs EE1012 Selection Rules

The two codes have exactly the same Arglist (func, value, param, reason). Only the message template differs:

| Error Code | Text Before the Third %s | Example Output |
|--------|-------------------|----------|
| **EE1011** | `for parameter` | `aclrtMalloc failed. Value 3 for parameter deviceId is invalid. Reason: ...` |
| **EE1012** | `for` (omitting "parameter") | `aclrtMalloc failed. Value 3 for deviceId is invalid. Reason: ...` |

**Selection method**: Substitute the third arg into both templates and use whichever reads naturally. If adding "parameter" makes the sentence unnatural (for example, the parameter name is already a descriptive phrase such as "queue name length"), use EE1012; otherwise, prefer EE1011.

### EH Layer Selection Decision Tree

```
Invalid input parameter?
  ├─ Are multiple pointers NULL at the same time?
  │     ├─ Yes → EH0014 (dedicated to multiple pointers being NULL at the same time)
  │     └─ No → Is a single parameter a NULL pointer?
  │           ├─ Yes → Can the function name be included?
  │           │     ├─ Yes → ⭐ EH0008
  │           │     └─ No → ⛔ EH0002
  │           └─ No → Can an exact expected value be provided?
  │                 ├─ Yes → ⭐ EH0007
  │                 └─ No → The expected value cannot be provided, but can the specific invalid value + reason be provided?
  │                       ├─ Yes → EH0009 ("...Value %s for parameter %s is invalid. Reason: %s")
  │                       └─ No → The specific input value of the parameter cannot be provided?
  │                             ├─ Yes → EH0012 ("...Parameter %s is invalid. Reason: %s")
  │                             └─ No → ⛔ EH0001 (fallback only. ACL should not trigger EH0001)
```

#### EH0009 vs EH0012 Selection Rules

The core difference between the two codes is the Arglist:

| Error Code | Arglist | Can the Specific Invalid Value Be Provided? | Example Output |
|--------|---------|---------------------|----------|
| **EH0009** | func, value, param, reason | **Yes** | `aclrtDeviceCanAccessPeer failed. Value 0 for parameter deviceId is invalid. Reason: deviceId and peerDeviceId must be different.` |
| **EH0012** | func, param, reason | **No** | `aclrtGetAllocator failed, Parameter stream is invalid. Reason: The stream is not registered with any allocator.` |

**Selection method**: When the specific input value of the parameter can be provided, prefer EH0009 (more complete information). When the specific value cannot be provided (for example, an invalid attribute or a conditional conflict), use EH0012.

#### Priority Alignment Mapping Between EE and EH for Invalid Parameters

| Priority | EE Code (Runtime layer) | EH Code (ACL layer) | Semantic Alignment |
|--------|--------------------|----------------|----------|
| Multiple parameters invalid at the same time | EE1022 | EH0014 | Multiple parameters meet the invalid condition at the same time, and EH0014 limits the multiple parameters to NULL |
| Null pointer | EE1004 | EH0008 ⭐ | Dedicated to null pointers |
| Value + expected value | EE1003 | EH0007 | The invalid value and the expected correct value can be output |
| Value + reason | EE1011 ⭐ / EE1012 | EH0009 | The expected value cannot be provided, but the invalid value + reason can be provided |
| No value + reason | EE1017 | EH0012 | The specific input value cannot be provided, only the parameter name + reason |
| Fallback | EE1001 ⛔ | EH0001 ⛔ | For fallback use only. Do not trigger in other scenarios |

## Easily Confused Error Codes 2: Not Supported

### EE Layer Selection Decision Tree

```
Is the driver version incorrect, the corresponding driver API missing, and the problem resolvable by upgrading the driver package?
  ├─ Yes → EE1015
  ├─ No → Is a complete feature not supported by the current chip?
  │     ├─ Yes → EE1005
  │     └─ No → Is a configuration parameter of a non-complete feature not supported?
  │          ├─ Yes → EE1006
  │          └─ No → EE1016
```

| Priority | Error Code | Message Format (JSON ErrMessage) | Arglist | Selection Basis | Typical Scenario |
|--------|--------|---------------------------|---------|----------|----------|
| **1** | **EE1015** | `%s failed. Reason: The driver version capability is insufficient. %s` | func, reason | The driver version is incorrect, the corresponding driver API cannot be found, and upgrading the driver package resolves the problem | The driver version does not support the halxxx API |
| **2** | **EE1005** | `The current system or device does not support %s.` | func | A complete feature is not supported by the current chip | aclrtMemMap is not supported on the current chip |
| **3** | **EE1006** | `%s failed. %s is not supported. Reason: %s.` | func, type, reason | A configuration parameter of a non-complete feature is not supported.<br>① If the problem can be resolved by upgrading the version, or the non-support is caused by version incompatibility, specify the supported software version information in Reason;<br>② If the problem cannot be resolved by upgrading, Reason can state the principle of non-support, the supported operations, or the details of the non-support. | The ACL_FLOAT16 data type is not supported on the current SoC |
| **4** | **EE1016-intrinsic non-support** | `%s failed. Reason: %s.` | func, reason | A certain type of operation is not supported in a certain state or scenario | Switching the stop-on-failure mode from stop to continue is not supported |
| **4** | **EE1016-complete feature not supported** | `%s failed. Reason: %s.` | func, reason | A complete feature is not supported, which is unrelated to the chip | The MemCopy operation has been converted to a synchronous operation. The operation is not permitted when a stream is capturing and the specified capture mode is not relaxed. |


#### EE1005 vs EE1006 vs EE1016 Selection Rules

| Comparison | Key Difference | Selection Method |
|------|---------|---------|
| EE1005 vs EE1016-version-related non-support | Both mean a complete feature is not supported. EE1005 is at the chip layer, and EE1016 is for non-chip reasons | If the root cause is the chip → EE1005; if the root cause is that the software version or a certain state does not support an operation → EE1016 |
| EE1006 vs EE1016-version-related non-support | EE1006 is **a non-complete feature** (configuration parameter), and EE1016-version-related is **a complete feature** | If a configuration parameter is not supported → EE1006; if a complete feature itself is not supported → EE1016 |

### EH Layer Selection Decision Tree

```
Is a complete feature not supported by the current chip?
  ├─ Yes → EH0011
  └─ No → EH0006
```

**Selection method**: If the root cause is that **the current chip does not support it** (resolved by changing the chip) → EH0011; if the root cause is a **non-chip reason** (configuration parameter version/intrinsic limitation/software version) → EH0006.

#### Alignment Mapping Between EE and EH for Not Supported

| Not Supported Type | EE Code | EH Code | Remarks |
|-----------|-------|-------|------|
| Incorrect driver version | EE1015 | — | Internal reason. No mapping at the EH layer |
| A complete feature is not supported by the chip | EE1005 | EH0011 | Resolved by changing the chip |
| Configuration parameter of a non-complete feature | EE1006 | EH0006 | reason specifies the detailed requirements |
| Intrinsic non-support | EE1016-intrinsic non-support | EH0006 | reason indicates an intrinsic limitation |
| A complete feature is not supported | EE1016-complete feature not supported | EH0006 | reason specifies the detailed requirements |

## Common Errors

### ❌ Error 1: Using a Fallback Code Instead of a Dedicated Code

```cpp
// ✗ Wrong: the pointer is clearly NULL, but EE1001 is used
RT_LOG_OUTER_MSG(RT_INVALID_ARGUMENT_ERROR, "stream cannot be NULL");

// ✓ Correct: use the dedicated code EE1004
PARAM_NULL_RETURN_ERROR_WITH_EXT_ERRCODE(stream, RT_ERROR_INVALID_VALUE);
```

### ❌ Error 2: Confusing EH0003 and EH0004

```cpp
// ✗ Wrong: JSON parsing of the file fails, but EH0003 (invalid path) is used
ReportInputError(INVALID_PATH_MSG, {"path", "reason"}, {fileName, "JSON parse error"});

// ✓ Correct: use EH0004 when the file content is invalid
ReportInputError(INVALID_FILE_MSG, {"path", "reason"}, {fileName, "JSON parse error at line 5"});
```

### ❌ Error 3: Misusing EE1012 (Select EE1011 or EE1012 According to the Context)

```cpp
// ✗ Wrong: the parameter name is "deviceId", adding "parameter" is completely natural, but EE1012 is used
RT_LOG_OUTER_MSG_WITH_FUNC_DESC(ErrorCode::EE1012, "Setting the current device for the thread", "3", "deviceId", "must be in [0,7]");
// Output: Setting the current device for the thread failed. Value 3 for deviceId is invalid. — missing "parameter" is not formal enough

// ✓ Correct: the parameter name is "deviceId", adding "parameter" reads naturally → use EE1011
RT_LOG_OUTER_MSG_WITH_FUNC_DESC(ErrorCode::EE1011, "Setting the current device for the thread", "3", "deviceId", "must be in [0,7]");
// Output: Setting the current device for the thread failed. Value 3 for parameter deviceId is invalid.

// ✓ Correct: the parameter name is "queue name length", adding "parameter" is redundant → use EE1012
RT_LOG_OUTER_MSG_WITH_FUNC_DESC(ErrorCode::EE1012, "Setting the queue attribute", "256", "queue name length", "must be <= 128");
// Output: Setting the queue attribute failed. Value 256 for queue name length is invalid. — natural and fluent
```

### ❌ Error 4: Misusing EE1005 for Version-Related Complete Feature Non-Support

```cpp
// ✗ Wrong: a CANN version-related complete feature is not supported, but the chip-layer EE1005 is used
// Output: The current system or device does not support aclrtXxx.
// Problem: the root cause is the CANN version rather than the chip. Users mistakenly believe that changing the chip is the only solution

// ✓ Correct: use EE1016-version-related non-support
EE1016: func="Setting the error reporting mode", reason="This feature requires CANN 3.x. CANN 2.x and 3.x packages are incompatible. Please upgrade the CANN package to 3.x."
// Output: Setting the error reporting mode failed. Reason: This feature requires CANN 3.x. CANN 2.x and 3.x packages are incompatible. Please upgrade the CANN package to 3.x.
```

### ❌ Error 5: Misusing EE1006 for Intrinsic Non-Support

```cpp
// ✗ Wrong: switching the stop-on-failure mode from stop to continue is intrinsic non-support, but EE1006 is used
// Output: Setting the stream error reporting mode failed. stop-to-continue mode switch is not supported. Reason: ...
// Problem: this is not a version dependency problem of a configuration parameter, but an intrinsic limitation

// ✓ Correct: use EE1016-intrinsic non-support
EE1016: func="Setting the stream error reporting mode", reason="Changing stop mode to continue mode is intrinsically not supported and cannot be resolved by upgrading."
// Output: Setting the stream error reporting mode failed. Reason: Changing stop mode to continue mode is intrinsically not supported and cannot be resolved by upgrading.
```

### ❌ Error 6: Misusing EE1014 in Non-Operator ELF Parsing Scenarios

The ErrMessage template of EE1014 is hardcoded to `Failed to parse the binary file of the operator. Reason: %s.` and applies only to operator ELF bin parsing failures. Misuse in other file operation scenarios outputs misleading information, and its suggestion (Rebuild and load the binary file of the operator) provides no guidance for non-parsing scenarios.

```cpp
// ✗ Wrong: the path cannot be accessed when reading a binary file, but EE1014 is used
RT_LOG_OUTER_MSG_IMPL(ErrorCode::EE1014, RtFmtMsg("Path %s cannot be accessed", binPath_.c_str()));
// Output: Failed to parse the binary file of the operator. Reason: Path /xxx/xxx cannot be accessed. ErrorCode=EE1014.
// Problem: the actual scenario is a path access failure, not an operator ELF parsing failure. Neither ErrMessage nor suggestion applies

// ✓ Correct: use EE1012 (the expected value cannot be provided, but the invalid value + reason can be provided)
RT_LOG_OUTER_MSG_IMPL(ErrorCode::EE1012, "Read binary file", binPath_, "binPath_", RtFmtMsg("Path %s cannot be accessed", binPath_.c_str()));
// Output: Read binary file failed. Value /xxx/xxx for binPath_ is invalid. Reason: Path /xxx/xxx cannot be accessed. ErrorCode=EE1012.
```

### ❌ Error 7: Misusing EE1006 Due to Stream State Restrictions (model stream scenario)

Some operations are not supported when a stream is in the model stream state (`GetBindFlag()` is true). This belongs to the intrinsic non-support where "a certain type of operation is not supported in a certain state". Treating model stream as a configuration parameter type by mistake leads to misusing EE1006.

```cpp
// ✗ Wrong: model stream is a runtime state of the stream, not a configuration parameter, but EE1006 is used
COND_RETURN_AND_MSG_OUTER(stm->GetBindFlag(), RT_ERROR_STREAM_INVALID, ErrorCode::EE1006, "Clearing tasks in a stream",
    "Clearing model stream", "xxx");
// Output: Clearing tasks in a stream failed. Clearing model stream is not supported. Reason: xxx. ErrorCode=EE1006.
// Problem: model stream is a runtime state of the stream rather than a configuration parameter, and does not belong to "a configuration parameter of a non-complete feature not supported". Misusing EE1006 misleads users into checking parameter configurations. Tracing up to the rtStreamClear API, it is a complete feature (not "a non-complete feature"). Neither condition meets the prerequisite of using EE1006

// ✓ Correct: model stream is a state/scenario, and the clear operation is not supported in this state → EE1016-intrinsic non-support
COND_RETURN_AND_MSG_OUTER(
    stm->GetBindFlag(), RT_ERROR_STREAM_INVALID, ErrorCode::EE1016, "Clearing tasks in a stream", "Clearing model stream is not supported");
// Output: Clearing tasks in a stream failed. Reason: Clearing model stream is not supported. ErrorCode=EE1016.
```

## Key Source File Index

| File | Purpose |
|-----|------|
| `src/dfx/error_manager/error_code.json` | ErrCode metadata definitions |
| `src/runtime/core/inc/common/rt_log.h` | ErrorCode enum |
| `src/runtime/core/inc/common/error_code_meta.h` | X-Macro parameter table |
