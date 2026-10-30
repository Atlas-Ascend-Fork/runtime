# Function: dump\_reg\_callback

## Applicable Products

<!-- npu="950" id1 -->
- Ascend 950PR&950DT products: Supported
<!-- end id1 -->
<!-- npu="A3" id2 -->
- Atlas A3 products: supported
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

Registers the dump data callback function.

The [function: init_dump](function-init_dump.md), [function: dump_reg_callback](function-dump_reg_callback.md) (the callback function registered through this API needs to be implemented by the user. The implementation logic of the callback function includes obtaining the dump data and data length), [function: dump_unreg_callback](function-dump_unreg_callback.md), and [function: finalize_dump](function-finalize_dump.md) APIs are used together to obtain dump data through the callback function. **The following are some example scenarios:**

- **Execute a model and obtain dump data through callback.**

    Two options are available:

  - **Disable** model and single-operator dump configurations at the aclInit API.

    [Function: init](../init/function-init.md) API --\> [Function: init_dump](function-init_dump.md) API --\> [Function: dump_reg_callback](function-dump_reg_callback.md) API --\> Model Loading --\> model execution --\> [Function: dump_unreg_callback](function-dump_unreg_callback.md) API --\> [Function: finalize_dump](function-finalize_dump.md) API --\> Model Unloading --\> [Function: finalize](../init/function-finalize.md) API

  - **Enable** the model dump configuration and single-operator dump configuration in the aclInit API. When enabling the dump configuration in the aclInit API, you need to configure the dump path. However, if the [function: dump\_reg\_callback](function-dump_reg_callback.md) API is called, the dump path does not take effect, and the dump data obtained by the callback function is used.

    [Function: init](../init/function-init.md) API --\> [Function: dump_reg_callback](function-dump_reg_callback.md) API --\> Model Loading --\> Model Execution --\> [Function: dump_unreg_callback](function-dump_unreg_callback.md) API --\> Model unloading --\> [Function: finalize](../init/function-finalize.md) API

- **Execute two different models and obtain dump data through callback.** In this context, as long as the callback function is not deregistered by calling [Function: dump_unreg_callback](function-dump_unreg_callback.md), you can obtain the dump data of both models through the callback function.

    [Function: init](../init/function-init.md) API --\> [Function: init_dump](function-init_dump.md) API --\> [Function: dump_reg_callback](function-dump_reg_callback.md) API --\> Model 1 Loading --\> Model 1 Execution --\>--\> Model 2 Loading --\> Model 2 Execution --\> [Function: dump_unreg_callback](function-dump_unreg_callback.md) API --\> [Function: finalize_dump](function-finalize_dump.md) API --\> Model Unloading --\> [Function: finalize](../init/function-finalize.md) API

## Prototype

- **C Prototype**

    ```c
    aclError acldumpRegCallback(int32_t (* const messageCallback)(const acldumpChunk *, int32_t), int32_t flag)
    ```

- **Python Function**

    ```python
    ret = acl.mdl.dump_reg_callback(mdl_dump_callback, flag)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| mdl_dump_callback | Callback function used to receive callback data. It has the following parameters:<br>`dump_chunk`: dict. When the `mdl_dump_callback` function is implemented, the values of parameters such as `data_fuf` and `buf_len` in `dump_chunk` can be obtained to obtain the dump data and data length.<br>{<br>"file_name": file_name, // Name of the dump file to be flushed to drives<br>"data_buf": data_buf, // Memory address of the dump data<br>"buf_len": buf_len, // data_buf length, in bytes<br>"is_last_chunk": is_last_chunk, // Indicates whether the dump data is the last fragment. The value 0 indicates that the dump data is not the last fragment, and the value 1 indicates that the dump data is the last fragment.<br>"offset": offset, // Offset of the dump data file content. –1 indicates the content to be added to the file.<br>"flag": flag // Reserved dump data flag. Currently, the data has no flag.<br>} |
| flag | Int, whether to write dump data to a drive after the callback API is called.<br>`0`: no. Currently, only the value `0` is supported.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

None
