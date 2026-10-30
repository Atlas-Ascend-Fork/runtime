# aclrtMallocAttrValue

| Name| Description|
| --- | --- |
| moduleId | Int, module ID. You are advised to set this parameter to `33`, indicating the application. In this situation, the memory is allocated by the user application, which facilitates fault locating in maintenance and debugging scenarios.|
| deviceId | Int, device ID. If the device ID configured here is different from the device ID used for compute, an error is reported. You are advised not to set this parameter.|
| rsv[8] | List, reserved.|
