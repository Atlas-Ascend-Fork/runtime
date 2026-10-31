# 4. Device Management

<!-- md-trans-meta sourceCommit=unknown translatedAt=2026-10-26T07:07:37.277Z pushedAt=2026-10-29T06:32:11.880Z nl=2 -->

This section describes CANN Runtime's device management APIs, which are used for device setting, resetting, query, synchronization, and P2P access.

- [`aclError aclrtSetDevice(int32_t deviceId)`](#aclrtSetDevice): Specifies the device used for computation in the current thread. You can call aclrtSetDevice in different threads to specify the same device for computation.
- [`aclError aclrtResetDevice(int32_t deviceId)`](#aclrtResetDevice): Resets the current device used for computation and releases resources on the device.
- [`aclError aclrtResetDeviceForce(int32_t deviceId)`](#aclrtResetDeviceForce): Resets the current device used for computation and releases resources on the device.
- [`aclError aclrtGetDevice(int32_t *deviceId)`](#aclrtGetDevice): Obtains the ID of the device currently in use.
- [`aclError aclrtGetRunMode(aclrtRunMode *runMode)`](#aclrtGetRunMode): Obtains the operating mode of the current AI software stack.
- [`aclError aclrtSetTsDevice(aclrtTsId tsId)`](#aclrtSetTsDevice): Sets the Task Schedule to be used for this computation.
- [`aclError aclrtGetDeviceCount(uint32_t *count)`](#aclrtGetDeviceCount): Obtains the number of available devices.
- [`aclError aclrtGetDeviceUtilizationRate(int32_t deviceId, aclrtUtilizationInfo *utilizationInfo)`](#aclrtGetDeviceUtilizationRate): Queries the utilization of Cube, Vector, and AI CPU on the device.
- [`aclError aclrtQueryDeviceStatus(int32_t deviceId, aclrtDeviceStatus *deviceStatus)`](#aclrtQueryDeviceStatus): Queries whether the device status is normal and available or abnormal and unavailable.
- [`const char *aclrtGetSocName()`](#aclrtGetSocName): Queries the AI processor version in the runtime environment.
- [`aclError aclrtSetDeviceSatMode(aclrtFloatOverflowMode mode)`](#aclrtSetDeviceSatMode): Sets the output mode of floating-point computation results on the current device.
- [`aclError aclrtGetDeviceSatMode(aclrtFloatOverflowMode *mode)`](#aclrtGetDeviceSatMode): Queries the output mode of floating-point computation results on the current device.
- [`aclError aclrtDeviceCanAccessPeer(int32_t *canAccessPeer, int32_t deviceId, int32_t peerDeviceId)`](#aclrtDeviceCanAccessPeer): Queries whether data exchange is supported between devices.
- [`aclError aclrtDeviceEnablePeerAccess(int32_t peerDeviceId, uint32_t flags)`](#aclrtDeviceEnablePeerAccess): Enables data exchange between the current device and the specified device. Enabling data exchange is device-level.
- [`aclError aclrtDeviceDisablePeerAccess(int32_t peerDeviceId)`](#aclrtDeviceDisablePeerAccess): Disables data exchange between the current device and the specified device. Disabling data exchange is device-level.
- [`aclError aclrtDevicePeerAccessStatus(int32_t deviceId, int32_t peerDeviceId, int32_t *status)`](#aclrtDevicePeerAccessStatus): Queries the data exchange status between two devices.
- [`aclError aclrtGetOverflowStatus(void *outputAddr, size_t outputSize, aclrtStream stream)`](#aclrtGetOverflowStatus): Obtains the overflow status of tasks on all streams under the current device and copies the status value to the device memory requested by the user. This API is asynchronous.
- [`aclError aclrtResetOverflowStatus(aclrtStream stream)`](#aclrtResetOverflowStatus): Clears the overflow status of tasks on all streams under the current device. This API is asynchronous.
- [`aclError aclrtGetFloatOverflowStatus(void *outputAddr, uint64_t outputSize, aclrtStream stream)`](#aclrtGetFloatOverflowStatus): Gets the overflow status of floating-point operations on the current device and writes the status value to the device memory allocated by the user. This API is asynchronous.
- [`aclError aclrtResetFloatOverflowStatus(aclrtStream stream)`](#aclrtResetFloatOverflowStatus): Clears the overflow status of floating-point operations on the current device. This API is asynchronous.
- [`aclError aclrtNpuGetFloatOverFlowStatus(void *outputAddr, uint64_t outputSize, uint32_t checkMode, aclrtStream stream)`](#aclrtNpuGetFloatOverFlowStatus): Dispatches a task to get the overflow status of floating-point operations and writes the status value to the device memory allocated by the user. This API is asynchronous.
- [`aclError aclrtNpuClearFloatOverFlowStatus(uint32_t checkMode, aclrtStream stream)`](#aclrtNpuClearFloatOverFlowStatus): Dispatches a task to clear the overflow status of floating-point operations. This API is asynchronous.
- [`aclError aclrtSynchronizeDevice(void)`](#aclrtSynchronizeDevice): Blocks the current thread until the device corresponding to the context bound to the current thread completes computation.
- [`aclError aclrtSynchronizeDeviceWithTimeout(int32_t timeout)`](#aclrtSynchronizeDeviceWithTimeout): Blocks the current thread until the device corresponding to the context bound to the current thread completes computation.
- [`aclError aclrtGetDeviceInfo(uint32_t deviceId, aclrtDevAttr attr, int64_t *value)`](#aclrtGetDeviceInfo): Gets information about the specified device.
- [`aclError aclrtDeviceGetStreamPriorityRange(int32_t *leastPriority, int32_t *greatestPriority)`](#aclrtDeviceGetStreamPriorityRange): Queries the lowest and highest stream priorities supported by the hardware.
- [`aclError aclrtGetDeviceCapability(int32_t deviceId, aclrtDevFeatureType devFeatureType, int32_t *value)`](#aclrtGetDeviceCapability): Queries the supported feature information.
- [`aclError aclrtGetDevicesTopo(uint32_t deviceId, uint32_t otherDeviceId, uint64_t *value)`](#aclrtGetDevicesTopo): Gets the network topology relationship between two devices.
- [`aclError aclrtRegDeviceStateCallback(const char *regName, aclrtDeviceStateCallback callback, void *args)`](#aclrtRegDeviceStateCallback): Registers a device state callback function. Duplicate registration is not supported.
- [`aclError aclrtGetLogicDevIdByUserDevId(const int32_t userDevid, int32_t *const logicDevId)`](#aclrtGetLogicDevIdByUserDevId): Obtains the corresponding logical device ID based on the user device ID.
- [`aclError aclrtGetUserDevIdByLogicDevId(const int32_t logicDevId, int32_t *const userDevid)`](#aclrtGetUserDevIdByLogicDevId): Obtains the corresponding user device ID based on the logical device ID.
- [`aclError aclrtGetLogicDevIdByPhyDevId(const int32_t phyDevId, int32_t *const logicDevId)`](#aclrtGetLogicDevIdByPhyDevId): Obtains the corresponding logical device ID based on the physical device ID.
- [`aclError aclrtGetPhyDevIdByLogicDevId(const int32_t logicDevId, int32_t *const phyDevId)`](#aclrtGetPhyDevIdByLogicDevId): Obtains the corresponding physical device ID based on the logical device ID.
- [`aclError aclrtGetUserDevIdByPhyDevId(const int32_t phyDevId, int32_t *const userDevId)`](#aclrtGetUserDevIdByPhyDevId): Obtains the corresponding user device ID based on the physical device ID.
- [`aclError aclrtGetPhyDevIdByUserDevId(const int32_t userDevId, int32_t *const phyDevId)`](#aclrtGetPhyDevIdByUserDevId): Obtains the corresponding physical device ID based on the user device ID.
- [`aclError aclrtDeviceGetUuid(int32_t deviceId, aclrtUuid *uuid)`](#aclrtDeviceGetUuid): Obtains the UUID (Universally Unique Identifier) of a device.
- [`aclError aclrtDeviceGetPCIBusId(int32_t deviceId, char *pciBusId, int32_t len)`](#aclrtDeviceGetPCIBusId): Obtains the PCI bus ID of the corresponding device based on the device ID.
- [`aclError aclrtDeviceGetByPCIBusId(const char *pciBusId, int32_t *deviceId)`](#aclrtDeviceGetByPCIBusId): Obtains the corresponding device ID based on the PCI bus ID.
- [`aclError aclrtDeviceGetBareTgid(int32_t *pid)`](#aclrtDeviceGetBareTgid): Obtains the process ID of the current process.
- [`aclError aclrtDeviceGetHostAtomicCapabilities(uint32_t* capabilities, const aclrtAtomicOperation* operations, const uint32_t count, int32_t deviceId)`](#aclrtDeviceGetHostAtomicCapabilities): Queries the details of atomic operations supported between a specified device and the host.
- [`aclError aclrtDeviceGetP2PAtomicCapabilities(uint32_t* capabilities, const aclrtAtomicOperation* operations, const uint32_t count, int32_t srcDeviceId, int32_t dstDeviceId)`](#aclrtDeviceGetP2PAtomicCapabilities): Queries the details of atomic operations supported between two devices within an AI Server. An AI Server is a general term for a server form composed of multiple devices.
- [`aclError aclrtDeviceSetLimit(aclrtDeviceLimit limit, size_t value)`](#aclrtDeviceSetLimit): Sets the device resource limits of the current process, such as the SIMT operator stack size and the SIMT Printf buffer size.
- [`aclError aclrtDeviceGetLimit(aclrtDeviceLimit limit, size_t *value)`](#aclrtDeviceGetLimit): Obtains the device resource limits of the current process.
- [`aclError aclrtDeviceL2CacheFlush(void* rsv)`](#aclrtDeviceL2CacheFlush): Flushes the L2 Cache of the current device.

<a id="aclrtSetDevice"></a>

## aclrtSetDevice

```c
aclError aclrtSetDevice(int32_t deviceId)
```

### Applicable Products

<!-- npu="950" id295 -->
- Ascend 950PR&950DT products: Supported
<!-- end id295 -->
<!-- npu="A3" id296 -->
- Atlas A3 products: Supported
<!-- end id296 -->
<!-- npu="910b" id297 -->
- Atlas A2 products: Supported
<!-- end id297 -->
<!-- npu="310b" id298 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id298 -->
<!-- npu="310p" id299 -->
- Atlas inference products: Supported
<!-- end id299 -->
<!-- npu="910" id300 -->
- Atlas training products: Supported
<!-- end id300 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id1 -->

### Function

Sets the compute device in the current thread. aclrtSetDevice can be called to specify the same device for computation in different threads.

<!-- npu="950,A3,910b,910,310p,310b" id1 -->
If there are multiple devices, aclrtSetDevice can be called in the process to switch to another device.
<!-- end id1 -->

Calling this API implicitly creates a default context that contains a default stream. In multiple threads of the same process, if aclrtSetDevice is called and the same device is specified for computation, these threads share the same default context.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| deviceId | Input | device ID.<br>After you call [aclrtGetDeviceCount](#aclrtGetDeviceCount) to obtain the number of available devices, the value range of this device ID is [0, (number of available devices - 1)]. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

### Constraints

After calling aclrtSetDevice to specify the device for computation, if the resources on the device are no longer needed, call [aclrtResetDevice](#aclrtResetDevice) or [aclrtResetDeviceForce](#aclrtResetDeviceForce) to release the device resources used by the current process in a timely manner. If the Reset API is not called, the device resources used by the current process are also released when the process exits:

- If [aclrtResetDevice](#aclrtResetDevice) is called to release device resources:

  The aclrtResetDevice API internally uses reference counting. It is recommended that aclrtResetDevice be used in pairs with [aclrtSetDevice](#aclrtSetDevice). Each call to aclrtSetDevice increments the reference count by one, and each call to aclrtResetDevice decrements the reference count by one. The resources on the device are actually released only when the reference count reaches 0.

- If [aclrtResetDeviceForce](#aclrtResetDeviceForce) is called to release device resources:

  aclrtResetDeviceForce can be used in pairs with aclrtSetDevice, or it can be used without pairing. If it is not used in pairs, after aclrtSetDevice is called once or multiple times for the same device in a process, calling aclrtResetDeviceForce only once releases the resources on the device.

<br>
<br>
<br>

<a id="aclrtResetDevice"></a>

## aclrtResetDevice

```c
aclError aclrtResetDevice(int32_t deviceId)
```

### Applicable Products

<!-- npu="950" id288 -->
- Ascend 950PR&950DT products: Supported
<!-- end id288 -->
<!-- npu="A3" id289 -->
- Atlas A3 products: Supported
<!-- end id289 -->
<!-- npu="910b" id290 -->
- Atlas A2 products: Supported
<!-- end id290 -->
<!-- npu="310b" id291 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id291 -->
<!-- npu="310p" id292 -->
- Atlas inference products: Supported
<!-- end id292 -->
<!-- npu="910" id293 -->
- Atlas training products: Supported
<!-- end id293 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id2 -->

### Function

Resets the current compute device and releases the resources on the device. The resources to be released include the default context, default stream, and all streams created in the default context. If tasks in the default context or default stream have not yet completed, the system will wait for the tasks to finish before releasing the resources.

The aclrtResetDevice API internally uses reference counting. It is recommended that aclrtResetDevice be used in pairs with [aclrtSetDevice](#aclrtSetDevice). Each call to aclrtSetDevice increments the reference count by one, and each call to aclrtResetDevice decrements the reference count by one. The resources on the device are actually released only when the reference count reaches 0.

If aclrtSetDevice is called multiple times without calling aclrtResetDevice to release the device resources used by the current thread, the device resources used by the current process are also released when the process exits.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| deviceId | Input | Device ID. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

### Constraints

If there are explicitly created contexts, streams, or events on the device to be reset, you are advised to follow the following calling sequence before resetting. Otherwise, exceptions may occur.

**API call sequence**: Call [aclrtDestroyEvent](07_event_management.md#aclrtDestroyEvent) to release the event/Call [aclrtDestroyStream](06_stream_management.md#aclrtDestroyStream) to release the explicitly created stream**--\> Call [aclrtDestroyContext](05_context_management.md#aclrtDestroyContext) to release the explicitly created context--\>** Call aclrtResetDevice

<br>
<br>
<br>

<a id="aclrtResetDeviceForce"></a>

## aclrtResetDeviceForce

```c
aclError aclrtResetDeviceForce(int32_t deviceId)
```

### Applicable Products

<!-- npu="950" id1849 -->
- Ascend 950PR&950DT products: Supported
<!-- end id1849 -->
<!-- npu="A3" id1850 -->
- Atlas A3 products: Supported
<!-- end id1850 -->
<!-- npu="910b" id1851 -->
- Atlas A2 products: Supported
<!-- end id1851 -->
<!-- npu="310b" id1852 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id1852 -->
<!-- npu="310p" id1853 -->
- Atlas inference products: Supported
<!-- end id1853 -->
<!-- npu="910" id1854 -->
- Atlas training products: Supported
<!-- end id1854 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id3 -->

### Function

Resets the current compute device and releases the resources on the device. The resources to be released include the default context, default stream, and all streams created in the default context. If tasks in the default context or default stream have not yet completed, the system will wait for the tasks to finish before releasing the resources.

aclrtResetDeviceForce can be used in pairs with aclrtSetDevice, or it can be used without pairing. If it is not used in pairs, after aclrtSetDevice is called once or multiple times for the same device in a process, calling aclrtResetDeviceForce only once releases the resources on the device.

```text
// Used in pair with the aclrtSetDevice API:
aclrtSetDevice(1) -> aclrtResetDeviceForce(1) -> aclrtSetDevice(1) -> aclrtResetDeviceForce(1)
 
// Used without pairing with the aclrtSetDevice API:
aclrtSetDevice(1) -> aclrtSetDevice(1) -> aclrtResetDeviceForce(1)
```

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| deviceId | Input | Device ID. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

### Constraints

- In a multi-thread scenario, if each thread calls the [aclrtSetDevice](#aclrtSetDevice) API and the aclrtResetDeviceForce API for the same device, as shown below, the aclrtResetDeviceForce API in thread 2 returns an error because the aclrtResetDeviceForce API in thread 1 has already released the resources of Device 1:

    ```text
    Timeline ----------------------------------------------------------------------------->
    Thread 1: aclrtSetDevice(1)           aclrtResetDeviceForce(1)
    Thread 2: aclrtSetDevice(1)                                   aclrtResetDeviceForce(1)
    ```

    In a multi-thread scenario, the correct approach is to call aclrtResetDeviceForce once at the end of thread execution to release the device resources, as shown below:

    ```text
    Timeline ----------------------------------------------------------------------------->
    Thread 1: aclrtSetDevice(1)    
    Thread 2: aclrtSetDevice(1)                                   aclrtResetDeviceForce(1)
    ```

- The [aclrtResetDevice](#aclrtResetDevice) API and the aclrtResetDeviceForce API can be used together. However, when they are mixed, if the call counts or call order of the two Reset APIs are incorrect, the API returns an error.

    ```text
    # Correct approach when mixing:
    # Both Reset APIs are paired with the Set API, and aclrtResetDeviceForce is called after aclrtResetDevice.
    aclrtSetDevice(1) -> aclrtResetDevice(1) -> aclrtSetDevice(1) -> aclrtResetDeviceForce(1)
    aclrtSetDevice(1) -> aclrtSetDevice(1) -> aclrtResetDevice(1) -> aclrtResetDeviceForce(1)
    
    # Incorrect usage when mixing the two APIs:
    # aclrtResetDevice internally uses reference counting. Each call to aclrtResetDevice decrements the reference count by 1. When the reference count reaches 0, the resources on the Device are actually released. Calling aclrtResetDevice or aclrtResetDeviceForce again after that returns an error.
    aclrtSetDevice(1) -> aclrtSetDevice(1) -> aclrtResetDevice(1)-->aclrtResetDevice(1)-->aclrtResetDeviceForce(1)
    aclrtSetDevice(1) -> aclrtSetDevice(1) -> aclrtResetDevice(1)-->aclrtResetDeviceForce(1)-->aclrtResetDeviceForce(1)
    # aclrtResetDeviceForce must be called after aclrtResetDevice; otherwise, the API returns an error.
    aclrtSetDevice(1) -> aclrtSetDevice(1) -> aclrtResetDeviceForce(1)-->aclrtResetDevice(1)
    ```

<br>
<br>
<br>

<a id="aclrtGetDevice"></a>

## aclrtGetDevice

```c
aclError aclrtGetDevice(int32_t *deviceId)
```

### Applicable Products

<!-- npu="950" id3242 -->
- Ascend 950PR&950DT products: Supported
<!-- end id3242 -->
<!-- npu="A3" id3243 -->
- Atlas A3 products: Supported
<!-- end id3243 -->
<!-- npu="910b" id3244 -->
- Atlas A2 products: Supported
<!-- end id3244 -->
<!-- npu="310b" id3245 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id3245 -->
<!-- npu="310p" id3246 -->
- Atlas inference products: Supported
<!-- end id3246 -->
<!-- npu="910" id3247 -->
- Atlas training products: Supported
<!-- end id3247 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id4 -->

### Function

Obtains the ID of the device currently in use.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| deviceId | Output | Pointer to the device ID. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

### Constraints

If no compute device is specified in advance (for example, by calling the [aclrtSetDevice](#aclrtSetDevice) API), an error is returned when the aclrtGetDevice API is called.

<br>
<br>
<br>

<a id="aclrtGetRunMode"></a>

## aclrtGetRunMode

```c
aclError aclrtGetRunMode(aclrtRunMode *runMode)
```

### Applicable Products

<!-- npu="950" id596 -->
- Ascend 950PR&950DT products: Supported
<!-- end id596 -->
<!-- npu="A3" id597 -->
- Atlas A3 products: Supported
<!-- end id597 -->
<!-- npu="910b" id598 -->
- Atlas A2 products: Supported
<!-- end id598 -->
<!-- npu="310b" id599 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id599 -->
<!-- npu="310p" id600 -->
- Atlas inference products: Supported
<!-- end id600 -->
<!-- npu="910" id601 -->
- Atlas training products: Supported
<!-- end id601 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id5 -->

### Function

Obtains the operating mode of the current AI software stack.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| runMode | Output | Pointer to the operating mode. For the type definition, see [aclrtRunMode](25-02_Enumerations.md#aclrtRunMode). |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

<br>
<br>
<br>

<a id="aclrtSetTsDevice"></a>

## aclrtSetTsDevice

```c
aclError aclrtSetTsDevice(aclrtTsId tsId)
```

### Applicable Products

<!-- npu="950" id3046 -->
- Ascend 950PR&950DT products: Supported
<!-- end id3046 -->
<!-- npu="A3" id3047 -->
- Atlas A3 products: Supported
<!-- end id3047 -->
<!-- npu="910b" id3048 -->
- Atlas A2 products: Supported
<!-- end id3048 -->
<!-- npu="310b" id3049 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id3049 -->
<!-- npu="310p" id3050 -->
- Atlas inference products: Supported
<!-- end id3050 -->
<!-- npu="910" id3051 -->
- Atlas training products: Supported
<!-- end id3051 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id6 -->

### Function

Sets the task schedule required for the computation.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| tsId | Input | Specifies the Task Schedule to be used for this computation. If the AI processor has only the AI CORE Task Schedule and no VECTOR Core Task Schedule, setting this parameter has no effect, and the AI CORE Task Schedule is used by default. |

aclrtTsId is defined as follows:

```c
typedef enum aclrtTsId {
    ACL_TS_ID_AICORE  = 0,  // Use AI CORE Task Schedule.
    ACL_TS_ID_AIVECTOR = 1, // Use VECTOR Core Task Schedule.
    ACL_TS_ID_RESERVED = 2, 
} aclrtTsId;
```

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

<br>
<br>
<br>

<a id="aclrtGetDeviceCount"></a>

## aclrtGetDeviceCount

```c
aclError aclrtGetDeviceCount(uint32_t *count)
```

### Applicable Products

<!-- npu="950" id1653 -->
- Ascend 950PR&950DT products: Supported
<!-- end id1653 -->
<!-- npu="A3" id1654 -->
- Atlas A3 products: Supported
<!-- end id1654 -->
<!-- npu="910b" id1655 -->
- Atlas A2 products: Supported
<!-- end id1655 -->
<!-- npu="310b" id1656 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id1656 -->
<!-- npu="310p" id1657 -->
- Atlas inference products: Supported
<!-- end id1657 -->
<!-- npu="910" id1658 -->
- Atlas training products: Supported
<!-- end id1658 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id7 -->

### Function

Obtains the number of available devices.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| count | Output | Pointer to the number of devices. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

<br>
<br>
<br>

<a id="aclrtGetDeviceUtilizationRate"></a>

## aclrtGetDeviceUtilizationRate

```c
aclError aclrtGetDeviceUtilizationRate(int32_t deviceId, aclrtUtilizationInfo *utilizationInfo)
```

### Applicable Products

<!-- npu="950" id393 -->
- Ascend 950PR&950DT products: Supported
<!-- end id393 -->
<!-- npu="A3" id394 -->
- Atlas A3 products: Supported
<!-- end id394 -->
<!-- npu="910b" id395 -->
- Atlas A2 products: Supported
<!-- end id395 -->
<!-- npu="310b" id396 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id396 -->
<!-- npu="310p" id397 -->
- Atlas inference products: Supported
<!-- end id397 -->
<!-- npu="910" id398 -->
- Atlas training products: Supported
<!-- end id398 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id8 -->

### Function

Queries the utilization of the Cube, Vector, AI CPU, and other components on a device.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| deviceId | Input | device ID.<br>After you call [aclrtGetDeviceCount](#aclrtGetDeviceCount) to obtain the number of available devices, the value range of this device ID is [0, (number of available devices - 1)]. |
| utilizationInfo | Output | Pointer to the utilization information struct. For the type definition, see [aclrtUtilizationInfo](25-04_Structs.md#aclrtUtilizationInfo). |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

### Constraints

- When this API queries Vector utilization, a query result of -1 indicates that Vector does not exist.
- The current version does not support querying device memory utilization. If memory utilization is queried through this API, the returned utilization is -1.
- When profiling is enabled, this API cannot be called to query the usage, and the returned value has no meaning.
<!-- npu="910b,910,310p" id5 -->
- For Ascend virtual instances, this API cannot be called to query the usage, and the returned value has no meaning.
<!-- end id5 -->

<br>
<br>
<br>

<a id="aclrtQueryDeviceStatus"></a>

## aclrtQueryDeviceStatus

```c
aclError aclrtQueryDeviceStatus(int32_t deviceId, aclrtDeviceStatus *deviceStatus)
```

### Applicable Products

<!-- npu="950" id1737 -->
- Ascend 950PR&950DT products: Supported
<!-- end id1737 -->
<!-- npu="A3" id1738 -->
- Atlas A3 products: Supported
<!-- end id1738 -->
<!-- npu="910b" id1739 -->
- Atlas A2 products: Supported
<!-- end id1739 -->
<!-- npu="310b" id1740 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id1740 -->
<!-- npu="310p" id1741 -->
- Atlas inference products: Supported
<!-- end id1741 -->
<!-- npu="910" id1742 -->
- Atlas training products: Supported
<!-- end id1742 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id9 -->

### Function

Queries the status of a device (normal or abnormal).

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| deviceId | Input | Device ID.<br>After you call [aclrtGetDeviceCount](#aclrtGetDeviceCount) to obtain the number of available devices, the value range of this device ID is [0, (number of available devices - 1)]. |
| deviceStatus | Output | device status. See [aclrtDeviceStatus](25-02_Enumerations.md#aclrtDeviceStatus) for the type definition. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

<br>
<br>
<br>

<a id="aclrtGetSocName"></a>

## aclrtGetSocName

```c
const char *aclrtGetSocName()
```

### Applicable Products

<!-- npu="950" id2640 -->
- Ascend 950PR&950DT products: Supported
<!-- end id2640 -->
<!-- npu="A3" id2641 -->
- Atlas A3 products: Supported
<!-- end id2641 -->
<!-- npu="910b" id2642 -->
- Atlas A2 products: Supported
<!-- end id2642 -->
<!-- npu="310b" id2643 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id2643 -->
<!-- npu="310p" id2644 -->
- Atlas inference products: Supported
<!-- end id2644 -->
<!-- npu="910" id2645 -->
- Atlas training products: Supported
<!-- end id2645 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id10 -->

### Function

Queries the AI processor version of the runtime environment.

### Parameters

None

### Return Values

Returns a pointer to the AI processor version string.

If the chip version fails to be obtained through this API, a null pointer is returned. If the number of devices in the runtime environment is greater than 1, the AI processor version name of Device 0 is always returned.

<br>
<br>
<br>

<a id="aclrtSetDeviceSatMode"></a>

## aclrtSetDeviceSatMode

```c
aclError aclrtSetDeviceSatMode(aclrtFloatOverflowMode mode)
```

### Applicable Products

<!-- npu="950" id3004 -->
- Ascend 950PR&950DT products: Supported
<!-- end id3004 -->
<!-- npu="A3" id3005 -->
- Atlas A3 products: Supported
<!-- end id3005 -->
<!-- npu="910b" id3006 -->
- Atlas A2 products: Supported
<!-- end id3006 -->
<!-- npu="310b" id3007 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id3007 -->
<!-- npu="310p" id3008 -->
- Atlas inference products: Supported
<!-- end id3008 -->
<!-- npu="910" id3009 -->
- Atlas training products: Supported
<!-- end id3009 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id11 -->

### Function

Sets the output mode of the floating-point computation result of the device.

The setting takes effect only for the streams created on the device after this API call.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| mode | Input | Sets the output mode of floating-point computation results. For the type definition, see [aclrtFloatOverflowMode](25-02_Enumerations.md#aclrtFloatOverflowMode). |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

<br>
<br>
<br>

<a id="aclrtGetDeviceSatMode"></a>

## aclrtGetDeviceSatMode

```c
aclError aclrtGetDeviceSatMode(aclrtFloatOverflowMode *mode)
```

### Applicable Products

<!-- npu="950" id1051 -->
- Ascend 950PR&950DT products: Supported
<!-- end id1051 -->
<!-- npu="A3" id1052 -->
- Atlas A3 products: Supported
<!-- end id1052 -->
<!-- npu="910b" id1053 -->
- Atlas A2 products: Supported
<!-- end id1053 -->
<!-- npu="310b" id1054 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id1054 -->
<!-- npu="310p" id1055 -->
- Atlas inference products: Supported
<!-- end id1055 -->
<!-- npu="910" id1056 -->
- Atlas training products: Supported
<!-- end id1056 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id12 -->

### Function

Queries the output mode of the floating-point computation result of the device.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| mode | Output | Obtains the output mode of floating-point computation results. For the type definition, see [aclrtFloatOverflowMode](25-02_Enumerations.md#aclrtFloatOverflowMode). |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

<br>
<br>
<br>

<a id="aclrtDeviceCanAccessPeer"></a>

## aclrtDeviceCanAccessPeer

```c
aclError aclrtDeviceCanAccessPeer(int32_t *canAccessPeer, int32_t deviceId, int32_t peerDeviceId)
```

### Applicable Products

<!-- npu="950" id2493 -->
- Ascend 950PR&950DT products: Supported
<!-- end id2493 -->
<!-- npu="A3" id2494 -->
- Atlas A3 products: Supported
<!-- end id2494 -->
<!-- npu="910b" id2495 -->
- Atlas A2 products: Supported
<!-- end id2495 -->
<!-- npu="310b" id2496 -->
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id2496 -->
<!-- npu="310p" id2497 -->
- Atlas inference products: Supported
<!-- end id2497 -->
<!-- npu="910" id2498 -->
- Atlas training products: Supported
<!-- end id2498 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id13 -->

### Function

Queries whether data exchange is supported between devices.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| canAccessPeer | Output | Whether data exchange is supported. 1 indicates supported, and 0 indicates not supported. |
| deviceId | Input | ID of the specified device. It cannot be the same as the peerDeviceId parameter value.<br>After you call [aclrtGetDeviceCount](#aclrtGetDeviceCount) to obtain the number of available devices, the value range of this device ID is [0, (number of available devices - 1)]. |
| peerDeviceId | Input | ID of the specified device. It cannot be the same as the deviceId parameter value.<br>After you call [aclrtGetDeviceCount](#aclrtGetDeviceCount) to obtain the number of available devices, the value range of this device ID is [0, (number of available devices - 1)]. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

### Constraints

- This API supports data exchange only in physical machines and containers.
- This API supports data exchange only between devices in the same PCIe switch. In AI Server applications, data exchange between devices is supported even when they reside in different PCIe switches.
- This API supports data exchange only between devices in the same physical machine or container.
- This API supports data exchange only between devices within the same process and across threads, and does not support data exchange between devices in different processes.
<!-- npu="310p" id6 -->
- For Atlas inference products in the open Control CPU mode, when the application runs on the Control CPU of a device, this API does not support data exchange between devices.
<!-- end id6 -->

<br>
<br>
<br>

<a id="aclrtDeviceEnablePeerAccess"></a>

## aclrtDeviceEnablePeerAccess

```c
aclError aclrtDeviceEnablePeerAccess(int32_t peerDeviceId, uint32_t flags)
```

### Applicable Products

<!-- npu="950" id2269 -->
- Ascend 950PR&950DT products: Supported
<!-- end id2269 -->
<!-- npu="A3" id2270 -->
- Atlas A3 products: Supported
<!-- end id2270 -->
<!-- npu="910b" id2271 -->
- Atlas A2 products: Supported
<!-- end id2271 -->
<!-- npu="310b" id2272 -->
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id2272 -->
<!-- npu="310p" id2273 -->
- Atlas inference products: Supported
<!-- end id2273 -->
<!-- npu="910" id2274 -->
- Atlas training products: Supported
<!-- end id2274 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id14 -->

### Function

Enables data exchange between the current device and a specified device. Enabling data exchange is device-level.

Data exchange enabled by calling this API is unidirectional. For example, if the current device ID is 0 and you call aclrtDeviceEnablePeerAccess to specify Device ID 1, only data exchange from Device 0 to Device 1 is possible. To enable data exchange from Device 1 to Device 0, switch the current device to Device 1 and call aclrtDeviceEnablePeerAccess again to specify device ID 0. Only then can data exchange from Device 1 to Device 0 be achieved.

You can call [aclrtDeviceCanAccessPeer](#aclrtDeviceCanAccessPeer) in advance to query whether data exchange is possible between the current device and the specified device. After enabling data exchange between devices, you can call [aclrtDeviceDisablePeerAccess](#aclrtDeviceDisablePeerAccess) to disable it.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| peerDeviceId | Input | Specified device ID, which cannot be the same as the current device ID.<br>After you call [aclrtGetDeviceCount](#aclrtGetDeviceCount) to obtain the number of available devices, the value range of this device ID is [0, (number of available devices - 1)]. |
| flags | Input | Reserved parameter, which must be set to 0. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

<!-- npu="310p" id7 -->
### Constraints

For Atlas inference products in the open Control CPU mode, when the application runs on the Control CPU of a device, this API does not support data exchange between devices.
<!-- end id7 -->

<br>
<br>
<br>

<a id="aclrtDeviceDisablePeerAccess"></a>

## aclrtDeviceDisablePeerAccess

```c
aclError aclrtDeviceDisablePeerAccess(int32_t peerDeviceId)
```

### Applicable Products

<!-- npu="950" id2962 -->
- Ascend 950PR&950DT products: Supported
<!-- end id2962 -->
<!-- npu="A3" id2963 -->
- Atlas A3 products: Supported
<!-- end id2963 -->
<!-- npu="910b" id2964 -->
- Atlas A2 products: Supported
<!-- end id2964 -->
<!-- npu="310b" id2965 -->
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id2965 -->
<!-- npu="310p" id2966 -->
- Atlas inference products: Supported
<!-- end id2966 -->
<!-- npu="910" id2967 -->
- Atlas training products: Supported
<!-- end id2967 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id15 -->

### Function

Disables the data exchange function between the current device and a specified device. Disabling the data exchange function is device-level.

After the data exchange between the current device and a specified device is enabled by calling [aclrtDeviceEnablePeerAccess](#aclrtDeviceEnablePeerAccess), you can call aclrtDeviceDisablePeerAccess to disable the data exchange function.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| peerDeviceId | Input | device ID, which cannot be the same as the ID of the current device.<br>After you call [aclrtGetDeviceCount](#aclrtGetDeviceCount) to obtain the number of available devices, the value range of this device ID is [0, (number of available devices - 1)]. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

<!-- npu="310p" id8 -->
### Constraints

For Atlas inference products in the open Control CPU mode, when the application runs on the Control CPU of a device, this API does not support data exchange between devices.
<!-- end id8 -->

<br>
<br>
<br>

<a id="aclrtDevicePeerAccessStatus"></a>

## aclrtDevicePeerAccessStatus

```c
aclError aclrtDevicePeerAccessStatus(int32_t deviceId, int32_t peerDeviceId, int32_t *status)
```

### Applicable Products

<!-- npu="950" id2955 -->
- Ascend 950PR&950DT products: Supported
<!-- end id2955 -->
<!-- npu="A3" id2956 -->
- Atlas A3 products: Supported
<!-- end id2956 -->
<!-- npu="910b" id2957 -->
- Atlas A2 products: Supported
<!-- end id2957 -->
<!-- npu="310b" id2958 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id2958 -->
<!-- npu="310p" id2959 -->
- Atlas inference products: Supported
<!-- end id2959 -->
<!-- npu="910" id2960 -->
- Atlas training products: Supported
<!-- end id2960 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id16 -->

### Function

Queries the data exchange status between two devices.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| deviceId | Input | ID of the specified device.<br>After you call [aclrtGetDeviceCount](#aclrtGetDeviceCount) to obtain the number of available devices, the value range of this device ID is [0, (number of available devices - 1)]. |
| peerDeviceId | Input | ID of the specified device.<br>After you call [aclrtGetDeviceCount](#aclrtGetDeviceCount) to obtain the number of available devices, the value range of this device ID is [0, (number of available devices - 1)]. |
| status | Output | Device status. 0 indicates that data exchange is not enabled; 1 indicates that data exchange is enabled. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

### Constraints

This API can only query the data exchange status of two devices whose IDs are within the value range. If the input device ID is out of the range [0, (number of available devices – 1)], the query result is 0 or the error code ACL_ERROR_RT_PARAM_INVALID is returned.

<br>
<br>
<br>

<a id="aclrtGetOverflowStatus"></a>

## aclrtGetOverflowStatus

```c
aclError aclrtGetOverflowStatus(void *outputAddr, size_t outputSize, aclrtStream stream)
```

### Applicable Products

<!-- npu="950" id1135 -->
- Ascend 950PR&950DT products: Supported
<!-- end id1135 -->
<!-- npu="A3" id1136 -->
- Atlas A3 products: Supported
<!-- end id1136 -->
<!-- npu="910b" id1137 -->
- Atlas A2 products: Supported
<!-- end id1137 -->
<!-- npu="310b" id1138 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id1138 -->
<!-- npu="310p" id1139 -->
- Atlas inference products: Supported
<!-- end id1139 -->
<!-- npu="910" id1140 -->
- Atlas training products: Supported
<!-- end id1140 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id17 -->

### Function

Queries the overflow status of tasks on all streams in the current device and copies the status value to the device memory that you requested. This API is asynchronous.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| outputAddr | Input&Output | Device memory allocated by the user, for example, through the aclrtMalloc API. |
| outputSize | Input | Size of the device memory to be allocated, in bytes. The fixed size is 64 bytes. |
| stream | Input | Specified stream used to dispatch the overflow status query task. See [aclrtStream](25-05_Typedefs.md#aclrtStream) for the type definition. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

<!-- npu="950,A3,910b" id9 -->
### Constraints

For Ascend 950PR&950DT products, Atlas A3 products, and Atlas A2 products, the overflow status queried by this API is process-level.
<!-- end id9 -->

<br>
<br>
<br>

<a id="aclrtResetOverflowStatus"></a>

## aclrtResetOverflowStatus

```c
aclError aclrtResetOverflowStatus(aclrtStream stream)
```

### Applicable Products

<!-- npu="950" id2276 -->
- Ascend 950PR&950DT products: Supported
<!-- end id2276 -->
<!-- npu="A3" id2277 -->
- Atlas A3 products: Supported
<!-- end id2277 -->
<!-- npu="910b" id2278 -->
- Atlas A2 products: Supported
<!-- end id2278 -->
<!-- npu="310b" id2279 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id2279 -->
<!-- npu="310p" id2280 -->
- Atlas inference products: Supported
<!-- end id2280 -->
<!-- npu="910" id2281 -->
- Atlas training products: Supported
<!-- end id2281 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id18 -->

### Function

Resets the overflow status of tasks on all streams in the current device. This API is asynchronous.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| stream | Input | Specifies the stream used to dispatch the overflow status reset task. See [aclrtStream](25-05_Typedefs.md#aclrtStream) for the type definition. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

<!-- npu="950,A3,910b" id10 -->
### Constraints

For Ascend 950PR&950DT products, Atlas A3 products, and Atlas A2 products, the overflow status cleared by this API is process-level.
<!-- end id10 -->

<br>
<br>
<br>

<a id="aclrtGetFloatOverflowStatus"></a>

## aclrtGetFloatOverflowStatus

```c
aclError aclrtGetFloatOverflowStatus(void *outputAddr, uint64_t outputSize, aclrtStream stream)
```

### Applicable Products

<!-- npu="950" id4101 -->
- Ascend 950PR&950DT products: Supported
<!-- end id4101 -->
<!-- npu="A3" id4102 -->
- Atlas A3 products: Supported
<!-- end id4102 -->
<!-- npu="910b" id4103 -->
- Atlas A2 products: Supported
<!-- end id4103 -->
<!-- npu="310b" id4104 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id4104 -->
<!-- npu="310p" id4105 -->
- Atlas inference products: Supported
<!-- end id4105 -->
<!-- npu="910" id4106 -->
- Atlas training products: Supported
<!-- end id4106 -->
<!-- npu="IPV350" id4107 -->
- IPV350: Not supported
<!-- end id4107 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id41 -->

### Function

Obtains the floating-point operation overflow status on the current device and writes the status value to the device memory allocated by you.

This API is asynchronous. A successful call only indicates that the task has been submitted, not that the task has been executed. After calling this API, call a synchronous API (for example, [aclrtSynchronizeStream](06_stream_management.md#aclrtSynchronizeStream)) to ensure that the task has been executed.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| outputAddr | Input&Output | As an input, outputAddr is a first-level address, which is the device memory address passed in by the user for storing the overflow status. The address cannot be empty, and the memory size cannot be smaller than outputSize.<br>As an output, this memory stores the overflow status data of floating-point operations on the current device. |
| outputSize | Input | Size of the device memory pointed to by outputAddr, in bytes, fixed at 64 bytes. |
| stream | Input | Specified stream used to dipatch the overflow status query task. See [aclrtStream](25-05_Typedefs.md#aclrtStream) for the type definition. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

### Constraints

- This API cannot be called during the stream capture phase.
- This API can only be used in pair with [aclrtResetFloatOverflowStatus](#aclrtResetFloatOverflowStatus).
- For Ascend 950PR&950DT products, Atlas A3 products, and Atlas A2 products, the overflow status queried by this API is process-level.

<br>
<br>
<br>

<a id="aclrtResetFloatOverflowStatus"></a>

## aclrtResetFloatOverflowStatus

```c
aclError aclrtResetFloatOverflowStatus(aclrtStream stream)
```

### Applicable Products

<!-- npu="950" id4108 -->
- Ascend 950PR&950DT products: Supported
<!-- end id4108 -->
<!-- npu="A3" id4109 -->
- Atlas A3 products: Supported
<!-- end id4109 -->
<!-- npu="910b" id4110 -->
- Atlas A2 products: Supported
<!-- end id4110 -->
<!-- npu="310b" id4111 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id4111 -->
<!-- npu="310p" id4112 -->
- Atlas inference products: Supported
<!-- end id4112 -->
<!-- npu="910" id4113 -->
- Atlas training products: Supported
<!-- end id4113 -->
<!-- npu="IPV350" id4114 -->
- IPV350: Not supported
<!-- end id4114 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id42 -->

### Function

Clears the overflow status of floating-point operations on the current device.

This API is asynchronous. A successful call only indicates that the task has been submitted, not that the task has been executed. After calling this API, call a synchronous API (for example, [aclrtSynchronizeStream](06_stream_management.md#aclrtSynchronizeStream)) to ensure that the task has been executed.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| stream | Input | Specifies the stream used to dispatch the overflow status clearing task. See [aclrtStream](25-05_Typedefs.md#aclrtStream) for the type definition. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

### Constraints

- This API cannot be called during the stream capture phase.
- For Ascend 950PR&950DT products, Atlas A3 products, and Atlas A2 products, the overflow status cleared by this API is process-level.

<br>
<br>
<br>

<a id="aclrtNpuGetFloatOverFlowStatus"></a>

## aclrtNpuGetFloatOverFlowStatus

```c
aclError aclrtNpuGetFloatOverFlowStatus(
    void *outputAddr, uint64_t outputSize, uint32_t checkMode, aclrtStream stream)
```

### Applicable Products

<!-- npu="950" id4115 -->
- Ascend 950PR&950DT products: Supported
<!-- end id4115 -->
<!-- npu="A3" id4116 -->
- Atlas A3 products: Supported
<!-- end id4116 -->
<!-- npu="910b" id4117 -->
- Atlas A2 products: Supported
<!-- end id4117 -->
<!-- npu="310b" id4118 -->
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id4118 -->
<!-- npu="310p" id4119 -->
- Atlas inference products: Not supported
<!-- end id4119 -->
<!-- npu="910" id4120 -->
- Atlas training products: Not supported
<!-- end id4120 -->
<!-- npu="IPV350" id4121 -->
- IPV350: Not supported
<!-- end id4121 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id43 -->

### Function

Obtains the floating-point operation overflow status on the current device and writes the status value to the device memory allocated by you.

The difference between this API and [aclrtGetFloatOverflowStatus](#aclrtGetFloatOverflowStatus) lies in the meaning of the outputAddr parameter: for aclrtGetFloatOverflowStatus, outputAddr is a first-level address that directly points to the actual output memory; for this API, outputAddr is a second-level address, and the device memory it points to stores the address of the actual output memory.

This API is asynchronous. A successful call only indicates that the task has been submitted, not that the task has been executed. After calling this API, call a synchronous API (for example, [aclrtSynchronizeStream](06_stream_management.md#aclrtSynchronizeStream)) to ensure that the task has been executed.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| outputAddr | Input&Output | As an input, outputAddr is a second-level address. The device memory it points to must store the address of the actual output memory, and the size of the actual output memory cannot be smaller than outputSize. outputAddr cannot be empty.<br>As an output, the actual output memory stores the queried floating-point operation overflow status data. |
| outputSize | Input | Size of the actual output memory, in bytes, fixed at 64 bytes. |
| checkMode | Input | Reserved parameter, currently fixed to 0. |
| stream | Input | Specifies the stream used to submit the floating-point operation overflow status query task. See [aclrtStream](25-05_Typedefs.md#aclrtStream) for the type definition. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

### Constraints

- This API cannot be called during the stream capture phase.
- This API can only be used in pair with [aclrtNpuClearFloatOverFlowStatus](#aclrtNpuClearFloatOverFlowStatus).

<br>
<br>
<br>

<a id="aclrtNpuClearFloatOverFlowStatus"></a>

## aclrtNpuClearFloatOverFlowStatus

```c
aclError aclrtNpuClearFloatOverFlowStatus(uint32_t checkMode, aclrtStream stream)
```

### Applicable Products

<!-- npu="950" id4122 -->
- Ascend 950PR&950DT products: Supported
<!-- end id4122 -->
<!-- npu="A3" id4123 -->
- Atlas A3 products: Supported
<!-- end id4123 -->
<!-- npu="910b" id4124 -->
- Atlas A2 products: Supported
<!-- end id4124 -->
<!-- npu="310b" id4125 -->
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id4125 -->
<!-- npu="310p" id4126 -->
- Atlas inference products: Not supported
<!-- end id4126 -->
<!-- npu="910" id4127 -->
- Atlas training products: Not supported
<!-- end id4127 -->
<!-- npu="IPV350" id4128 -->
- IPV350: Not supported
<!-- end id4128 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id44 -->

### Function

Dispatches a task on the specified stream to clear the floating-point operation overflow status.

This API is asynchronous. A successful call only indicates that the task has been submitted, not that the task has been executed. After calling this API, call a synchronous API (for example, [aclrtSynchronizeStream](06_stream_management.md#aclrtSynchronizeStream)) to ensure that the task has been executed.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| checkMode | Input | Reserved parameter, currently fixed to 0. |
| stream | Input | Stream used to dispatch the floating-point operation overflow status clearing task. For the type definition, see [aclrtStream](25-05_Typedefs.md#aclrtStream). |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

### Constraints

This API cannot be called during the stream capture phase.

<br>
<br>
<br>

<a id="aclrtSynchronizeDevice"></a>

## aclrtSynchronizeDevice

```c
aclError aclrtSynchronizeDevice(void)
```

### Applicable Products

<!-- npu="950" id1268 -->
- Ascend 950PR&950DT products: Supported
<!-- end id1268 -->
<!-- npu="A3" id1269 -->
- Atlas A3 products: Supported
<!-- end id1269 -->
<!-- npu="910b" id1270 -->
- Atlas A2 products: Supported
<!-- end id1270 -->
<!-- npu="310b" id1271 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id1271 -->
<!-- npu="310p" id1272 -->
- Atlas inference products: Supported
<!-- end id1272 -->
<!-- npu="910" id1273 -->
- Atlas training products: Supported
<!-- end id1273 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id19 -->

### Function

Blocks the current thread until the device corresponding to the context bound to the current thread completes its computation.

### Parameters

None

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

<br>
<br>
<br>

<a id="aclrtSynchronizeDeviceWithTimeout"></a>

## aclrtSynchronizeDeviceWithTimeout

```c
aclError aclrtSynchronizeDeviceWithTimeout(int32_t timeout)
```

### Applicable Products

<!-- npu="950" id2367 -->
- Ascend 950PR&950DT products: Supported
<!-- end id2367 -->
<!-- npu="A3" id2368 -->
- Atlas A3 products: Supported
<!-- end id2368 -->
<!-- npu="910b" id2369 -->
- Atlas A2 products: Supported
<!-- end id2369 -->
<!-- npu="310b" id2370 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id2370 -->
<!-- npu="310p" id2371 -->
- Atlas inference products: Supported
<!-- end id2371 -->
<!-- npu="910" id2372 -->
- Atlas training products: Supported
<!-- end id2372 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id20 -->

### Function

Blocks the current thread until the device corresponding to the context bound to the current thread completes computation. This API is an enhancement of [aclrtSynchronizeDevice](#aclrtSynchronizeDevice) that allows you to set a timeout. When an application exception occurs, the API exits on its own based on the configured timeout, and returns ACL\_ERROR\_RT\_STREAM\_SYNC\_TIMEOUT upon timeout exit.

If there are multiple devices, this API is called to wait for the device corresponding to the current context.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| timeout | Input | Timeout of the API.<br>Valid values are as follows:<br><br>  - -1: Wait indefinitely, which is the same as the [aclrtSynchronizeDevice](#aclrtSynchronizeDevice) API.<br>  - >0: Configure a specific timeout in milliseconds. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

<br>
<br>
<br>

<a id="aclrtGetDeviceInfo"></a>

## aclrtGetDeviceInfo

```c
aclError aclrtGetDeviceInfo(uint32_t deviceId, aclrtDevAttr attr, int64_t *value)
```

### Applicable Products

<!-- npu="950" id3032 -->
- Ascend 950PR&950DT products: Supported
<!-- end id3032 -->
<!-- npu="A3" id3033 -->
- Atlas A3 products: Supported
<!-- end id3033 -->
<!-- npu="910b" id3034 -->
- Atlas A2 products: Supported
<!-- end id3034 -->
<!-- npu="310b" id3035 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id3035 -->
<!-- npu="310p" id3036 -->
- Atlas inference products: Supported
<!-- end id3036 -->
<!-- npu="910" id3037 -->
- Atlas training products: Supported
<!-- end id3037 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id21 -->

### Function

Obtains information about a specified device.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| deviceId | Input | device ID.<br>After you call [aclrtGetDeviceCount](#aclrtGetDeviceCount) to obtain the number of available devices, the value range of this device ID is [0, (number of available devices - 1)]. |
| attr | Input | Attribute. See [aclrtDevAttr](25-02_Enumerations.md#aclrtDevAttr) for the type definition. |
| value | Output | Attribute value. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

<br>
<br>
<br>

<a id="aclrtDeviceGetStreamPriorityRange"></a>

## aclrtDeviceGetStreamPriorityRange

```c
aclError aclrtDeviceGetStreamPriorityRange(int32_t *leastPriority, int32_t *greatestPriority)
```

### Applicable Products

<!-- npu="950" id1989 -->
- Ascend 950PR&950DT products: Supported
<!-- end id1989 -->
<!-- npu="A3" id1990 -->
- Atlas A3 products: Supported
<!-- end id1990 -->
<!-- npu="910b" id1991 -->
- Atlas A2 products: Supported
<!-- end id1991 -->
<!-- npu="310b" id1992 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id1992 -->
<!-- npu="310p" id1993 -->
- Atlas inference products: Supported
<!-- end id1993 -->
<!-- npu="910" id1994 -->
- Atlas training products: Supported
<!-- end id1994 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id22 -->

### Function

Queries the minimum and maximum stream priorities supported by the hardware.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| leastPriority | Output | Minimum priority. |
| greatestPriority | Output | Maximum priority. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

<br>
<br>
<br>

<a id="aclrtGetDeviceCapability"></a>

## aclrtGetDeviceCapability

```c
aclError aclrtGetDeviceCapability(int32_t deviceId, aclrtDevFeatureType devFeatureType, int32_t *value)
```

### Applicable Products

<!-- npu="950" id1079 -->
- Ascend 950PR&950DT products: Supported
<!-- end id1079 -->
<!-- npu="A3" id1080 -->
- Atlas A3 products: Supported
<!-- end id1080 -->
<!-- npu="910b" id1081 -->
- Atlas A2 products: Supported
<!-- end id1081 -->
<!-- npu="310b" id1082 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id1082 -->
<!-- npu="310p" id1083 -->
- Atlas inference products: Supported
<!-- end id1083 -->
<!-- npu="910" id1084 -->
- Atlas training products: Supported
<!-- end id1084 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id23 -->

### Function

Queries the supported feature information.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| deviceId | Input | device ID.<br>After you call [aclrtGetDeviceCount](#aclrtGetDeviceCount) to obtain the number of available devices, the value range of this device ID is [0, (number of available devices - 1)]. |
| devFeatureType | Input | Feature type. For the type definition, see [aclrtDevFeatureType](25-02_Enumerations.md#aclrtDevFeatureType). |
| value | Output | Whether the feature is supported.<br><br>  - ACL_DEV_FEATURE_NOT_SUPPORT(0): Not supported<br>  - ACL_DEV_FEATURE_SUPPORT(1): Supported<br><br><br>The related macro definitions are as follows:<br>#define ACL_DEV_FEATURE_SUPPORT  0x00000001<br>#define ACL_DEV_FEATURE_NOT_SUPPORT 0x00000000 |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

<br>
<br>
<br>

<a id="aclrtGetDevicesTopo"></a>

## aclrtGetDevicesTopo

```c
aclError aclrtGetDevicesTopo(uint32_t deviceId, uint32_t otherDeviceId, uint64_t *value)
```

### Applicable Products

<!-- npu="950" id813 -->
- Ascend 950PR&950DT products: Supported
<!-- end id813 -->
<!-- npu="A3" id814 -->
- Atlas A3 products: Supported
<!-- end id814 -->
<!-- npu="910b" id815 -->
- Atlas A2 products: Supported
<!-- end id815 -->
<!-- npu="310b" id816 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id816 -->
<!-- npu="310p" id817 -->
- Atlas inference products: Supported
<!-- end id817 -->
<!-- npu="910" id818 -->
- Atlas training products: Supported
<!-- end id818 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id24 -->

### Function

Obtains the network topology between two devices.

<!-- npu="310b" id11 -->
This API cannot be called in the Ascend RC mode of Atlas 200I/500 A2 inference products.
<!-- end id11 -->

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| deviceId | Input | ID of the specified device.<br>After you call [aclrtGetDeviceCount](#aclrtGetDeviceCount) to obtain the number of available devices, the value range of this device ID is [0, (number of available devices - 1)]. |
| otherDeviceId | Input | ID of the specified device.<br>After you call [aclrtGetDeviceCount](#aclrtGetDeviceCount) to obtain the number of available devices, the value range of this device ID is [0, (number of available devices - 1)]. |
| value | Output | Topology relationship between the two devices.<br><br>  - ACL_RT_DEVS_TOPOLOGY_HCCS: Connected through HCCS. HCCS (Huawei Cache Coherence System) is used for high-speed interconnection between CPUs and NPUs.<br>  - ACL_RT_DEVS_TOPOLOGY_PIX: Connected through the same PCIe Switch.<br>  - ACL_RT_DEVS_TOPOLOGY_PHB: Connected through a PCIe Host Bridge.<br>  - ACL_RT_DEVS_TOPOLOGY_SYS: Connected through SMP (Symmetric Multiprocessing). NUMA nodes are interconnected through SMP.<br>  - ACL_RT_DEVS_TOPOLOGY_SIO: On-chip interconnection, through which two dies are connected.<br>  - ACL_RT_DEVS_TOPOLOGY_HCCS_SW: Connected through an HCCS Switch.<br>  - ACL_RT_DEVS_TOPOLOGY_PIB: Reserved value, not supported yet.<br><br>The macro definitions are as follows:<br>#define ACL_RT_DEVS_TOPOLOGY_HCCS  0x01ULL<br>#define ACL_RT_DEVS_TOPOLOGY_PIX  0x02ULL<br>#define ACL_RT_DEVS_TOPOLOGY_PHB  0x08ULL<br>#define ACL_RT_DEVS_TOPOLOGY_SYS  0x10ULL<br>#define ACL_RT_DEVS_TOPOLOGY_SIO  0x20ULL<br>#define ACL_RT_DEVS_TOPOLOGY_HCCS_SW  0x40ULL<br>#define ACL_RT_DEVS_TOPOLOGY_PIB  0x04ULL |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

<br>
<br>
<br>

<a id="aclrtRegDeviceStateCallback"></a>

## aclrtRegDeviceStateCallback

```c
aclError aclrtRegDeviceStateCallback(const char *regName, aclrtDeviceStateCallback callback, void *args)
```

### Applicable Products

<!-- npu="950" id2633 -->
- Ascend 950PR&950DT products: Supported
<!-- end id2633 -->
<!-- npu="A3" id2634 -->
- Atlas A3 products: Supported
<!-- end id2634 -->
<!-- npu="910b" id2635 -->
- Atlas A2 products: Supported
<!-- end id2635 -->
<!-- npu="310b" id2636 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id2636 -->
<!-- npu="310p" id2637 -->
- Atlas inference products: Supported
<!-- end id2637 -->
<!-- npu="910" id2638 -->
- Atlas training products: Supported
<!-- end id2638 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id25 -->

### Function

Registers a callback function for device state changes. Duplicate registration is not supported.

When the device state changes (for example, when APIs such as [aclrtSetDevice](#aclrtSetDevice) and [aclrtResetDevice](#aclrtResetDevice) are called), the Runtime module triggers the callback function.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| regName | Input | Registration name, which must be unique and cannot be empty. The input string must end with \0. |
| callback | Input | Callback function. If callback is not NULL, the callback function is registered; if it is NULL, the callback function is unregistered.<br>The prototype of the callback function is as follows:<br>typedef enum {<br>   ACL_RT_DEVICE_STATE_SET_PRE = 0, // Before calling a set API (for example, aclrtSetDevice)<br>   ACL_RT_DEVICE_STATE_SET_POST,  // After calling a set API (for example, aclrtSetDevice)<br>   ACL_RT_DEVICE_STATE_RESET_PRE,  // Before calling a reset API (for example, aclrtResetDevice)<br>   ACL_RT_DEVICE_STATE_RESET_POST, // After calling a reset API (for example, aclrtResetDevice)<br>} aclrtDeviceState;<br>typedef void (*aclrtDeviceStateCallback)(uint32_t devId, aclrtDeviceState state, void* args); |
| args | Input | Pointer to the user data to be passed to the callback function. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

<br>
<br>
<br>

<a id="aclrtGetLogicDevIdByUserDevId"></a>

## aclrtGetLogicDevIdByUserDevId

```c
aclError aclrtGetLogicDevIdByUserDevId(const int32_t userDevid, int32_t *const logicDevId)
```

### Applicable Products

<!-- npu="950" id456 -->
- Ascend 950PR&950DT products: Supported
<!-- end id456 -->
<!-- npu="A3" id457 -->
- Atlas A3 products: Supported
<!-- end id457 -->
<!-- npu="910b" id458 -->
- Atlas A2 products: Supported
<!-- end id458 -->
<!-- npu="310b" id459 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id459 -->
<!-- npu="310p" id460 -->
- Atlas inference products: Supported
<!-- end id460 -->
<!-- npu="910" id461 -->
- Atlas training products: Supported
<!-- end id461 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id26 -->

### Function

Obtains the logical device ID based on the user device ID.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| userDevid | Input | User device ID. |
| logicDevId | Output | Logical device ID. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

### Relationships Between the User Device ID, Logical Device ID, and Physical Device ID

If the `ASCEND\_RT\_VISIBLE\_DEVICES` environment variable is not set, the logical device ID is the same as the user device ID. In non-container scenarios, the physical device ID is the same as the logical device ID.

The following figure uses a container scenario with the ASCEND\_RT\_VISIBLE\_DEVICES environment variable set as an example to illustrate the relationship among the three: the device IDs set through the ASCEND\_RT\_VISIBLE\_DEVICES environment variable are **1** and 2, and the corresponding device index values are **0** and 1. The user device ID set through the [aclrtSetDevice](#aclrtSetDevice) API is **0**, that is, the corresponding device index value is **0**. Therefore, User Device ID = **0** corresponds to Logical Device ID = **1**, and Logical Device ID = **1** in the container is mapped to Physical Device ID = **6**. As a result, the physical device with ID 6 is ultimately used for computation.

![](figures/UserDevId_LogicDevId_PhyDevId.png)

For details about the ASCEND\_RT\_VISIBLE\_DEVICES environment, see [*Environment Variables*](../env_vars/ASCEND_RT_VISIBLE_DEVICES.md).

<br>
<br>
<br>

<a id="aclrtGetUserDevIdByLogicDevId"></a>

## aclrtGetUserDevIdByLogicDevId

```c
aclError aclrtGetUserDevIdByLogicDevId(const int32_t logicDevId, int32_t *const userDevid)
```

### Applicable Products

<!-- npu="950" id1702 -->
- Ascend 950PR&950DT products: Supported
<!-- end id1702 -->
<!-- npu="A3" id1703 -->
- Atlas A3 products: Supported
<!-- end id1703 -->
<!-- npu="910b" id1704 -->
- Atlas A2 products: Supported
<!-- end id1704 -->
<!-- npu="310b" id1705 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id1705 -->
<!-- npu="310p" id1706 -->
- Atlas inference products: Supported
<!-- end id1706 -->
<!-- npu="910" id1707 -->
- Atlas training products: Supported
<!-- end id1707 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id27 -->

### Function

Obtains the user device ID based on the logical device ID.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| logicDevId | Input | Logical device ID. |
| userDevid | Output | User device ID. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

### Relationships Between the User Device ID, Logical Device ID, and Physical Device ID

If the `ASCEND\_RT\_VISIBLE\_DEVICES` environment variable is not set, the logical device ID is the same as the user device ID. In non-container scenarios, the physical device ID is the same as the logical device ID.

The following figure uses a container scenario with the ASCEND\_RT\_VISIBLE\_DEVICES environment variable set as an example to illustrate the relationship among the three: the device IDs set through the ASCEND\_RT\_VISIBLE\_DEVICES environment variable are **1** and 2, and the corresponding device index values are **0** and 1. The user device ID set through the [aclrtSetDevice](#aclrtSetDevice) API is **0**, that is, the corresponding device index value is **0**. Therefore, User Device ID = **0** corresponds to Logical Device ID = **1**, and Logical Device ID = **1** in the container is mapped to Physical Device ID = **6**. As a result, the physical device with ID 6 is ultimately used for computation.

![](figures/UserDevId_LogicDevId_PhyDevId.png)

For details about the ASCEND\_RT\_VISIBLE\_DEVICES environment, see [*Environment Variables*](../env_vars/ASCEND_RT_VISIBLE_DEVICES.md).

<br>
<br>
<br>

<a id="aclrtGetLogicDevIdByPhyDevId"></a>

## aclrtGetLogicDevIdByPhyDevId

```c
aclError aclrtGetLogicDevIdByPhyDevId(const int32_t phyDevId, int32_t *const logicDevId)
```

### Applicable Products

<!-- npu="950" id1296 -->
- Ascend 950PR&950DT products: Supported
<!-- end id1296 -->
<!-- npu="A3" id1297 -->
- Atlas A3 products: Supported
<!-- end id1297 -->
<!-- npu="910b" id1298 -->
- Atlas A2 products: Supported
<!-- end id1298 -->
<!-- npu="310b" id1299 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id1299 -->
<!-- npu="310p" id1300 -->
- Atlas inference products: Supported
<!-- end id1300 -->
<!-- npu="910" id1301 -->
- Atlas training products: Supported
<!-- end id1301 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id28 -->

### Function

Obtains the logical device ID based on the physical device ID.

**Note: The semantics of the logical device ID in this API are described incorrectly; it actually corresponds to the user device ID. To fix this issue, Runtime provides the [aclrtGetUserDevIdByPhyDevId](#aclrtGetUserDevIdByPhyDevId) API as a replacement.**

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| phyDevId | Input | Physical device ID. |
| logicDevId | Output | Logical device ID (the parameter is actually userDevId). |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

### Relationships Between the User Device ID, Logical Device ID, and Physical Device ID

If the `ASCEND\_RT\_VISIBLE\_DEVICES` environment variable is not set, the logical device ID is the same as the user device ID. In non-container scenarios, the physical device ID is the same as the logical device ID.

The following figure uses a container scenario with the ASCEND\_RT\_VISIBLE\_DEVICES environment variable set as an example to illustrate the relationship among the three: the device IDs set through the ASCEND\_RT\_VISIBLE\_DEVICES environment variable are **1** and 2, and the corresponding device index values are **0** and 1. The user device ID set through the [aclrtSetDevice](#aclrtSetDevice) API is **0**, that is, the corresponding device index value is **0**. Therefore, User Device ID = **0** corresponds to Logical Device ID = **1**, and Logical Device ID = **1** in the container is mapped to Physical Device ID = **6**. As a result, the physical device with ID 6 is ultimately used for computation.

![](figures/UserDevId_LogicDevId_PhyDevId.png)

For details about the ASCEND\_RT\_VISIBLE\_DEVICES environment, see [*Environment Variables*](../env_vars/ASCEND_RT_VISIBLE_DEVICES.md).

<br>
<br>
<br>

<a id="aclrtGetPhyDevIdByLogicDevId"></a>

## aclrtGetPhyDevIdByLogicDevId

```c
aclError aclrtGetPhyDevIdByLogicDevId(const int32_t logicDevId, int32_t *const phyDevId)
```

### Applicable Products

<!-- npu="950" id2255 -->
- Ascend 950PR&950DT products: Supported
<!-- end id2255 -->
<!-- npu="A3" id2256 -->
- Atlas A3 products: Supported
<!-- end id2256 -->
<!-- npu="910b" id2257 -->
- Atlas A2 products: Supported
<!-- end id2257 -->
<!-- npu="310b" id2258 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id2258 -->
<!-- npu="310p" id2259 -->
- Atlas inference products: Supported
<!-- end id2259 -->
<!-- npu="910" id2260 -->
- Atlas training products: Supported
<!-- end id2260 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id29 -->

### Function

Obtains the physical device ID based on the logical device ID.

**Note: The semantics of the logical device ID in this API are described incorrectly; it actually corresponds to the user device ID. To fix this issue, Runtime provides the [aclrtGetPhyDevIdByUserDevId](#aclrtGetPhyDevIdByUserDevId) API as a replacement.**

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| logicDevId | Input | Logical device ID (the parameter is actually userDevId). |
| phyDevId | Output | Physical device ID. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

### Relationships Between the User Device ID, Logical Device ID, and Physical Device ID

If the `ASCEND\_RT\_VISIBLE\_DEVICES` environment variable is not set, the logical device ID is the same as the user device ID. In non-container scenarios, the physical device ID is the same as the logical device ID.

The following figure uses a container scenario with the ASCEND\_RT\_VISIBLE\_DEVICES environment variable set as an example to illustrate the relationship among the three: the device IDs set through the ASCEND\_RT\_VISIBLE\_DEVICES environment variable are **1** and 2, and the corresponding device index values are **0** and 1. The user device ID set through the [aclrtSetDevice](#aclrtSetDevice) API is **0**, that is, the corresponding device index value is **0**. Therefore, User Device ID = **0** corresponds to Logical Device ID = **1**, and Logical Device ID = **1** in the container is mapped to Physical Device ID = **6**. As a result, the physical device with ID 6 is ultimately used for computation.

![](figures/UserDevId_LogicDevId_PhyDevId.png)

For details about the ASCEND\_RT\_VISIBLE\_DEVICES environment, see [*Environment Variables*](../env_vars/ASCEND_RT_VISIBLE_DEVICES.md).

<br>
<br>
<br>

<a id="aclrtGetUserDevIdByPhyDevId"></a>

## aclrtGetUserDevIdByPhyDevId

```c
aclError aclrtGetUserDevIdByPhyDevId(const int32_t phyDevId, int32_t *const userDevId)
```

### Applicable Products

<!-- npu="950" id3326 -->
- Ascend 950PR&950DT products: Supported
<!-- end id3326 -->
<!-- npu="A3" id3327 -->
- Atlas A3 products: Supported
<!-- end id3327 -->
<!-- npu="910b" id3328 -->
- Atlas A2 products: Supported
<!-- end id3328 -->
<!-- npu="310b" id3329 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id3329 -->
<!-- npu="310p" id3330 -->
- Atlas inference products: Supported
<!-- end id3330 -->
<!-- npu="910" id3331 -->
- Atlas training products: Supported
<!-- end id3331 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id30 -->

### Function

Obtains the user device ID based on the physical device ID.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| phyDevId | Input | Physical device ID. |
| userDevId | Output | User device ID. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

### Relationships Between the User Device ID, Logical Device ID, and Physical Device ID

If the `ASCEND\_RT\_VISIBLE\_DEVICES` environment variable is not set, the logical device ID is the same as the user device ID. In non-container scenarios, the physical device ID is the same as the logical device ID.

The following figure uses a container scenario with the ASCEND\_RT\_VISIBLE\_DEVICES environment variable set as an example to illustrate the relationship among the three: the device IDs set through the ASCEND\_RT\_VISIBLE\_DEVICES environment variable are **1** and 2, and the corresponding device index values are **0** and 1. The user device ID set through the [aclrtSetDevice](#aclrtSetDevice) API is **0**, that is, the corresponding device index value is **0**. Therefore, User Device ID = **0** corresponds to Logical Device ID = **1**, and Logical Device ID = **1** in the container is mapped to Physical Device ID = **6**. As a result, the physical device with ID 6 is ultimately used for computation.

![](figures/UserDevId_LogicDevId_PhyDevId.png)

For details about the ASCEND\_RT\_VISIBLE\_DEVICES environment, see [*Environment Variables*](../env_vars/ASCEND_RT_VISIBLE_DEVICES.md).

<br>
<br>
<br>

<a id="aclrtGetPhyDevIdByUserDevId"></a>

## aclrtGetPhyDevIdByUserDevId

```c
aclError aclrtGetPhyDevIdByUserDevId(const int32_t userDevId, int32_t *const phyDevId)
```

### Applicable Products

<!-- npu="950" id575 -->
- Ascend 950PR&950DT products: Supported
<!-- end id575 -->
<!-- npu="A3" id576 -->
- Atlas A3 products: Supported
<!-- end id576 -->
<!-- npu="910b" id577 -->
- Atlas A2 products: Supported
<!-- end id577 -->
<!-- npu="310b" id578 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id578 -->
<!-- npu="310p" id579 -->
- Atlas inference products: Supported
<!-- end id579 -->
<!-- npu="910" id580 -->
- Atlas training products: Supported
<!-- end id580 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id31 -->

### Function

Obtains the physical device ID based on the user device ID.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| userDevId | Input | User device ID. |
| phyDevId | Output | Physical device ID. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

### Relationships Between the User Device ID, Logical Device ID, and Physical Device ID

If the `ASCEND\_RT\_VISIBLE\_DEVICES` environment variable is not set, the logical device ID is the same as the user device ID. In non-container scenarios, the physical device ID is the same as the logical device ID.

The following figure uses a container scenario with the ASCEND\_RT\_VISIBLE\_DEVICES environment variable set as an example to illustrate the relationship among the three: the device IDs set through the ASCEND\_RT\_VISIBLE\_DEVICES environment variable are **1** and 2, and the corresponding device index values are **0** and 1. The user device ID set through the [aclrtSetDevice](#aclrtSetDevice) API is **0**, that is, the corresponding device index value is **0**. Therefore, User Device ID = **0** corresponds to Logical Device ID = **1**, and Logical Device ID = **1** in the container is mapped to Physical Device ID = **6**. As a result, the physical device with ID 6 is ultimately used for computation.

![](figures/UserDevId_LogicDevId_PhyDevId.png)

For details about the ASCEND\_RT\_VISIBLE\_DEVICES environment, see [*Environment Variables*]().

<br>
<br>
<br>

<a id="aclrtDeviceGetUuid"></a>

## aclrtDeviceGetUuid

```c
aclError aclrtDeviceGetUuid(int32_t deviceId, aclrtUuid *uuid)
```

### Applicable Products

<!-- npu="950" id2654 -->
- Ascend 950PR&950DT products: Supported
<!-- end id2654 -->
<!-- npu="A3" id2655 -->
- Atlas A3 products: Supported
<!-- end id2655 -->
<!-- npu="910b" id2656 -->
- Atlas A2 products: Supported
<!-- end id2656 -->
<!-- npu="310b" id2657 -->
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id2657 -->
<!-- npu="310p" id2658 -->
- Atlas inference products: Not supported
<!-- end id2658 -->
<!-- npu="910" id2659 -->
- Atlas training products: Not supported
<!-- end id2659 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id32 -->

### Function

Obtains the universally unique identifier (UUID) of a device.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| deviceId | Input | Device ID, which must be consistent with the device ID in the [aclrtSetDevice](#aclrtSetDevice) API. |
| uuid | Output | Unique identifier of the device. See [aclrtUuid](25-04_Structs.md#aclrtUuid) for the type definition. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

<br>
<br>
<br>

<a id="aclrtDeviceGetPCIBusId"></a>

## aclrtDeviceGetPCIBusId

```c
aclError aclrtDeviceGetPCIBusId(int32_t deviceId, char *pciBusId, int32_t len)
```

### Applicable Products

<!-- npu="950" id3333 -->
- Ascend 950PR&950DT products: Supported
<!-- end id3333 -->
<!-- npu="A3" id3334 -->
- Atlas A3 products: Supported
<!-- end id3334 -->
<!-- npu="910b" id3335 -->
- Atlas A2 products: Supported
<!-- end id3335 -->
<!-- npu="310b" id3336 -->
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id3336 -->
<!-- npu="310p" id3337 -->
- Atlas inference products: Not supported
<!-- end id3337 -->
<!-- npu="910" id3338 -->
- Atlas training products: Not supported
<!-- end id3338 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id36 -->

### Function

Obtains the PCI bus ID of the device corresponding to the device ID. The PCI bus ID is in the format `domain:bus:device.function`, for example, `0000:3d:00.0`.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| deviceId | Input | Device ID, which must be consistent with the device ID in the [aclrtSetDevice](#aclrtSetDevice) API. |
| pciBusId | Output | Pointer to the buffer used to store the PCI bus ID. |
| len | Input | Buffer length, which must be greater than or equal to 13. The PCI bus ID consists of 12 characters plus the trailing `\0`, totaling 13 bytes. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

### Constraints

- In virtual machine or container scenarios, the returned value is the virtual PCI Bus ID allocated by the virtualization layer. It is only guaranteed to be valid in format and unique within the current virtual machine or container, and is not guaranteed to be consistent with the physical machine or unique across virtual machines.
- For devices using non-PCIe interconnect topologies (such as Huawei Cache Coherence System and Unified Bus), this API returns `ACL_ERROR_RT_FEATURE_NOT_SUPPORT`.

<br>
<br>
<br>

<a id="aclrtDeviceGetByPCIBusId"></a>

## aclrtDeviceGetByPCIBusId

```c
aclError aclrtDeviceGetByPCIBusId(const char *pciBusId, int32_t *deviceId)
```

### Applicable Products

<!-- npu="950" id3340 -->
- Ascend 950PR&950DT products: Supported
<!-- end id3340 -->
<!-- npu="A3" id3341 -->
- Atlas A3 products: Supported
<!-- end id3341 -->
<!-- npu="910b" id3342 -->
- Atlas A2 products: Supported
<!-- end id3342 -->
<!-- npu="310b" id3343 -->
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id3343 -->
<!-- npu="310p" id3344 -->
- Atlas inference products: Not supported
<!-- end id3344 -->
<!-- npu="910" id3345 -->
- Atlas training products: Not supported
<!-- end id3345 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id37 -->

### Function

Obtains the corresponding device ID based on a PCI bus ID. The PCI bus ID is in the format `domain:bus:device.function`, for example, `0000:3d:00.0`.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| pciBusId | Input | PCI bus ID in the format `domain:bus:device.function`. |
| deviceId | Output | Device ID, which must be consistent with the device ID in the [aclrtSetDevice](#aclrtSetDevice) API. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

### Constraints

- For devices using non-PCIe interconnect topologies (such as Huawei Cache Coherence System and Unified Bus), this API returns `ACL_ERROR_RT_FEATURE_NOT_SUPPORT`.

<br>
<br>
<br>

<a id="aclrtDeviceGetBareTgid"></a>

## aclrtDeviceGetBareTgid

```c
aclError aclrtDeviceGetBareTgid(int32_t *pid)
```

### Applicable Products

<!-- npu="950" id855 -->
- Ascend 950PR&950DT products: Supported
<!-- end id855 -->
<!-- npu="A3" id856 -->
- Atlas A3 products: Supported
<!-- end id856 -->
<!-- npu="910b" id857 -->
- Atlas A2 products: Supported
<!-- end id857 -->
<!-- npu="310b" id858 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id858 -->
<!-- npu="310p" id859 -->
- Atlas inference products: Supported
<!-- end id859 -->
<!-- npu="910" id860 -->
- Atlas training products: Supported
<!-- end id860 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id33 -->

### Function

Obtains the ID of the current process.

Internally, this API has been adapted to both physical machine and virtual machine scenarios when obtaining the process ID. You only need to call this API to obtain the process ID and then configure other APIs to use it (for the workflow, see [aclrtMemExportToShareableHandle](11-04_virtual_memory_management.md#aclrtMemExportToShareableHandle)) to achieve physical memory sharing. If you do not call this API and obtain the process ID on your own, subsequent use of the process ID may be abnormal.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| pid | Output | Process ID. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

<br>
<br>
<br>

<a id="aclrtDeviceGetHostAtomicCapabilities"></a>

## aclrtDeviceGetHostAtomicCapabilities

```c
aclError aclrtDeviceGetHostAtomicCapabilities(uint32_t* capabilities, const aclrtAtomicOperation* operations, const uint32_t count, int32_t deviceId)
```

### Applicable Products

<!-- npu="950" id2262 -->
- Ascend 950PR&950DT products: Supported
<!-- end id2262 -->
<!-- npu="A3" id2263 -->
- Atlas A3 products: Supported
<!-- end id2263 -->
<!-- npu="910b" id2264 -->
- Atlas A2 products: Supported
<!-- end id2264 -->
<!-- npu="310b" id2265 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id2265 -->
<!-- npu="310p" id2266 -->
- Atlas inference products: Supported
<!-- end id2266 -->
<!-- npu="910" id2267 -->
- Atlas training products: Supported
<!-- end id2267 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id34 -->

### Function

Queries the details of the atomic operations supported between a specified device and the host.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| capabilities | Output | Array of atomic operation capability masks, with the same length as the count parameter. Each element in the array is a bit mask, where each bit indicates whether the atomic operation is supported for a specific data type: 1 indicates supported, and 0 indicates not supported. See [aclrtAtomicOperationCapability](25-02_Enumerations.md#aclrtAtomicOperationCapability) for the type definition. |
| operations | Input | Array of atomic operations to query, with the same length as the count parameter. See [aclrtAtomicOperation](25-02_Enumerations.md#aclrtAtomicOperation) for the type definition. |
| count | Input | Number of atomic operations to query. Its value must match the length of the capabilities and operations arrays; otherwise, undefined behavior may occur. |
| deviceId | Input | Device ID.<br>After you call [aclrtGetDeviceCount](#aclrtGetDeviceCount) to obtain the number of available devices, the value range of this device ID is [0, (number of available devices - 1)]. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

<br>
<br>
<br>

<a id="aclrtDeviceGetP2PAtomicCapabilities"></a>

## aclrtDeviceGetP2PAtomicCapabilities

```c
aclError aclrtDeviceGetP2PAtomicCapabilities(uint32_t* capabilities, const aclrtAtomicOperation* operations, const uint32_t count, int32_t srcDeviceId, int32_t dstDeviceId)
```

### Applicable Products

<!-- npu="950" id1968 -->
- Ascend 950PR&950DT products: Supported
<!-- end id1968 -->
<!-- npu="A3" id1969 -->
- Atlas A3 products: Supported
<!-- end id1969 -->
<!-- npu="910b" id1970 -->
- Atlas A2 products: Supported
<!-- end id1970 -->
<!-- npu="310b" id1971 -->
- Atlas 200I/500 A2 inference products: Supported
<!-- end id1971 -->
<!-- npu="310p" id1972 -->
- Atlas inference products: Supported
<!-- end id1972 -->
<!-- npu="910" id1973 -->
- Atlas training products: Supported
<!-- end id1973 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id35 -->

### Function

Queries the details of atomic operations supported between two devices in an AI Server. An AI Server is a general term for a server form that typically consists of multiple devices.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| capabilities | Output | Array of atomic operation capability masks, with the same length as the count parameter. Each element in the array is a bit mask, where each bit indicates whether the atomic operation is supported for a specific data type: 1 indicates supported, and 0 indicates not supported. See [aclrtAtomicOperationCapability](25-02_Enumerations.md#aclrtAtomicOperationCapability) for the type definition. |
| operations | Input | Array of atomic operations to query, with the same length as the count parameter. See [aclrtAtomicOperation](25-02_Enumerations.md#aclrtAtomicOperation) for the type definition. |
| count | Input | Number of atomic operations to query. Its value must match the length of the capabilities and operations arrays; otherwise, undefined behavior may occur. |
| srcDeviceId | Input | Device ID.<br>After you call [aclrtGetDeviceCount](#aclrtGetDeviceCount) to obtain the number of available devices, the value range of this device ID is [0, (number of available devices - 1)]. |
| dstDeviceId | Input | Device ID.<br>After you call [aclrtGetDeviceCount](#aclrtGetDeviceCount) to obtain the number of available devices, the value range of this device ID is [0, (number of available devices - 1)]. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

<a id="aclrtDeviceSetLimit"></a>

## aclrtDeviceSetLimit

```c
aclError aclrtDeviceSetLimit(aclrtDeviceLimit limit, size_t value)
```

### Applicable Products

<!-- npu="950" id3260 -->
- Ascend 950PR&950DT products: Supported
<!-- end id3260 -->
<!-- npu="A3" id3261 -->
- Atlas A3 products: Supported
<!-- end id3261 -->
<!-- npu="910b" id3262 -->
- Atlas A2 products: Supported
<!-- end id3262 -->
<!-- npu="310b" id3266 -->
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id3266 -->
<!-- npu="310p" id3267 -->
- Atlas inference products: Not supported
<!-- end id3267 -->
<!-- npu="910" id3268 -->
- Atlas training products: Not supported
<!-- end id3268 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id38 -->

### Function

Sets the device resource limit of the current process, such as the Single Instruction Multiple Thread (SIMT) operator stack size and SIMT Printf buffer size.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| limit | Input | Resource type. For details, see the [aclrtDeviceLimit](25-02_Enumerations.md#aclrtDeviceLimit) enumeration. |
| value | Input | Resource limit size, in bytes. The value of this parameter depends on the limit type. For details, see the [aclrtDeviceLimit](25-02_Enumerations.md#aclrtDeviceLimit) enumeration. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

### Constraints

- Different product models support different limit resource types. For unsupported resource types, the API returns `ACL_ERROR_RT_FEATURE_NOT_SUPPORT`.
- It is recommended that you call this API after `aclInit` and before `aclrtSetDevice` to ensure that the resource limit configuration takes effect.
- If `aclrtSetDevice` is called multiple times, note that `aclrtSetDevice` and `aclrtResetDevice` internally involve reference counting and must be used in pairs. After the reference count drops to 0, call this API to configure the resource limit, and then call `aclrtSetDevice` again for the configuration to take effect. The call sequence is as follows:

  `aclInit`-->`aclrtDeviceSetLimit` (first call to set the limit)-->`aclrtSetDevice` (the resource limit configuration takes effect)-->service processing-->`aclrtResetDevice` (reset device resources)-->`aclrtDeviceSetLimit` (second call to set the limit)-->`aclrtSetDevice` (the resource limit configuration takes effect)

- You can use either this API or `aclInit` to configure resource limits, such as the SIMT operator stack size and SIMT Printf buffer size. Using this API is more flexible and convenient for adjusting resource limits. If the resource limit is configured using both methods, the later configuration will overwrite the previous one.
- The device resource limit configured using this API applies to the current process. All devices share the same configuration, and different resource limits cannot be set for different devices.
- This API internally uses Device0 for configuration. If the `ASCEND_RT_VISIBLE_DEVICES` environment variable is set and does not include Device0, configuring resource limits through this API or `aclInit` will fail. Therefore, if you use the `ASCEND_RT_VISIBLE_DEVICES` environment variable, ensure that its value includes Device0.

<br>
<br>
<br>

<a id="aclrtDeviceGetLimit"></a>

## aclrtDeviceGetLimit

```c
aclError aclrtDeviceGetLimit(aclrtDeviceLimit limit, size_t *value)
```

### Applicable Products

<!-- npu="950" id3263 -->
- Ascend 950PR&950DT products: Supported
<!-- end id3263 -->
<!-- npu="A3" id3264 -->
- Atlas A3 products: Supported
<!-- end id3264 -->
<!-- npu="910b" id3265 -->
- Atlas A2 products: Supported
<!-- end id3265 -->
<!-- npu="310b" id3272 -->
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id3272 -->
<!-- npu="310p" id3273 -->
- Atlas inference products: Not supported
<!-- end id3273 -->
<!-- npu="910" id3274 -->
- Atlas training products: Not supported
<!-- end id3274 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id39 -->

### Function

Obtains the device resource limits of the current process.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| limit | Input | Resource type. For details, see the [aclrtDeviceLimit](25-02_Enumerations.md#aclrtDeviceLimit) enumeration. |
| value | Output | Resource limit size, in bytes. It cannot be nullptr. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

### Constraints

- The device resource limits configured through the `aclrtDeviceSetLimit` API apply to the current process. All devices share the same configuration, and querying on any device returns the same value.
- This API returns the instantaneous value of the current process and does not guarantee thread safety under concurrent access by multiple threads.
- For example: first call `aclrtDeviceSetLimit` to set the stack size to A, and then call `aclrtSetDevice` to make it take effect. At this point, querying through the `aclrtDeviceGetLimit` API returns A, and the actual resource limit is also A. Then call `aclrtDeviceSetLimit` again to change it to B, but do not call `aclrtSetDevice` again. At this point, querying through the `aclrtDeviceGetLimit` API returns B, while the actual resource limit remains A.

<!-- npu="A3,910b" id3276 -->
- For Atlas A3 products and Atlas A2 products, querying `ACL_RT_DEV_LIMIT_SIMT_STACK_SIZE`, `ACL_RT_DEV_LIMIT_SIMT_DVG_WARP_STACK_SIZE`, or `ACL_RT_DEV_LIMIT_SIMT_PRINTF_FIFO_SIZE` returns `ACL_ERROR_RT_FEATURE_NOT_SUPPORT`.
<!-- end id3276 -->

<!-- npu="950" id3277 -->
- For Ascend 950PR&950DT products, querying `ACL_RT_DEV_LIMIT_SIMT_STACK_SIZE` returns the aligned value multiplied by 32 (the number of threads per warp). For example, if 256 is set, the query returns 8192. Querying `ACL_RT_DEV_LIMIT_SIMT_DVG_WARP_STACK_SIZE` returns the aligned value (without multiplying by the number of threads). For example, if 512 is set, the query returns 512.
<!-- end id3277 -->

<br>
<br>
<br>

<a id="aclrtDeviceL2CacheFlush"></a>

## aclrtDeviceL2CacheFlush

```c
aclError aclrtDeviceL2CacheFlush(void* rsv)
```

### Applicable Products

<!-- npu="950" id3300 -->
- Ascend 950PR&950DT products: Supported
<!-- end id3300 -->
<!-- npu="A3" id3301 -->
- Atlas A3 products: Not supported
<!-- end id3301 -->
<!-- npu="910b" id3302 -->
- Atlas A2 products: Not supported
<!-- end id3302 -->
<!-- npu="310b" id3303 -->
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id3303 -->
<!-- npu="310p" id3304 -->
- Atlas inference products: Not supported
<!-- end id3304 -->
<!-- npu="910" id3305 -->
- Atlas training products: Not supported
<!-- end id3305 -->
<!-- @ref: runtime/res/docs/zh/api_ref/04_device_management_res.md#id40 -->

### Function

Flushes the L2 cache of the current device. The API returns only after the L2 cache flush is complete.

The current device is specified by the [aclrtSetDevice](#aclrtSetDevice) API.

### Parameters

| Parameter | Input/Output | Description |
| --- | :---: | --- |
| rsv | Input | Reserved parameter. nullptr must be passed. |

### Return Values

0: success; others: failure. For details, see [aclError](25-01_aclError.md#aclError).

### Constraints

- This API is not supported in Ascend virtual instance scenarios.
- Calling this API at a high frequency is not recommended, as frequent calls may affect service performance.
- If concurrent services are running on the device during the flush, the L2 cache may be occupied again, making this flush operation ineffective.
