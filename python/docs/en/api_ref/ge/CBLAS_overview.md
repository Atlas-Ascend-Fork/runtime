# Overview

The APIs described in this section implement matrix-matrix or matrix-vector multiplication. The built-in General Matrix Multiply (GEMM) operator has been encapsulated in these APIs. For details about the API call sequence, see [API Calling Process](https://www.hiascend.com/document/detail/en/CANNCommunityEdition/latest/others/acldevg/aclpythondevg_0069.html).

According to the API calling process, before using the APIs in this section, use Ascend Tensor Compiler (ATC) to build the operator description information (including the input and output tensor descriptions and operator attributes) of the built-in GEMM operator into an \*.om AI processor-adapted offline model to validate the execution result of the GEMM operator.

All CBLAS APIs described in this section are asynchronous. The API call delivers a task rather than executes a task. After this API is called, call the synchronization API (for example, `acl.rt.synchronize_stream`) to ensure that the task is complete.
