# Function: set\_dump

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

Sets dump parameters.

## Prototype

- **C Prototype**

    ```c
    aclError aclmdlSetDump(const char *dumpCfgPath)
    ```

- **Python Function**

    ```python
    ret = acl.mdl.set_dump(dump_cfg_path)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| dump_cfg_path | Str, path of the configuration file, including the file name.<br>You can use this configuration file to enable or configure various dump information. For details, see the description in the following function configuration examples. If the operator input or output contains sensitive user information, there may be risks of information leakage.|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- [acl.mdl.init_dump](function-init_dump.md) must be used in pair with [acl.mdl.set_dump](function-set_dump.md) and [acl.mdl.finalize_dump](function-finalize_dump.md) to dump data to files. These APIs can be called for multiple times in a single process to obtain dump data of different Dump configurations.
- Example scenario:
  - To execute the model twice, you need to set different dump configurations. The API call sequence is as follows: [acl.init](../init/function-init.md) --\> acl.mdl.init\_dump --\> [acl.mdl.set\_dump](function-set_dump.md) --\> Model Loading --\> Model Execution --\> [acl.mdl.finalize\_dump](function-finalize_dump.md) --\> Model Unloading --\> [acl.mdl.init\_dump](function-init_dump.md) --\> [acl.mdl.set\_dump](function-set_dump.md) --\> Model Loading --\> Model Execution --\> [acl.mdl.finalize\_dump](function-finalize_dump.md) --\> Model Unloading --\> Other tasks --\> [acl.finalize](../init/function-finalize.md)
  - If a model is executed twice, dump is required for the first execution and not required for the second execution. The API call sequence is as follows: [acl.init](../init/function-init.md) --\> acl.mdl.init\_dump --\> [acl.mdl.set\_dump](function-set_dump.md) --\> Model Loading --\> Model Execution --\> [acl.mdl.finalize\_dump](function-finalize_dump.md) --\> Model Unloading --\> Model Loading --\> Model Execution --\> Other tasks --\> [acl.finalize](../init/function-finalize.md)

- The configured dump information is valid only when the model is loaded after the dump function is enabled by calling this API. The dump configuration does not take effect on models loaded before this API call unless you reload the models after this API call.

    For example, in the following API calling sequence, the dump configuration is valid only for model 2.

    [acl.mdl.init_dump](function-init_dump.md) --\> Load model 1. --\> acl.mdl.set\_dump --\> Load model 2. --\> [acl.mdl.finalize\_dump](function-finalize_dump.md)

- If this API is called repeatedly to set the dump configuration for the same model, the most recent configuration is applied.

    For example, in the following API call sequence, the second dump configuration call overwrites the first call:

    [acl.mdl.init_dump](function-init_dump.md) --\> acl.mdl.set\_dump --\> acl.mdl.set\_dump --\> Load model 1. --\> [acl.mdl.finalize\_dump](function-finalize_dump.md)

## Reference

[acl.init](../init/function-init.md) is also available. During initialization, the dump configuration is passed through a JSON file to dump the data at runtime. In this mode, [acl.init](../init/function-init.md) can be called only once in a process. You can modify the dump configuration in the JSON file.

## Model Dump Configuration and Single-Operator Dump Configuration Example

Model dump configuration (used to export the input and output data of operators at each layer in a model) and single-operator dump configuration (used to export the input and output data of a single operator). The exported data is used to compare with that of a specified model or operator to locate accuracy issues. For details about the comparison method, see [Precision Tunning Tool](https://hiascend.com/en/document/redirect/CannCommunityToolAccucacy). Dump is disabled by default.

To enable dump through this API, set the `dump\_path` parameter to specify the path for storing dump data. For details about the parameters, see "Comparison Between NPU and NPU (Offline Inference) \> Preparing Dump Data of an Offline Model" in [Precision Tuning Tool](https://hiascend.com/en/document/redirect/CannCommunityToolAccucacy)

Model dump configuration example:

```json
{                                                                                            
 "dump":{
  "dump_list":[                                                                        
   { "model_name":"ResNet-101"
   },
   {                                                                                
    "model_name":"ResNet-50",
    "layer":[
          "conv1conv1_relu",
          "res2a_branch2ares2a_branch2a_relu",
          "res2a_branch1",
          "pool1"
    ] 
   }  
  ],  
  "dump_path":"/home/output",
                "dump_mode":"output",
  "dump_op_switch":"off",
                "dump_data":"tensor"
 }                                                                                        
}
```

Example of single-operator dump configuration:

```json
{
    "dump":{
        "dump_path":"output",
        "dump_list":[], 
 "dump_op_switch":"on",
        "dump_data":"tensor"
    }
}
```

## Example of Dump Configuration for Exception Operators

**Exception operator dump configuration** (used to export the input and output data, workspace information, and tiling information of the exception operator). The exported data is used to analyze AI Core errors. Dump is disabled by default.

For details about how to collect and locate AI Core errors, see "Typical Faults" and "AI Core Error Locating" in [Troubleshooting]( https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/maintenref/troubleshooting/docs/en/troubleshooting/troubleshooting_intro.md).

You can enable dump for exception operators by setting `dump\_scene`. The following is an example of the configuration file, indicating that lightweight exception dump is enabled:

```json
{
    "dump":{
        "dump_path":"output",
        "dump_scene":"aic_err_brief_dump"
    }
}
```

The details are as follows:

- The `dump_scene` parameter can be set to the following values:
  - `aic_err_brief_dump`: lightweight exception dump, which is used to export the input, output, and workspace data of AI Core error operators.
  - `aic_err_norm_dump`: common exception dump, which extends the lightweight exception dump with the shape, data type, format, and attribute information.
  - `aic_err_detail_dump`: detailed exception dump, which extends the lightweight exception dump with the internal storage, register, and call stack information about the AI Core.

    When configuring this option, pay attention to the following points:

    <!-- npu="A3,910b" id7 -->
    - This option is supported only by the following models and requires the driver of 25.0.RC1 or later:

        <!-- npu="910b" id8 -->
        Atlas A2 products
        <!-- end id8 -->

        <!-- npu="A3" id9 -->
        Atlas A3 products
        <!-- end id9 -->

        You can click [Link](https://www.hiascend.com/en/hardware/firmware-drivers) to download the driver installation package of Ascend HDK 25.0.RC1 or later and install or upgrade the driver by referring to the corresponding version documentation.
    <!-- end id7 -->

    - During dump file export, the AI Core where an exception operator is located is suspended, which may affect the execution of other processes on the device. After dump files are exported, the AI Core is automatically restored. Therefore, if multiple user service processes on the host specify the same device, you are advised not to use the aic_err_detail_dump option.
    - After the dump file is exported, the user service process on the host is forcibly terminated. The error reported during the forcible exit is not used as the input for AI Core problem analysis.
    - After the `aic\_err\_detail\_dump` option is configured, if the dump file is generated but not the `\*.core` file, it indicates that the function corresponding to the `aic\_err\_detail\_dump` option is not enabled. In this case, the system automatically switches to dump by `aic\_err\_brief\_dump`.

  - `lite_exception`: lightweight exception dump. To be compatible with earlier versions, the effect is the same as that of `aic\_err\_brief\_dump`.

- `dump_path` is an optional parameter that indicates the path for storing the exported dump file.

    The priorities of the dump file storage paths are as follows: `NPU_COLLECT_PATH` environment variable \> `ASCEND\_WORK\_PATH` environment variable \> `dump\_path` in the configuration file \> Current execution directory of the application

    For details about the environment variables, see [Environment Variables](https://hiascend.com/en/document/redirect/CannCommunityEnvRef).

- To view the content of the exported dump file, convert the dump file to a NumPy file and then view the NumPy file through Python. For details about the conversion procedure, see "Extended Functions \> Viewing Dump Files" in [Precision Tuning Tool](https://hiascend.com/en/document/redirect/CannCommunityToolAccucacy).

    If `dump_scene` is set to `aic_err_detail_dump`, use the msDebug tool to view the content of the exported dump file. For details, see [Operator Development Tools](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/devaids/optool/MindStudio/26.1.0/en/user_guide/msot_user_guide.md).

- The dump configuration for exception operators cannot be enabled if the model dump configuration or single-operator dump configuration is enabled.

## Example of Overflow/Underflow Operator Dump Configuration

**Dump configuration of the overflow operator** (used to export the input and output data of the overflow operator in the model). The exported data is used to analyze overflow causes and locate model accuracy problems. Dump is disabled by default.

Set `dump\_debug` to `on` to enable the overflow operator configuration. The following is an example of the configuration file:

```json
{
    "dump":{
        "dump_path":"output",
        "dump_debug":"on"
    }
}
```

The details are as follows:

- If `dump\_debug` is not set or is set to off, the overflow operator configuration is disabled.
- If the overflow operator configuration is enabled, `dump_path` must be set to specify the path for storing exported dump files.

    For details about how to parse the exported data file, see "Extended Functions > Overflow/Underflow Operator Data Collection and Analysis" in [Precision Tuning Tool](https://hiascend.com/en/document/redirect/CannCommunityToolAccucacy).

    `dump_path` can be set to an absolute path or a relative path.

  - An absolute path starts with a slash (/), for example, `/home`.
  - If set to a relative path, the path starts with a directory name, for example, `output`.

- The overflow operator configuration cannot be enabled if the model dump configuration or single-operator dump configuration is enabled. Otherwise, an error is returned.
- Only overflow data of AI Core operators can be collected.

## Dump Watch Configuration for Operators

**Dump Watch mode configuration for operators** (enables the observation mode for the output data of a specified operator). If you suspect that the memory is overwritten by other operators after locating the accuracy issues of some operators and excluding the computation issues of the operators, you can enable the Dump Watch mode. **The dump watch mode is disabled by default.**

Set `dump\_scene` to watcher to enable the operator dump watch mode. The following is an example of the configuration file: (1) After operators A and B are executed, the output of operators C and D is dumped. (2) After the C and D operators are executed, the output of the C and D operators is also dumped. Compare the dump files of operators C and D in (1) and (2) to check whether operators A and B overwrite the output memory of operators C and D.

```json
{
    "dump":{
        "dump_list":[
            {
                "layer":["A", "B"],
                "watcher_nodes":["C", "D"]
            }
        ],
        "dump_path":"/home/",
        "dump_mode":"output",
        "dump_level":"op",
        "dump_scene":"watcher"
    }
}
```

The details are as follows:

- Dump watch cannot be applied in the single-operator API dump scenario.
- If the operator dump watch mode is enabled, the overflow operator dump (by configuring the `dump\_debug` parameter) or single-operator model dump (by configuring the `dump\_op\_switch` parameter) cannot be enabled at the same time. Otherwise, an error is reported.
- In `dump\_list`, the `layer` parameter is used to configure the names of the operators that may overwrite the memory of other operators, and the `watcher\_nodes` parameter is used to configure the names of the operators with accuracy issues possibly due to output memory being overwritten by other operators.
  - If `layer` is unspecified, the output of the operators configured for `watcher\_nodes` is dumped after all operators that support dump in the model are executed.
  - If any operator in `layer` and `watcher\_nodes` is not in a static graph or static subgraph, the configuration does not take effect.
  - If an operator is in both `layer` and `watcher\_nodes` an operator in `layer` is a collective communication operator (the operator type starts with `Hcom`, for example, `HcomAllReduce`), only the dump files of operators in `watcher\_nodes` be exported.
  - For a fused operator, use its name after fusion when you add it to `watcher\_nodes`. Otherwise, dump files cannot be exported.
  - Currently, `model_name` cannot be configured in `dump_list`.

- If the operator dump watch mode is enabled, `dump\_path`, which is the path for storing the exported dump file, must be configured.

    The dump files collected here cannot be viewed in a text tool. To view the dump file content, convert the dump files to NumPy files and then view the NumPy files through Python. For details about the conversion procedure, see "Extended Functions \> Viewing Dump Files" in [Precision Tunning Tool](https://hiascend.com/en/document/redirect/CannCommunityToolAccucacy).

    `dump_path` can be set to an absolute path or a relative path.

  - An absolute path starts with a slash (/), for example, `/home`.
  - If set to a relative path, the path starts with a directory name, for example, `output`.

- The `dump_mode` parameter controls which part of the data of the operator configured in `watcher_nodes` is exported. Currently, this parameter can only be set to `output`.
- The `dump_level` parameter is used to set the dump data level. The options are as follows:

  - `op`: dumps data at the operator level.
  - `kernel`: dumps data at the kernel level.
  - `all` (default): dumps data at both the `op` level and the `kernel` level.

    If the default value is used, there are a large number of dump files, for example, dump files starting with `aclnn`. If you have requirements on the dump performance or the memory resources are limited, you can set this parameter to the `op` level to improve the dump performance and reduce the number of dump files.

    **Note**: An operator represents a computational logic (such as addition, subtraction, multiplication, and division). A kernel is the implementation that executes this computational logic, and requires allocation of specific computing devices to complete computation.

<!-- npu="950,A3,910b,310p,310b" id10 -->
## Dump Configuration for Operator Kernel Debugging Information

This dump configuration is used to export the debugging information of the Ascend C operator kernel to locate operator problems. **This dump configuration is disabled by default.**

This configuration is only available for the following models:

<!-- npu="950" id11 -->
Ascend 950PR&950DT products
<!-- end id11 -->

<!-- npu="A3" id12 -->
Atlas A3 products
<!-- end id12 -->

<!-- npu="910b" id13 -->
Atlas A2 products
<!-- end id13 -->

<!-- npu="310b" id14 -->
Atlas 200I/500 A2 inference products
<!-- end id14 -->

<!-- npu="310p" id15 -->
Atlas inference products
<!-- end id15 -->
Set the `dump\_kernel\_data` parameter to enable the dump function for operator kernel debugging information. The following is an example of the configuration file:

```json
{
    "dump":{
        "dump_kernel_data":"printf,assert",
        "dump_path":"/home/"
    }
}
```

The details are as follows:

- `dump\_kernel\_data`: specifies the type of data to be exported. Multiple types can be configured and separated by commas (,). If this field is not configured but the model dump configuration and single-operator dump configuration are enabled, the debugging information is exported based on all by default.

    Available environment variables are as follows:

  - `all`: Exports the output data of all the following types:
  - `printf`: exports the output data debugged by AscendC::printf.
  - `tensor`: exports the output data debugged by AscendC::DumpTensor.
  - `assert`: exports the output data debugged by assert/ascendc_assert.
  - `timestamp`: exports the output data debugged by AscendC::PrintTimeStamp.

- `dump\_path`: specifies the path for storing the exported dump file. This parameter must be set when the operator kernel debugging information dump function is enabled. The value can be an absolute path or a relative path.

    The priorities of the dump file storage paths are as follows: ASCEND\_DUMP\_PATH environment variable \> ASCEND\_WORK\_PATH environment variable \> `dump\_path` in the configuration file. For details about the environment variables, see [Environment Variables](https://hiascend.com/en/document/redirect/CannCommunityEnvRef).

    The content of the exported dump file cannot be directly viewed using a text tool. To view the content, use the show\_kernel\_debug\_data tool to parse the debugging information into a readable format. For details about how to use the tool, see "Programming Guide \> Appendix \> show\_kernel\_debug\_data Tool" in [Ascend C Operator Development](https://hiascend.com/en/document/redirect/CannCommunityOpdevAscendC).

<!-- end id10 -->
