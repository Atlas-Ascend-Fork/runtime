# Function: model\_un\_subscribe

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

Unsubscribes from basic operator information, including the operator name, operator type, and operator execution duration, in network scenarios.

## Prototype

- **C Prototype**

    ```c
    aclError aclprofModelUnSubscribe(uint32_t modelId)
    ```

- **Python Function**

    ```python
    ret = acl.prof.model_un_subscribe(model_id)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_id | Int, ID of the model that is subscribed to.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br>`0`: success<br>If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

This API must be used in pair with [acl.prof.model_subscribe](function-model_subscribe.md).
