# Function: use\_stream\_res\_in\_current\_thread

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

Sets the device resource limits of a specified stream in the current thread. If this API is called multiple times to set the stream, the last setting takes effect.

You need to call [acl.rt.set\_stream\_res\_limit](function-set_stream_res_limit.md) to set the device resource limits of the stream first.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtUseStreamResInCurrentThread(aclrtStream stream)
    ```

- **Python Function**

    ```python
    ret = acl.rt.use_stream_res_in_current_thread(stream)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| stream | Int, specified stream. If `0` is passed, it indicates the default stream.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|
