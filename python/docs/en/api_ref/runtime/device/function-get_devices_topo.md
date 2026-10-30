# Function: get\_devices\_topo

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

>[!NOTE]NOTE
>For Atlas 200I/500 A2 inference products, this API cannot be called in Ascend RC mode.

## Function

Obtains the network topology between two devices.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtGetDevicesTopo(uint32_t deviceId, uint32_t otherDeviceId, uint64_t *value)
    ```

- **Python Function**

    ```python
    value, ret = acl.rt.get_devices_topo(device_id, other_device_id)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| device_id | Int, device ID.|
| other_device_id | Int, device ID.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|
| value | Int, topology of the interconnection between two devices.<br>0x01: ACL_RT_DEVS_TOPOLOGY_HCCS. Connected through the Huawei Cache Coherence System (HCCS), which is used for high-speed interconnection between CPUs and NPUs.<br>`0x02: ACL_RT_DEVS_TOPOLOGY_PIX`: connected through the same PCIe switch.<br>`0x04: ACL_RT_DEVS_TOPOLOGY_PIB`: reserved<br>`0x08: ACL_RT_DEVS_TOPOLOGY_PHB`: connected through the PCIe host bridge.<br>`0x10: ACL_RT_DEVS_TOPOLOGY_SYS`: connected through Symmetric Multiprocessing (SMP). NUMA nodes are interconnected through SMP.<br>`0x20: ACL_RT_DEVS_TOPOLOGY_SIO`: intra-chip connection. Two dies are connected in this mode.<br>`0x40: ACL_RT_DEVS_TOPOLOGY_HCCS_SW`: connected through the HCCS switch.|

## Constraints
<!-- npu="950" id10 -->
For Ascend 950PR&950DT series products, deviceId and otherDeviceId must be different. Otherwise, an error is returned.
<!-- end id10 -->
