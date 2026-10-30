# aclFormat

The available dimensions are the batch size (N), height (H), width (W), channels (C), and depth (D).

| Data Format| Description|
| --- | --- |
| ACL_FORMAT_UNDEFINED = -1 | Unknown data type (default)|
| ACL_FORMAT_NCHW = 0 | NCHW layout format.|
| ACL_FORMAT_NHWC = 1 | NHWC layout format.|
| ACL_FORMAT_ND = 2 | Indicates that any format is supported. Except for operators that process a single input on itself such as `Square` and `Tanh`, other operators must be used with caution.|
| ACL_FORMAT_NC1HWC0 = 3 | 5D data layout format. `C0` is strongly related to the microarchitecture. This value is identical to the size of the cube unit, for example, 16. `C1` is obtained by slicing the C dimension based on `C0`: `C1=C/C0`. If the result is not divisible, the last part of the data must be padded to `C0`.|
| ACL_FORMAT_FRACTAL_Z = 4 | Layout format of convolution weights.|
| ACL_FORMAT_NC1HWC0_C04 = 12 | 5D data layout format. `C0` is fixed to 4. `C1` is obtained by slicing the C dimension based on `C0`: `C1=C/C0`. If the result is not divisible, the last part of the data must be padded to `C0`. It is not supported by the current version.|
| ACL_FORMAT_HWCN = 16 | HWCN layout format.|
| ACL_FORMAT_NDHWC = 27 | NDHWC layout format. For 3D images, a layout format with a depth (D) dimension must be used.|
| ACL_FORMAT_FRACTAL_NZ = 29 | Internal layout format, which currently does not need to be used by users.|
| ACL_FORMAT_NCDHW = 30 | NCDHW layout format. For 3D images, a layout format with a depth (D) dimension must be used.|
| ACL_FORMAT_NDC1HWC0 = 32 | 6D data layout format. Compared with `NC1HWC0`, only a depth (D) dimension is added.|
| ACL_FRACTAL_Z_3D = 33 | 3D convolution weight layout format. Operators such as `Conv3D`, `MaxPool3D`, and `AvgPool3D` must be expressed in this layout format.|
| ACL_FORMAT_NC = 35 | 2D data layout format.|
| ACL_FORMAT_NCL = 47 | 3D data layout format.|
