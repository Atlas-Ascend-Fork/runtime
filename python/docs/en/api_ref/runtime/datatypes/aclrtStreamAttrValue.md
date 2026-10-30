# aclrtStreamAttrValue

| Name| Description|
| --- | --- |
| failureMode | When setting the **ACL_STREAM_ATTR_FAILURE_MODE** attribute in **aclrtStreamAttr**, the value options are as follows:<br>- `0`: If a task fails, the system continues to execute the next task. The default value is `0`.<br>- `1`: After a task fails, the subsequent tasks are stopped. This mode is also called stop-on-failure. After the stop-on-failure mode is triggered, new tasks cannot be delivered. If the stop-on-failure mode is set for a stream, the stop-on-failure mode also applies to other streams in the context of the stream.|
| overflowSwitch | When setting `ACL_STREAM_ATTR_FLOAT_OVERFLOW_CHECK` (overflow detection switch) in `aclrtStreamAttr`, the attribute values are as follows:<br>- `0`: disables overflow detection. Defaults to `0`.<br>- `1`: enables overflow detection.|
| userCustomTag | When setting `ACL_STREAM_ATTR_USER_CUSTOM_TAG` (overflow detection group tag) in `aclrtStreamAttr`, the attribute value ranges from 0 to the maximum value of the uint32_t type.|
| streamPriority | When setting `ACL_STREAM_ATTR_PRIORITY` (stream priority) in `aclrtStreamAttr`, the attribute value range is [0, 7]. A smaller value indicates a higher priority. The default value is `0`.|
| reserve | Reserved.|
