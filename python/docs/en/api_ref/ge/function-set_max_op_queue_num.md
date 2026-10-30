# Function: set\_max\_op\_queue\_num

## Applicable Products

<!-- npu="950" id1 -->
- Ascend 950PR&950DT products: Not supported
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

Configures the operator cache aging information to save memory and balance calling performance when a single operator is executed using a single-operator model.

## Prototype

- **C Prototype**

    ```c
    aclError aclopSetMaxOpQueueNum(uint64_t maxOpNum)
    ```

- **Python Function**

    ```python
    ret = acl.op.set_max_op_queue_num(max_op_num)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| max_op_num | Int, maximum length of the "operator type-single-operator model" mapping queue. If the length reaches the maximum, the mapping information that is not used for a long time and the single-operator model in the cache are deleted. Then, the latest mapping information and the corresponding single-operator model are loaded. When a single-operator is executed in single-operator model mode (except when executed by calling `aclopUpdateParams`), if this API is not called to configure the maximum length of the mapping queue, the default maximum length is `20000`. When `aclopUpdateParams` is called to execute a single operator, if this API is not called to configure the maximum length of the mapping queue, the operator cache information does not need to be aged.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|
