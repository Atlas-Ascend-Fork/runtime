# Function: bundle\_get\_model\_num

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

Obtains the number of executable models based on `bundle_id`.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlBundleGetModelNum(uint32_t bundleId, size_t modelNum)
    ```

- **Python Function**

    ```python
    model_num, ret = acl.mdl.bundle_get_model_num(bundle_id)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| bundle_id | Int, `bundle_id` returned after the model is successfully loaded through the [acl.mdl.bundle\_load\_from\_file](function-bundle_load_from_file.md) API or the [acl.mdl.bundle_load_from_mem](function-bundle_load_from_mem.md) API.|

## Return Values

| Return Value| Description|
| --- | --- |
| model_num | Int, number of executable models.|
| ret | Int, error code: `0` on success; [else](aclError.md), failure.|
