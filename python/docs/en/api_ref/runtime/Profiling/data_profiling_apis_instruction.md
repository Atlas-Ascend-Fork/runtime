# Overview

## General Restrictions

This API cannot be called together with [Subscribing to Operator Information](subscription_to_operator_information.md). The [acl.prof.model\_subscribe](function-model_subscribe.md), aclprofGet\*, or [acl.prof.model\_unsubscribe](function-model_unsubscribe.md) API cannot be called between [acl.prof.init](function-init-Profiling.md) and [acl.prof.finalize](function-finalize-Profiling.md).

## API Constraints

- **API requirements**
  - [acl.prof.init](function-init-Profiling.md) must be called after [acl.init](../init/function-init.md)and before model loading.

        If profiling has been configured by calling [acl.init](../init/function-init.md), an error is returned when [acl.prof.init](function-init-Profiling.md), [acl.prof.start](function-start.md), [acl.prof.stop](function-stop.md), or [acl.prof.finalize](function-finalize-Profiling.md) is called.

        If [acl.prof.init](function-init-Profiling.md) is not called, an error is returned when [acl.prof.start](function-start.md), [acl.prof.stop](function-stop.md), or [acl.prof.finalize](function-finalize-Profiling.md) is called.

  - [acl.prof.start](function-start.md) is called before model execution. If [acl.prof.start](function-start.md) is called during model execution, the data collected by profiling is the data after [acl.prof.start](function-start.md) is called, which may cause data incompleteness.

        When calling [acl.prof.start](function-start.md), you can specify one or more devices to profile.

        In a user app process, an error is returned if [acl.prof.start](function-start.md) is called repeatedly and the specified profiling configuration or device is duplicate.

  - In the lifetime of a user app process, do not call the [acl.prof.init](function-init-Profiling.md) and [acl.prof.finalize](function-finalize-Profiling.md) pair more than once. Otherwise, the path for storing profile data files may be changed.
  - The [acl.prof.start](function-start.md) and [acl.prof.stop](function-stop.md) APIs must be used in pairs.
  - Profiling msproftx collection APIs must be called between [acl.prof.start](function-start.md) and [acl.prof.stop](function-stop.md). The APIs used for pairing are [acl.prof.create\_stamp](function-create_stamp.md)/[acl.prof.destroy\_stamp](function-destroy_stamp.md), [acl.prof.push](function-push.md)/[acl.prof.pop](function-pop.md) and [acl.prof.range\_start](function-range_start.md)/[acl.prof.range\_stop](function-range_stop.md).
  - If [acl.finalize](../init/function-finalize.md) is called and a normal exit code is received, the execution is complete. Otherwise, the execution is abnormal. Due to the lack of support for multi-process concurrent execution in profile data collection, to ensure that the driver can be properly stopped, it is necessary to wait until the previous profile data collection test case is fully executed before starting the next round of collection. You are advised to add exception handling operations to the return value of [acl.finalize](../init/function-finalize.md) to facilitate execution status display and fault locating.

- **API call sequence**
  - The recommended API call sequence is as follows. In this example, two models are executed in a single user app process:

        [acl.init](../init/function-init.md) --\> [acl.prof.init](function-init-Profiling.md) --\> [acl.prof.start](function-start.md) (specifying device 0 and device 1) --\> model 1 load --\> model 1 execution --\>[acl.prof.stop](function-stop.md) (the aclprofConfig data must be consistent with [acl.prof.start](function-start.md) --\> [acl.prof.start](function-start.md) (specifying device 1 and device 2) --\> model 2 load --\> model 2 execution --\>[acl.prof.stop](function-stop.md) (the aclprofConfig data must be consistent with [acl.prof.start](function-start.md)) --\> [acl.prof.finalize](function-finalize-Profiling.md) --\> other task execution --\> model unload --\>[acl.finalize](../init/function-finalize.md)

  - The following is an example of an incorrect call sequence. In this example, [acl.prof.start](function-start.md) is called repeatedly and duplicated devices are specified in a single app process:

        [acl.init](../init/function-init.md) --\> [acl.prof.init](function-init-Profiling.md) --\> [acl.prof.start](function-start.md) (specifying device 0 and device 1) --\> [acl.prof.start](function-start.md) (specifying device 1 and device 2) --\> model 1 loading --\> model 1 execution --\> model 2 loading --\> model 2 execution --\> [acl.prof.stop](function-stop.md) --\> [acl.prof.stop](function-stop.md) --\> [acl.prof.finalize](function-finalize-Profiling.md)--\> other task execution --\> model unloading --\>[acl.finalize](../init/function-finalize.md)
