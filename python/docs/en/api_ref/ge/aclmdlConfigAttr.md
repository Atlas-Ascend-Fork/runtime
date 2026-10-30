# aclmdlConfigAttr

| Model Loading Configuration Type| Definition|
| --- | --- |
| ACL_MDL_PRIORITY_INT32 = 0 | Priority of model execution. A smaller value indicates a higher priority. This parameter is optional. Its value is [0, 7]. The default value is `0`.|
| ACL_MDL_LOAD_TYPE_SIZET = 1 | Model loading mode. For details, see Table 1. This parameter is mandatory.|
| ACL_MDL_PATH_PTR = 2 | (Required if the model is loaded from a file) Pointer address of the offline model file path.|
| ACL_MDL_MEM_ADDR_PTR = 3 | Start address of the model in the memory. This parameter is mandatory if the model is loaded from memory.|
| ACL_MDL_MEM_SIZET = 4 | (Required if the model is loaded from memory) Size of the model in the memory. Must be used in conjunction with ACL_MDL_MEM_ADDR_PTR.|
| ACL_MDL_WEIGHT_ADDR_PTR = 5 | (Required if the weight memory is managed by the user) Pointer address of the model weight memory on the device. If this parameter is not set, the system manages the memory.|
| ACL_MDL_WEIGHT_SIZET = 6 | (Required if the weight memory is managed by the user) Size of the weight memory on the device, in bytes. If this parameter is not set, the system manages the memory. Must be used in conjunction with ACL_MDL_WEIGHT_ADDR_PTR.|
| ACL_MDL_WORKSPACE_ADDR_PTR = 7 | (Required if the workspace is managed by the user) Pointer address of the model workspace on the device. If this parameter is not set, the system manages the memory.|
| ACL_MDL_WORKSPACE_SIZET = 8 | (Required if the workspace is managed by the user) Size of the workspace required by the model, in bytes. Must be used in conjunction with ACL_MDL_WORKSPACE_ADDR_PTR.|
| ACL_MDL_INPUTQ_NUM_SIZET = 9 | (Required if the model is loaded by using a queue) Size of the model input queue. Must be used in conjunction with `ACL_MDL_INPUTQ_ADDR_PTR`.|
| ACL_MDL_INPUTQ_ADDR_PTR = 10 | (Required if the model is loaded by using a queue) Pointer address of the model input queue ID.|
| ACL_MDL_OUTPUTQ_NUM_SIZET = 11 | Size of the model output queue. This parameter is mandatory if the model is loaded by using a queue. It must be used in conjunction with `ACL_MDL_OUTPUTQ_ADDR_PTR`.|
| ACL_MDL_OUTPUTQ_ADDR_PTR = 12 | (Required if the model is loaded by using a queue) Pointer address of the model output queue ID. One model output corresponds to one queue ID.|
| ACL_MDL_WORKSPACE_MEM_OPTIMIZE = 13 | Whether to enable model buffer optimization. The value `1` indicates that the function is enabled, and the value `0` indicates that the function is disabled. If buffer planning is considered or resources are limited, you are advised to enable the buffer optimization function before model loading to reduce the buffer size. In this case, the buffer does not contain the part for storing the input and output data of the model. Before model execution, you need to allocate the buffer for storing the input and output data of the model. Therefore, even if buffer optimization is enabled during model loading, subsequent model execution is not affected.|
| ACL_MDL_WEIGHT_PATH_PTR = 14 | Pointer address to the directory where weight files are located. If the size of an .om model file is limited, this parameter can be used to implement the function of externalizing weight files. If `ACL_MDL_LOAD_TYPE_SIZET` is set to `ACL_MDL_LOAD_FROM_MEM`, model data is loaded from the memory. You can also use `ACL_MDL_WEIGHT_PATH_PTR` to specify the weight file directory. Generally, if the size of an .om model file is limited or the model file is encrypted, you need to specify the weight file directory separately. The prerequisite is that when using the ATC tool to generate the .om file,<br> set the `--external_weight` parameter to `1` (`1` indicates that the weights of the Const/Constant nodes on the original network are saved in a separate file).|
| ACL_MDL_MEM_MALLOC_POLICY_SIZET | Memory allocation rule, whose value is of the size_t type. Not supported in the current version. Options: <li>ACL_MEM_MALLOC_HUGE_FIRST. When the allocated memory is less than or equal to 1 MB, only normal page memory is allocated even under this memory allocation policy. When the allocated memory is greater than 1 MB, the allocation of huge page memory is prioritized. If the huge page memory is insufficient, normal page memory is allocated. </li><li> ACL_MEM_MALLOC_HUGE_ONLY. Allocates only huge page memory. If the huge page memory is insufficient, an error is returned. </li><li> ACL_MEM_MALLOC_NORMAL_ONLY.Allocates only normal page memory. If the normal page memory is insufficient, an error is returned. </li><li> ACL_MEM_TYPE_LOW_BAND_WIDTH. Allocates memory from the physical memory with low bandwidth. </li><li> ACL_MEM_TYPE_HIGH_BAND_WIDTH. Allocates memory from the physical memory with high bandwidth.</li> |
| ACL_MDL_WITHOUT_GRAPH_INT32 | Whether to keep the computational graphs and cached data after model loading. It applies only when the input is a static shape. The value is of the INT32 type. The options are as follows:<li> 0: The computational graphs and cached data are retained. </li><li>1: The computational graphs and cached data are not retained. If this parameter is set to `1`, the system releases the computational graphs and the cached data after the model is successfully loaded, reducing memory usage. However, releasing the cached data impacts profiling and operator information obtaining in abnormal scenarios. Therefore, in profiling scenarios, `acl.prof.start` must be called before loading the model; otherwise, profiling is unavailable. In abnormal scenarios, the call to [acl.mdl.create_and_get_op_desc](function-create_and_get_op_desc.md) may fail to return the operator description.</li> |

<!-- npu="910" id6 -->
ACL\_MDL\_PRIORITY\_INT32 value description: For Atlas training products, this enumeration does not take effect when CANN is installed in a Docker container with computing power allocation configured.
<!-- end id6 -->

**Table 1** ACL\_MDL\_LOAD\_TYPE\_SIZET values

| Model Loading Mode| Definition|
| --- | --- |
| ACL_MDL_LOAD_FROM_FILE = 1 | Loads an offline model from a file. The memory is managed by the system.|
| ACL_MDL_LOAD_FROM_FILE_WITH_MEM = 2 | Loads an offline model from a file. The model workspace is managed by the user.|
| ACL_MDL_LOAD_FROM_MEM = 3 | Loads an offline model from memory. The model workspace is managed by the system.|
| ACL_MDL_LOAD_FROM_MEM_WITH_MEM = 4 | Loads an offline model from memory. The model workspace is managed by the user.|
| ACL_MDL_LOAD_FROM_FILE_WITH_Q = 5 | Loads an offline model from a file. The inputs and outputs of a model are stored in queues.|
| ACL_MDL_LOAD_FROM_MEM_WITH_Q = 6 | Loads an offline model from memory. The inputs and outputs of the model are stored in queues.|

**Note**: If `ACL_MDL_LOAD_TYPE_SIZET` is set to `ACL_MDL_LOAD_FROM_MEM`, model data is loaded from the memory. You can also use the `ACL_MDL_WEIGHT_PATH_PTR` option to specify the weight file directory.
