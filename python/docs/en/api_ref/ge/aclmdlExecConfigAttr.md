# aclmdlExecConfigAttr

| Parameter| Definition|
| --- | --- |
| ACL_MDL_STREAM_SYNC_TIMEOUT = 0 | Controls the timeout of a stream task during model inference. This attribute value is of the INT32 type. The options are as follows:<br> `-1` (default): forever.<br> > 0: specific timeout interval, in milliseconds.|
| ACL_MDL_EVENT_SYNC_TIMEOUT = 1 | Controls the timeout of an event task during model inference. This attribute value is of the INT32 type. The options are as follows:<br> `-1` (default): forever.<br> > 0: specific timeout interval, in milliseconds.|
| ACL_MDL_WORK_ADDR_PTR = 2 | Sets the pointer address of the workspace required by the model (temporary data during model execution is stored on the device). The workspace is managed by the user. Generally, this mode is used in the scenario where a model is loaded once and concurrent jobs are executed.|
| ACL_MDL_WORK_SIZET = 3 | Workspace size required by the model, in bytes. Generally, this mode is used in the scenario where a model is loaded once and concurrent jobs are executed.|
| ACL_MDL_MPAIMID_SIZET = 4 | Reserved configuration.|
| ACL_MDL_AICQOS_SIZET = 5 | Reserved configuration.|
| ACL_MDL_AICOST_SIZET = 6 | Reserved configuration.|
| ACL_MDL_MEC_TIMETHR_SIZET = 7 | Reserved configuration.|

<!-- npu="950,A3,910b,910,310p,310b" id7 -->
Note that only `ACL_MDL_STREAM_SYNC_TIMEOUT` and `ACL_MDL_EVENT_SYNC_TIMEOUT` are supported.
<!-- end id7 -->
