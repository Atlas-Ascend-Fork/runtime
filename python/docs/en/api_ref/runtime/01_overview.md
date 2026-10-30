# 1. Overview

This section describes the basic concepts, pyACL expression conventions, synchronous/asynchronous APIs, and deprecated APIs of CANN Runtime.

## pyACL Conventions

### API Naming Conventions

The APIs are named according to the following rules:

1. acl+*API class*+*Operation verb*+*Object noun*.
2. The *Operation verb* and *Object noun* fields are written with the first letter capitalized.

### API Classes

| API Class| Abbreviation| **Description**|
| --- | --- | --- |
| runtime | rt | Runtime|
| CBLAS | blas | Basic Linear Algebra Subprograms|
| Profiling | prof | Profiling configurations|

>[!NOTE]
>
>- The abbreviation of each class name contains a maximum of four letters.
>- If the class name coincides with the operation object name, the object name is omitted. For example, `acl.mdl.load_from_file_with_mem` is a model API for loading model from file and `mdl` after `Load` is omitted in the API name.

### Variable Naming

In the code examples provided in this guide, a variable with an underscore (_) suffix (for example, *_deviceId_*) is private to the corresponding class.

### Conventions

In this document, API or parameter status identifiers such as "Supported", "Not supported", "Experimental", "Reserved", and "Deprecated" are used. The meanings of these identifiers are as follows:

- "Supported": indicates that an API or parameter is supported.

- "Unsupported": indicates that an API or parameter is not supported. If that API or parameter is used, undefined behavior will occur. For example, the API returns an error or subsequent service functions are abnormal.

- "Reserved": indicates that an API or parameter is reserved. Currently, the API or parameter is not implemented or the functionality is not complete and cannot be called. The API or parameter may be available in later versions.

- "Deprecated": indicates that an API or parameter is planned to be removed in later versions. You are advised to use the replacement API or parameter provided in this document.

## Synchronous and Asynchronous APIs

CANN supports several explicit synchronization types. After these types of APIs are called, the host thread blocks until the related tasks are completed.

- **Device synchronization: `acl.rt.synchronize_device`**

    Blocks the current host thread until all explicitly or implicitly created streams on the device complete all previously delivered tasks. Avoid using this function as much as possible, because it delays host running.

- **Stream synchronization: `acl.rt.synchronize_stream`**

    Blocks the current host thread until the specified stream completes all delivered tasks.

- **Event synchronization: `acl.rt.synchronize_event`**

    Blocks the current host thread until the specified event is completed. It is a finer-grained synchronization.

For asynchronous APIs, the API call only indicates that tasks are delivered. The function is returned to the host thread before the tasks are completed. You need to call the explicit synchronization APIs to block the host thread until the tasks are completed.

## Deprecated APIs and Return Codes

### APIs

- [acl.get_data_buffer_size](datatypes/function-get_data_buffer_size.md)

    This API will be deprecated in later versions. Use the [acl.get_data_buffer_size_v2](datatypes/function-get_data_buffer_size_v2.md) API instead.

- [acl.rt.query_event](event/function-query_event.md)

    This API will be deprecated in later versions. Use the [acl.rt.query_event_status](event/function-query_event_status.md) API instead.

- [acl.util.numpy_to_ptr](util/function-numpy_to_ptr.md)

    This API will be deprecated in later versions. Use the [acl.util.bytes_to_ptr](util/function-bytes_to_ptr.md) API instead.

- [acl.util.numpy_contiguous_to_ptr](util/function-numpy_contiguous_to_ptr.md)

    This API will be deprecated in later versions. Use the [acl.util.bytes_to_ptr](util/function-bytes_to_ptr.md) API instead.

- [acl.util.ptr_to_numpy](util/function-ptr_to_numpy.md)

    This API will be deprecated in later versions. Use the [acl.util.ptr_to_bytes](util/function-ptr_to_bytes.md) API instead.

### Return Code

- [ACL\_ERROR\_NONE](datatypes/aclError.md)

    This return code will be deprecated in future releases. Use [ACL_SUCCESS](datatypes/aclError.md) instead.

- [ACL\_ERROR\_NOT\_STATIC\_AIPP](datatypes/aclError.md)

    This return code will be deprecated in future releases. Use [ACL_ERROR_GE_AIPP_NOT_EXIST](datatypes/aclError.md) instead.

- [ACL\_ERROR\_STREAM\_NOT\_SUBSCRIBE](datatypes/aclError.md)

    This return code will be deprecated in future releases. Use [ACL_ERROR_RT_STREAM_NO_CB_REG](datatypes/aclError.md) instead.

- [ACL\_ERROR\_THREAD\_NOT\_SUBSCRIBE](datatypes/aclError.md)

    This return code will be deprecated in future releases. Use [ACL_ERROR_RT_THREAD_SUBSCRIBE](datatypes/aclError.md) instead.

- [ACL\_ERROR\_WAIT\_CALLBACK\_TIMEOUT](datatypes/aclError.md)

    This return code will be deprecated in future releases. Use [ACL_ERROR_RT_REPORT_TIMEOUT](datatypes/aclError.md) instead.

- [ACL\_ERROR\_INVALID\_DEVICE](datatypes/aclError.md)

    This return code will be deprecated in future releases. Use [ACL_ERROR_RT_INVALID_DEVICEID](datatypes/aclError.md) instead.

- [ACL\_ERROR\_GROUP\_NOT\_SET](datatypes/aclError.md)

    This return code will be deprecated in future releases. Use [ACL_ERROR_RT_GROUP_NOT_SET](datatypes/aclError.md) instead.

- [ACL\_ERROR\_GROUP\_NOT\_CREATE](datatypes/aclError.md)

    This return code will be deprecated in future releases. Use [ACL_ERROR_RT_GROUP_NOT_CREATE](datatypes/aclError.md) instead.
