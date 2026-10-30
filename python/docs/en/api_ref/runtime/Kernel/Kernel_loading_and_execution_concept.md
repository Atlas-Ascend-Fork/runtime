# Concepts and Instructions

## Basic Concepts

The APIs in this section manipulate the operator binary, kernel function, kernel function parameter list, and parameters. The following figure shows the relationships between them.

![](../figures/relationship_between_aclmdlDataset_and_aclDataBuffer.png)

- **Operator binary**: After the operator source code is built, the operator binary file `\*.o` is obtained. For a built-in CANN operator, you can obtain the operator binary file from the operator binary package (named `Ascend-cann-kernels-*.run`). For a custom operator, you can obtain the operator binary file after compiling the operator and releasing the binary file. For details about how to develop and build a custom operator, see [Ascend C Operator Development](https://hiascend.com/en/document/redirect/CannCommunityOpdevAscendC).
- **Kernel function**: It is an entry point function for implementing an operator on the device. You can use the syntax extension of a C/C++ function to write the code running on the device. You can perform data access and compute operations in the kernel function to implement all functions of the operator.

## API Call Sequence for Kernel Loading and Execution

![](../figures/kernel_loading_and_execution_process.png)

The major steps are as follows:

1. Call [acl.init](../init/function-init.md) for initialization.
2. Allocate runtime resources, including calling [acl.rt.set_device](../device/function-set_device.md) to specify the device for computation and calling [acl.rt.create_stream](../stream/function-create_stream.md) to create a stream.

    For details, see the runtime resource allocation and deallocation sections in *Application Development (Python)*.

3. Call [acl.rt.binary\_load\_from\_file](function-binary_load_from_file.md) to load the operator binary file.
4. Call [acl.rt.binary_get_function](function-binary_get_function.md) to obtain the kernel handle.
5. Operate the parameter list according to the kernel function handle. The operations are as follows:
    1. Initialize the parameter list.

        Currently, the memory can be managed by the system (by calling [acl.rt.kernel_args_init](function-kernel_args_init.md)) or by you (by calling [acl.rt.kernel_args_init_by_user_mem](function-kernel_args_init_by_user_mem.md)).

    2. Append parameters and update parameter values.

        The kernel function parameter list contains different types of parameters, such as pointer parameters, placeholders, and uint8_t parameters.

        - Pointer parameters: The values indicate the device memory address. Generally, the input and output of an operator are of this type. You need to call the device memory allocation API (such as [acl.rt.malloc](../memory/function-malloc.md)) in advance to allocate memory and copy data to the device.
        - Placeholder: A placeholder is also a pointer parameter. The difference is that you do not need to manually copy the parameter data to the device. Instead, this operation is completed by the Runtime. The Runtime does not fill the actual device address when a parameter is appended, but fills it only during kernel launch. That is where the placeholder comes in. For non-input and non-output parameters of an operator, you can use a placeholder to combine the host-to-device copies of small data (< 2 KB recommended) into one copy during kernel launch, thus reducing the number of copy operations and improving performance.

        ![](../figures/kernel_function_parameter_list_diagram.png)

        You can call different parameter appending APIs for different types of parameters.

        - For a placeholder parameter, the associated memory must be placed after all parameters. Therefore, when appending parameters, call [acl.rt.kernel_args_append_place_holder](function-kernel_args_append_place_holder.md) to reserve a placeholder. After all parameters are appended, call [acl.rt.kernel_args_get_place_holder_buffer](function-kernel_args_get_place_holder_buffer.md) to obtain the memory address pointed to by the placeholder. You can manage the data in the memory based on the obtained memory address.
        - For non-placeholder parameters (such as pointer parameters and uint8_t parameters), call [acl.rt.kernel_args_append](function-kernel_args_append.md) to append the user-defined parameter values to the parameter data area pointed to by argsHandle. To update the parameter values, call [acl.rt.kernel\_args\_para\_update](function-kernel_args_para_update.md).

        Note that the kernel function parameter list may contain multiple parameters, and parameters of different types may appear in an interleaved manner. Therefore, you need to append parameters from left to right in the order defined in the parameter list. A maximum of 128 parameters can be appended.

    3. End the parameter appending and parameter value update.

        After all parameters are appended, call [acl.rt.kernel\_args\_finalize](function-kernel_args_finalize.md) to indicate that the parameter assembly is complete. However, after [acl.rt.kernel\_args\_finalize](function-kernel_args_finalize.md) is called, the parameter values can still be updated. After the update, call [acl.rt.kernel\_args\_finalize](function-kernel_args_finalize.md) again.

6. Call [acl.rt.launch\_kernel\_with\_config](function-launch_kernel_with_config.md) to launch the computation task of the operator.
7. Call [acl.rt.binary\_unload](function-binary_unload.md) to unload the operator binary file.
8. Deallocate runtime resources, including calling [acl.rt.destroy_stream](../stream/function-destroy_stream.md) to destroy the stream and calling [acl.rt.reset_device](../device/function-reset_device.md) to release device resources.

    For details, see the runtime resource allocation and deallocation sections in *Application Development (Python)*.

9. Call [acl.finalize](../init/function-finalize.md) for deinitialization.
