# Function: set\_tensor\_const

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

Sets a constant input for an operator and specifies the buffer address for storing the input tensor data and address length.

## Prototype

- **C Prototype**

    ```c
    aclError aclSetTensorConst(aclTensorDesc *desc, void *dataBuffer, size_t length)
    ```

- **Python Function**

    ```python
    ret = acl.set_tensor_const(desc, dataBuffer, length)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| desc | Int, pointer address of the `aclTensorDesc` type. Call [acl.create_tensor_desc](function-create_tensor_desc.md) to create data of the `aclTensorDesc` type in advance.|
| dataBuffer | Int, address of the memory for storing the input tensor of the constant. The memory for storing the input tensor data of the operator must be determined based on the application running mode. For details about memory allocation APIs, see [Memory Management](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/API/runtimeapi/aclpythondevg_01_0109.html).<br> If the app runs on the host, allocate the memory of the host.<br> If the app runs on the device, allocate device memory.|
| length | Int, length of the memory address, in bytes.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code.<br> `0`: success<br> [Other values](aclError.md): failure|
