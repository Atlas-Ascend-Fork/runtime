# Function: init

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

Performs initialization.

## Prototype

- **C Prototype**

    ```c
    aclError aclInit(const char *configPath)
    ```

- **Python Function**

    ```python
    ret = acl.init(config_path)
    ```

## Parameters

| Parameter| Description|
| --- | --- |
| config_path | Path of the configuration file, including the file name.<br>The configuration file is in JSON format. A JSON file allows up to 10 levels of curly brackets and square brackets, respectively. During initialization, you can use this configuration file to enable dump, configure profiling, and set other options. For details, see the configuration examples of each function in the following sections. To use the default configurations, directly call acl.init without passing any parameter or set the configuration file to an empty JSON string (that is, only {} exists in the configuration file).|

## Return Values

| Return Value| Description|
| --- | --- |
| ret | Int, error code. If 0 is returned, the operation is successful. If [other values](../datatypes/aclError.md) are returned, the operation fails.|

## Constraints

- Before using the pyACL APIs to develop an application, call the acl.init API. Otherwise, errors may occur during the initialization of internal system resources, causing exceptions in other services.

- aclInit can be called multiple times in a process, but aclFinalize or aclFinalizeReference must be called for deinitialization.
  - The configuration must be consistent each time aclInit is called. Otherwise, only the configuration of the first call is valid. Calling aclInit again may cause errors.
  - To be compatible with earlier versions, the error code ACL\_ERROR\_REPEAT\_INITIALIZE is returned when aclInit is called repeatedly. You can ignore this error and continue to process services.
  - The aclInit and aclFinalize APIs can be called repeatedly for initialization and deinitialization, respectively. Only sequential calls are available for the two APIs.

    ```text
    aclInit --> Service processing --> aclFinalize --> aclInit --> Service processing --> aclFinalize
    ```

    After you call aclInit multiple times, you only need to call aclFinalize once to perform deinitialization. The aclInit reference count will be reset to 0.

  - If the aclInit and aclFinalizeReference APIs are called for initialization and deinitialization, respectively, the two APIs need to be called in pairs.

    aclFinalizeReference involves reference counting. Each time aclInit is called, the reference count is incremented by 1. Each time aclFinalizeReference is called, the reference count decreases by 1. Deinitialization is performed only when the reference count decreases to 0.

    Repeated initialization and deinitialization are supported. The APIs can be called in sequence or concurrently. The API call sequence is as follows:

    - The following figure shows the sequential call sequence.

        ![](../figures/sequential_invoking_diagram.png)

    - The following figure shows the concurrent call sequence.

        ![](../figures/concurrent_invoking_diagram-0.png)

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
  <!-- npu="A3,910b" id7 -->
  - `aic_err_detail_dump`: detailed exception dump, which extends the lightweight exception dump with the internal storage, register, and call stack information about the AI Core.

    When configuring this option, pay attention to the following points:

    - This option is supported only by the following models and requires the driver of 25.0.RC1 or later:

        <!-- npu="910b" id8 -->
        Atlas A2 products
        <!-- end id8 -->

        <!-- npu="A3" id9 -->
        Atlas A3 products
        <!-- end id9 -->

        You can click [Link](https://www.hiascend.com/en/hardware/firmware-drivers) to download the driver installation package of Ascend HDK 25.0.RC1 or later and install or upgrade the driver by referring to the corresponding version documentation.

    - During dump file export, the AI Core where an exception operator is located is suspended, which may affect the execution of other processes on the device. After dump files are exported, the AI Core is automatically restored. Therefore, if multiple user service processes on the host specify the same device, you are advised not to use the `aic_err_detail_dump` option.
    - After the dump file is exported, the user service process on the host is forcibly terminated. The error reported during the forcible exit is not used as the input for AI Core problem analysis.
    - After the `aic\_err\_detail\_dump` option is configured, if the dump file is generated but not the `\*.core` file, it indicates that the function corresponding to the `aic\_err\_detail\_dump` option is not enabled. In this case, the system automatically switches to dump by `aic\_err\_brief\_dump`.
  <!-- end id7 -->

  - `lite_exception`: lightweight exception dump. To be compatible with earlier versions, the effect is the same as that of `aic\_err\_brief\_dump`.

- `dump_path` is an optional parameter that indicates the path for storing the exported dump file.

    The priorities of the dump file storage paths are as follows: `NPU_COLLECT_PATH` environment variable \> `ASCEND\_WORK\_PATH` environment variable \> `dump\_path` in the configuration file \> Current execution directory of the application

    For details about the environment variables, see [Environment Variables](https://hiascend.com/en/document/redirect/CannCommunityEnvRef).

- To view the content of the exported dump file, convert the dump file to a NumPy file and then view the NumPy file through Python. For details about the conversion procedure, see "Extended Functions \> Viewing Dump Files" in [Precision Tuning Tool](https://hiascend.com/en/document/redirect/CannCommunityToolAccucacy).

    If `dump_scene` is set to `aic_err_detail_dump`, use the msDebug tool to view the content of the exported dump file. For details, see [Operator Development Tools](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/devaids/optool/MindStudio/26.1.0/en/user_guide/msot_user_guide.md).

- The dump configuration for exception operators cannot be enabled if the model dump configuration or single-operator dump configuration is enabled.

## Example of Overflow Operator Dump Configuration

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

<!-- npu="950,A3,910b,310p,310b" id11 -->
This configuration is only available for the following models:

<!-- npu="950" id12 -->
Ascend 950PR&950DT products
<!-- end id12 -->

<!-- npu="A3" id13 -->
Atlas A3 products
<!-- end id13 -->

<!-- npu="910b" id14 -->
Atlas A2 products
<!-- end id14 -->

<!-- npu="310b" id15 -->
Atlas 200I/500 A2 inference products
<!-- end id15 -->

<!-- npu="310p" id16 -->
Atlas inference products
<!-- end id16 -->
<!-- end id11 -->

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

## Profiling Configuration

For details about the Profiling data collection configuration, configuration examples, description, and restrictions, see "Other Methods of Collecting Profile Data \> Using the acl.json Configuration File" in the [Performance Tunning Tool](https://hiascend.com/en/document/redirect/CannCommunityToolProfiling). **Profiling configuration is disabled by default.**

Dump configuration and profiling configuration are mutually exclusive. The dump operation may affect system performance, resulting in inaccurate profile data collected by Profiling.

## Example of Operator Cache Aging Configuration

**Operator cache aging configuration**. To save memory and balance the calling performance, you can use the `max_opqueue_num` parameter to configure the maximum length of the `operator type and single-operator model` mapping queue. If the length of the mapping queue reaches the maximum, the least used mapping information and single-operator models in the cache are deleted before the most recent mapping information and the corresponding single-operator model are loaded. The default maximum length of the mapping queue is `20000`.

The `max\_opqueue\_num` parameter is used to configure the maximum length of the operator type-single-operator model mapping queue to age the operator cache information. The following is an example of the configuration file:

```json
{
        "max_opqueue_num": "10000"
}
```

The details are as follows:

- For statically loaded operators (that is, operators loaded by loading the .om file compiled from a single-operator, for example, acl.op.set_model_dir), the aging configuration is invalid and the operator information will not be aged.
- The API maintains two mapping queues, one for static-shape and the other for dynamic-shape operators. However, their maximum lengths are both determined by the max_opqueue_num parameter.
- The value of `max_opqueue_num` is the sum of the number of single-operator models with statically loaded operators and the number of single-operator models with operators compiled online. Therefore, the value of `max_opqueue_num` must be greater than the number of single-operator models with statically loaded operators that are available in the current process; otherwise, the information about operators compiled online cannot be aged.

## Example of Error Information Report Mode Configuration

**Error information report mode configuration**, which is used to control the [acl.get\_recent\_err\_msg](../exception/function-get_recent_err_msg.md) API to obtain error information by process or thread level. By default, error information is obtained by thread level.

Value range of the `err_msg_mode` parameter: `0` (default value), indicating that error information is obtained by thread; `1`, indicating that error information is obtained by process.

The following gives a configuration example:

```json
{
        "err_msg_mode": "1"
}
```

## Example of Default Device Configuration

This configuration is used to configure the default compute device. If the device is also specified by calling [set_device](../device/function-set_device.md), aclrtSetDevice has a higher priority. If you want to explicitly create a context after enabling the default device configuration, you need to call [set_device](../device/function-set_device.md). Otherwise, service exceptions may occur.

Set the device ID in the `default_device` parameter. The device ID can be 0 or a positive decimal integer. After the number of available devices is obtained by calling [acl.rt.get_device_count](../device/function-get_device_count.md), the value range of the device ID is [0, Number of available devices – 1].

The following gives a configuration example:

```json
{
    "defaultDevice":{
        "default_device":"0"
    }
}
```

<!-- npu="950,A3,910b,310b" id17 -->
## Example of AI Core Stack Size Configuration

This configuration is used to control the size of the stack space allocated to each AI Core during kernel execution in a process. **The default value is 32 KB.**

Constraints: When compiling AI Core operators, the configured AI Core stack space size is valid only when O0 is enabled.

For Ascend 950PR&950DT products, the preceding constraints do not apply.

Set the stack space size in the `aicore_stack_size` parameter. The unit is byte. The value must meet the following requirements:

- The value of `aicore_stack_size` must be an integer multiple of 16 KB. If the input value is not an integer multiple of 16 KB, it is rounded up to ensure that it is an integer multiple of 16 KB.
- The minimum value of `aicore_stack_size` is 32 KB. If the input value is less than 32 KB, the default value 32 KB is used.
<!-- npu="950,A3,910b,310b" id18 -->
- The maximum value of `aicore_stack_size` for each product is as follows:

    <!-- npu="950" id19 -->
    For Ascend 950PR&950DT products, the maximum value of `aicore_stack_size` is 128 KB.
    <!-- end id19 -->

    <!-- npu="A3" id20 -->
    For Atlas A3 products, the maximum value of `aicore_stack_size` is 192 KB.
    <!-- end id20 -->

    <!-- npu="910b" id21 -->
    For Atlas A2 products, the maximum value of `aicore_stack_size` is 192 KB.
    <!-- end id21 -->

    <!-- npu="310b" id22 -->
    For Atlas 200I/500 A2 inference products, the maximum value of `aicore_stack_size` is 7680 KB.
    <!-- end id22 -->

<!-- end id18 -->
The following gives a configuration example:

```json
{
    "StackSize":{
        "aicore_stack_size":32768
    }
}
```
<!-- end id17 -->

<!-- npu="950" id23 -->
## Example of SIMT Operator Stack Size Configuration

**Single Instruction Multiple Thread (SIMT) stack size configuration** is used to control the stack size of an SIMT operator in each thread and the divergence stack size of an SIMT operator, in bytes.

<!-- npu="950" id24 -->
Only Ascend 950PR&950DT products support this configuration.
<!-- end id24 -->

`simt_stack_size` specifies the stack size of each thread of the SIMT operator. The unit is byte. The default value is 1152 bytes.

`simt_divergence_stack_size` specifies the divergence stack size of the SIMT operator. The unit is byte. The default value is 1024 bytes.

The values of `simt_stack_size` and `simt_divergence_stack_size` must be integer multiples of 128. If the input value is not an integer multiple of 128, the API automatically rounds up the value to ensure that it is an integer multiple of 128.

The following gives a configuration example:

```json
{
  "StackSize": {      
    "simt_stack_size": 1024,            
    "simt_divergence_stack_size": 512   
  }
}
```
<!-- end id23 -->

<!-- npu="950" id25 -->
## Example of SIMT Printf FIFO Size Configuration

This configuration is used to control the FIFO buffer size available for Printf output in SIMT operators, in bytes.

<!-- npu="950" id26 -->
Only Ascend 950PR&950DT products support this configuration.
<!-- end id26 -->

`simt\_printf\_fifo\_size` specifies the size of the Printf maintenance and test space of the SIMT operator. The unit is byte. The value must be an integer multiple of 8. If the input value is not an integer multiple of 8, the API automatically rounds up the value to ensure that it is an integer multiple of 8.

The default value of `simt\_printf\_fifo\_size` is 2 MB. The minimum value is 1 MB and the maximum value is 64 MB.

The following gives a configuration example:

```json
{
  "simt_printf_fifo_size": 1048576
}
```
<!-- end id25 -->

<!-- npu="950,A3,910b" id27 -->
## Example of SIMD Printf FIFO Size Configuration

This configuration is used to control the Printf FIFO buffer size available to SIMD operators on each Core, in bytes.

Only Ascend 950PR&950DT, Atlas A3, and Atlas A2 products support this configuration.

`simd\_printf\_fifo\_size\_per\_core` specifies the size of the Printf maintenance and test space of the SIMD operator. The unit is byte. The value must be an integer multiple of 8. If the input value is not an integer multiple of 8, the API automatically rounds up the value to ensure that it is an integer multiple of 8.

The default value of `simd\_printf\_fifo\_size\_per\_core` is 32 KB. The minimum value is 1 KB and the maximum value is 64 MB.

The following gives a configuration example:

```json
{
  "simd_printf_fifo_size_per_core": 1048576
}
```
<!-- end id27 -->

## Reference

For details about API call examples, see "Initialization and Deinitialization" in "Application Development (Python)".

More flexible APIs are provided for enabling dump or profiling. Unlike aclInit, these APIs can be called repeatedly in a process, allowing varied dump/profiling configurations with each call.

- Obtain dump data. For details, see [Function: init\_dump](../dump/function-init_dump.md), [Function: set\_dump](../dump/function-set_dump.md), and [Function: finalize\_dump](../dump/function-finalize_dump.md). If dump data does not need to be written to a file, you can obtain the dump data by using a callback function. For details, see [11.2.15-Function: dump\_reg\_callback](../dump/function-dump_reg_callback.md).
- Obtain profile data. For details, see [Profiling Data Collection APIs](../Profiling/data_profiling_apis.md).
