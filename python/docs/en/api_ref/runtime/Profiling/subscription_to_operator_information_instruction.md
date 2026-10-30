# Overview

## General Restrictions

The APIs in this section cannot be called together with [Profiling Data Collection APIs](../Profiling/data_profiling_apis.md). [acl.prof.init](function-init-Profiling.md), [acl.prof.start](function-start.md), [acl.prof.stop](function-stop.md), and [acl.prof.finalize](function-finalize-Profiling.md) cannot be called between [acl.prof.model\_subscribe](function-model_subscribe.md) and [acl.prof.model\_unsubscribe](function-model_unsubscribe.md).

## API Constraints

- **API call requirements**
  - [acl.prof.model\_subscribe](function-model_subscribe.md) is called before model execution. If [acl.prof.model\_subscribe](function-model_subscribe.md) is called during model execution, the data collected by profiling is the data after [acl.prof.model\_subscribe](function-model_subscribe.md) is called, which may cause data incompleteness.
  - [acl.prof.model\_subscribe](function-model_subscribe.md) must be used in pair with [acl.prof.model\_unsubscribe](function-model_unsubscribe.md). Do not call [acl.prof.model\_subscribe](function-model_subscribe.md) for multiple times to subscribe to the same model before calling [acl.prof.model\_unsubscribe](function-model_unsubscribe.md).
  - It is not allowed to pass a non-existent model ID to the [acl.prof.model\_subscribe](function-model_subscribe.md) call.
  - It is not allowed to pass a non-existent model ID or an unsubscribed model ID to the [acl.prof.model\_unsubscribe](function-model_unsubscribe.md) call.
  - If multiple models are loaded to the same device, the subscription configurations delivered to the models are the same.

- **API call sequence**
  - **Recommendation**

    Load a model --\> [acl.prof.model\_subscribe](function-model_subscribe.md) --\> [acl.prof.get\_op\_desc\_size](function-get_op_desc_size.md) --\> [acl.prof.get\_op\_num](function-get_op_num.md) --\> [acl.prof.get\_op\_type](function-get_op_type.md)/[acl.prof.get\_op\_name](function-get_op_name.md)/[acl.prof.get\_op\_start](function-get_op_start.md)/[acl.prof.get\_op\_end](function-get_op_end.md)/[acl.prof.get\_op\_duration](function-get_op_duration.md)/[acl.prof.get\_model\_id](function-get_model_id.md) --\> [acl.prof.model\_unsubscribe](function-model_unsubscribe.md)

  - **The following is an example of an incorrect call sequence**. In this example, the same model is repeatedly subscribed.

    Load model 1: --\> [acl.prof.model\_subscribe](function-model_subscribe.md)\ (specifying model 1) --\> [acl.prof.model\_subscribe](function-model_subscribe.md)\ (specifying model 1) --\> [acl.prof.model\_unsubscribe](function-model_unsubscribe.md)
