# Synchronous and Asynchronous APIs

CANN supports the following explicit synchronization types. After calling these types of APIs, the host thread is blocked until the related tasks are completed.

- **Device synchronization**: `acl.rt.synchronize_device`

 Blocks the current host thread until all explicitly or implicitly created streams on the device complete all previously delivered tasks. Avoid using this function as much as possible, because it delays host running.

- **Stream synchronization**: `acl.rt.synchronize_stream`

 Blocks the current host thread until the specified stream completes all delivered tasks.

- **Event synchronization**: `acl.rt.synchronize_event`

 Blocks the current host thread until the specified event is completed. It is a finer-grained synchronization.

For asynchronous APIs, the API call only indicates that tasks are delivered. The function is returned to the host thread before the tasks are completed. You need to call the explicit synchronization APIs to block the host thread until the tasks are completed.
