# aclrtStreamAttr

| Enumerated Item| Description|
| --- | --- |
| ACL_STREAM_ATTR_FAILURE_MODE = 1 | Sets the task scheduling mode for a stream to determine whether to execute the next task after a task within this stream encounters an error.<br>By default, the task scheduling mode cannot be set for a stream.<br>The function of setting the task scheduling mode by using this attribute is the same as that of the [set_stream_failure_mode](../stream/function-set_stream_failure_mode.md) call.|
| ACL_STREAM_ATTR_FLOAT_OVERFLOW_CHECK = 2 | Enables or disables the overflow detection function for a specified stream when the upper-layer training framework (such as PyTorch) is connected. After the function is disabled, you cannot use the overflow detection operator to check whether a task overflows.<br>After the overflow detection function is enabled or disabled, the setting takes effect only for new tasks. Previously delivered tasks remain unaffected.<br>The function of setting the overflow/underflow detection switch by using this attribute is the same as that of the [set_stream_overflow_switch](../stream/function-set_stream_overflow_switch.md) call.|
| ACL_STREAM_ATTR_USER_CUSTOM_TAG = 3 | Sets the overflow detection group tag on a stream to determine the detection granularity when an overflow occurs. If no group tag is set, the process granularity is used by default. If a group tag is set, only streams sharing the same group tag as the stream where an overflow occurs are subject to detection.|
| ACL_STREAM_ATTR_PRIORITY = 5 | Sets the stream priority.|

<!-- npu="950,A3,910b" id1 -->
For Ascend 950PR&950DT products, Atlas A3 products, and Atlas A2 products, the stream priority can be set.
<!-- end id1 -->

<!-- npu="910,310p,310b" id2 -->
For Atlas 200I/500 A2 inference products, Atlas inference products, and Atlas training products, the stream priority cannot be set.
<!-- end id2 -->
