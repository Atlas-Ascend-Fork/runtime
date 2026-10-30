# Function: set\_aipp\_rbuv\_swap\_switch

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

Sets the RB or UV channel swap switch before CSC in dynamic AIPP scenarios.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlSetAIPPRbuvSwapSwitch(aclmdlAIPP *aippParmsSet, int8_t rbuvSwapSwitch)
    ```

- **Python Function**

    ```python
    ret = acl.mdl.set_aipp_rbuv_swap_switch(aipp_parms_set, rbuv_swap_switch)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| aipp_parms_set | Int, pointer address of the dynamic AIPP configuration object. The `aclmdlAIPP` data must be created by the [acl.mdl.create_aipp](function-create_aipp.md) call in advance.|
| rbuv_swap_switch | Int, RB or UV channel swap switch. Value range: - `0` (default): disabled<br> `1`: enabled|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|
