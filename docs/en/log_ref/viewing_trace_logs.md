# Viewing Trace Logs

<!-- md-trans-meta sourceCommit=ebaafb0e14dfa73083668c3ce44e32283ada3241 translatedAt=2026-10-22T09:39:41.279Z pushedAt=2026-10-23T08:43:56.554Z -->

## Overview

The trace mechanism records the maintenance and test information of the software stack in memory during the runtime process, and saves it to a file when a program error occurs or the process ends. This avoids frequently generating and recording log files during program execution, which will affect performance. Currently, this feature is supported only in the Ascend EP standard form.

## Log Description

The default root directory for trace log storage is "$HOME/ascend/atrace/". You can also specify the trace log storage path through the environment variable **ASCEND\_WORK\_PATH**, for example, by setting **export ASCEND\_WORK\_PATH=/home/test**. For details, see [Environment Variable Reference](https://gitcode.com/cann/docs/blob/9.2.0/docs/en/env-vars/README.md).

The specific storage path of trace logs is "`$HOME/ascend/atrace/trace_{Process group PID}_{PID of the process that initially loads the trace dynamic library}_{Timestamp of the initial load of the trace dynamic library}/{event_name}_event_{Current process PID}_{Timestamp when the directory is generated}/`", where **event\_name** indicates the event type, and the value can be as follows: **schedule** (service process exception, such as an operator execution error), **stackcore** (process crash or receipt of an abnormal signal), and **exit** (normal process exit and destruction).

**Table 1**  Trace log file description

|Storage Path|Description|
|--|--|
|`schedule_tracer_ts_{device_id}.txt`|Maintenance and test information returned by Task Schedule to the host side, including registers, hardware buffers, and bitmaps, when an AI Core error or notify wait timeout occurs.|
|`stackcore_tracer_{signal}_{tid}_{program_name}_{time}.txt`|A lightweight core file recorded when a host service process crashes, including stack frame addresses and base addresses. This file needs to be parsed using the asys tool. For details, see the [asys tool](https://gitcode.com/cann/oam-tools/blob/9.2.0/docs/en/asys/README.md).|
|`schedule_tracer_{object_name}.txt`|Trace information reported by modules such as Runtime and HCCL during the runtime process, recording the runtime information.|
|`schedule_tracer_{object_name}.bin`|Trace information reported by modules such as AICPU during the runtime process, recording the runtime information. It is stored in binary format and needs to be parsed using the asys tool. For details, see the [asys tool](https://gitcode.com/cann/oam-tools/blob/9.2.0/docs/en/asys/README.md).|

- Configure the delay for returning device-side logs to the host side through the environment variable **ASCEND\_LOG\_DEVICE\_FLUSH\_TIMEOUT**. For details, see [Environment Variable Reference](https://gitcode.com/cann/docs/blob/9.2.0/docs/en/env-vars/README.md).
- Through the environment variable **ASCEND\_TRACE\_RECORD\_NUM**, you can control the aging specification of the "`schedule_event_{Current process PID}_{Timestamp when the directory is generated}`" subdirectory under the "`$HOME/ascend/atrace/trace_{Process group PID}_{PID of the process that initially loads the trace dynamic library}_{Timestamp of the initial load of the trace dynamic library}/`" directory. For details, see [Environment Variable Reference](https://gitcode.com/cann/docs/blob/9.2.0/docs/en/env-vars/README.md).

The preceding directory is shared by all applications in the container or physical machine. New application processes are continuously added, and logs keep increasing. Therefore, you need to periodically clean up this directory (you can use the built-in logrotate to split logs). Otherwise, insufficient disk space may occur and affect normal service running.
