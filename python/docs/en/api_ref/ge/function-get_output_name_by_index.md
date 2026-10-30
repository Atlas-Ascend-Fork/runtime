# Function: get\_output\_name\_by\_index

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

Obtains the output operator name, operator output edge index, top name, or output name of a model output based on the model description.

## Prototype

- **C Prototype**

    ```c
    const char *aclmdlGetOutputNameByIndex(const aclmdlDesc *modelDesc, size_tindex)
    ```

- **Python Function**

    ```python
    output_name = acl.mdl.get_output_name_by_index(model_desc, index)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| model_desc | Int, pointer address of the data of the `aclmdlDesc` type. Call the [acl.mdl.create_desc](function-create_desc.md) API to create data of the aclmdlDesc type in advance.|
| index | Int, sequence number of the input to obtain, indexed starting at 0|

## Return Values

| Return Value| Description|
| --- | --- |
| output_name | Str, output name. The output operator name, operator output edge index, top name, or output name. The format of the return value obtained by calling this API varies according to the original network and modeling method.<br> Caffe: The format of the return value is as follows, in which items are separated by colons (:) (a top name is returned only when the model contains one.): `Output operator name:Operator output edge index:Top name` <li>TensorFlow network:<br> In scenarios where the ATC tool is used to build OM models, the format of the return value is as follows, in which items are separated by colons (:): `Output operator name:Operator output edge index`<br> When the graph APIs are used to build an OM model, the return value format is as follows, in which items are separated by underscores (\_): `output_network output index_output operator name_operator output edge index` </li><li>ONNX network: The format of the return value is as follows, in which items are separated by colons (:): `Output operator name:Operator output edge index:Output name`. In the process of building an OM model, the output name is included in the return value in the following cases:<br> The output operator name or output name is not specified in the network model (the system automatically obtains the output name from the original model).<br> Only the output name is specified in the network model. During OM modeling using graph APIs, if the output operator name in the network model is specified, the format of the return value is as follows, in which items are separated by underscores (_): `output_network output index_output operator name_operator output edge index` </li>|
