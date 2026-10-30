# Function: get\_logic\_dev\_id\_by\_user\_dev\_id

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

Obtains the logical device ID based on the user device ID.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtGetLogicDevIdByUserDevId(const int32_t userDevid, int32_t *const logicDevId)
    ```

- **Python Function**

    ```python
    logic_dev_id, ret = acl.rt.get_logic_dev_id_by_user_dev_id(user_dev_id)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| user_dev_id | Int, user device ID.|

## Return Values

| Return Value| Description|
| --- | --- |
| logic_dev_id | Int, logical device ID.|
| ret | Int. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Relationships Between the User Device ID, Logical Device ID, and Physical Device ID

If the `ASCEND\_RT\_VISIBLE\_DEVICES` environment variable is not set, the logical device ID is the same as the user device ID. In non-container scenarios, the physical device ID is the same as the logical device ID.

The following figure uses the container scenario where the `ASCEND\_RT\_VISIBLE\_DEVICES` environment variable is set as an example to describe the relationships between the three IDs. The device IDs set by the `ASCEND\_RT\_VISIBLE\_DEVICES` environment variable are 1** and 2, and the corresponding device indexes are 0 and 1, respectively. The user device ID set by the [acl.rt.set\_device](function-set_device.md) API is 0, which corresponds to the device index 0. Therefore, the user device ID 0 corresponds to the logical device ID 1. The logical device ID 1 in the container is mapped to the physical device ID 6**. As a result, the physical device with ID 6 is used for computation.

Figure 1
![](../figures/deviceid.png)

For details about the `ASCEND\_RT\_VISIBLE\_DEVICES` environment variable, see [Environment Variables](https://hiascend.com/en/document/redirect/CannCommunityEnvRef).
