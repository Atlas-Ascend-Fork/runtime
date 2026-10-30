# aclAippInfo

| Static AIPP Configuration| Definition|
| --- | --- |
| inputFormat | AIPP input image format (data of the `aclAippInputFormat` type)|
| srcImageSizeW | Source image width. For the YUV420SP_U8 format, the value must be an even number. Value range: [1, 4096]|
| srcImageSizeH | Source image height. For the YUV420SP_U8 format, the value must be an even number. Value range: [1, 4096]|
| cropSwitch | Cropping enable<br> 0: The image is not cropped. When `cropSwitch` is set to 0, `cropStartPosW`, `cropStartPosH`, `cropSizeW`, and `cropSizeH` are invalid.<br>`1`: The image is cropped.|
| loadStartPosW | Horizontal coordinate of the crop start For YUV420SP_U8, the value must be an even number. Value range: [0, 4095].|
| loadStartPosH | Vertical coordinate of the crop start For YUV420SP_U8, the value must be an even number. Value range: [0, 4095].|
| cropSizeW | Width of the crop ROI. For YUV420SP_U8, the value must be an even number. Value range: [1, 4096]|
| cropSizeH | Height of the crop ROI. For YUV420SP_U8, the value must be an even number. Value range: [1, 4096]|
| resizeSwitch | Whether to enable resize in AIPP. This parameter is reserved. Resize is not supported currently.|
| resizeOutputW | Width of the resized image|
| resizeOutputH | Height of the resized image|
| paddingSwitch | Whether to enable padding in AIPP|
| leftPaddingSize | W: left padding|
| rightPaddingSize | W: right padding|
| topPaddingSize | H: top padding|
| bottomPaddingSize | H: bottom padding|
| cscSwitch | Whether to enable CSC in static AIPP|
| rbuvSwapSwitch | Whether to enable R/B or U/V channel swap before CSC|
| axSwapSwitch | Whether to enable RGBA->ARGB and YUVA->AYUV channel swap before CSC|
| singleLineMode | Single line mode switch (in this mode, only the first line after crop is processed.)|
| matrixR0C0 | 3 x 3 CSC matrix element|
| matrixR0C1 | 3 x 3 CSC matrix element|
| matrixR0C2 | 3 x 3 CSC matrix element|
| matrixR1C0 | 3 x 3 CSC matrix element|
| matrixR1C1 | 3 x 3 CSC matrix element|
| matrixR1C2 | 3 x 3 CSC matrix element|
| matrixR2C0 | 3 x 3 CSC matrix element|
| matrixR2C1 | 3 x 3 CSC matrix element|
| matrixR2C2 | 3 x 3 CSC matrix element|
| outputBias0 | Output bias for RGB2YUV conversion|
| outputBias1 | Output bias for RGB2YUV conversion|
| outputBias2 | Output bias for RGB2YUV conversion|
| inputBias0 | Input bias for YUV2RGB conversion|
| inputBias1 | Input bias for YUV2RGB conversion|
| inputBias2 | Input bias for YUV2RGB conversion|
| meanChn0 | Mean value of each channel.|
| meanChn1 | Mean value of each channel.|
| meanChn2 | Mean value of each channel.|
| meanChn3 | Mean value of each channel.|
| minChn0 | Minimum value of each channel.|
| minChn1 | Minimum value of each channel.|
| minChn2 | Minimum value of each channel.|
| minChn3 | Minimum value of each channel.|
| varReciChn0 | Variance value of each channel|
| varReciChn1 | Variance value of each channel|
| varReciChn2 | Variance value of each channel|
| varReciChn3 | Variance value of each channel|
| srcFormat | Source format (data of the `aclFormat` type)|
| srcDatatype | Source data type (data of the `aclDataType` type)|
| srcDimNum | Source dimension count.|
| shapeCount | Number of batch/image size profiles in the dynamic shape scenario|
| outDims | Output data dimension (data of the `aclAippDims` type)|
| aippExtend | Reserved parameter.|
