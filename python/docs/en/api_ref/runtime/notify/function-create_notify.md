# Function: create\_notify

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

Creates a Notify object.

## Prototype

- **C Prototype**

    ```c
    aclError aclrtCreateNotify(aclrtNotify *notify, uint64_t flag)
    ```

- **Python Function**

    ```python
    notify, ret = acl.rt.create_notify(flag)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| flag | Int, reserved parameter. The value is fixed at `0`.|

## Return Values

| Return Value| Description|
| --- | --- |
| notify | Int, pointer address of Notify.|
| ret | Int. If 0 is returned, the operation is successful. If other values are returned, the operation fails.|

## Constraints

The number of Notify objects supported varies depending on the hardware model.

<!-- npu="950" id7 -->
- For Ascend 950PR&950DT products, a maximum of 65535 Notify objects are supported per device.
<!-- end id7 -->
<!-- npu="A3,910b" id8 -->
- For Atlas A3 and Atlas A2 products, a maximum of 8192 Notify objects are supported per device.
<!-- end id8 -->
<!-- npu="310b" id9 -->
- For Atlas 200I/500 A2 inference products, a maximum of 2048 Notify objects are supported per device.
<!-- end id9 -->
<!-- npu="910,310p" id10 -->
- For Atlas inference and training products, a maximum of 1024 Notify objects are supported per device.
<!-- end id10 -->
