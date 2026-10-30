# Function: get\_device\_utilization\_rate

## Applicable Products

<!-- npu="950" id1 -->
- Ascend 950PR&950DT products: Supported
<!-- end id1 -->
<!-- npu="A3" id2 -->
- Atlas A3 products: Supported
<!-- end id2 -->
<!-- npu="910b" id3 -->
- Atlas A2 products: Supported
<!-- end id3 -->
<!-- npu="310b" id4 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas inference products: Supported
<!-- end id5 -->
<!-- npu="910" id6 -->
- Atlas training products: Supported
<!-- end id6 -->

## Function

Queries the utilization of the Cube, Vector, AI CPU, and other components on a device.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtGetDeviceUtilizationRate(int32_t deviceId, aclrtUtilizationInfo *utilizationInfo)
    ```

- **Python Function**

    ```python
    utilization_info, ret = acl.rt.get_device_utilization_rate(device_id)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| device_id | Int, device ID.<br>After the number of available devices is obtained by calling [acl.rt.get_device_count](function-get_device_count.md), the value range of the device ID is [0, Number of available devices – 1].|

## Return Values

| Return Value| Description|
| --- | --- |
| utilization_info | Dict, utilization information dictionary of the aclrtUtilizationInfo type. For details, see [aclrtUtilizationInfo](../datatypes/aclrtUtilizationInfo.md).|
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- For Ascend virtual instances, this API cannot be called to query the usage, and the returned value has no meaning.
- When profiling is enabled, this API cannot be called to query the utilization, and the returned value has no meaning.
- Querying the memory usage of a device is a reserved function and is not supported in the current version. If this API is called to query the memory usage, the returned value is `-1`.
<!-- npu="910" id7 -->
- Atlas training products do not have vectors. When this API is called to query the vector usage, the returned value is `-1`.
<!-- end id7 -->
