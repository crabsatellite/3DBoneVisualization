# DICOMImage3DBuilder

[Demo Video](https://personalwebpage-videos.s3.us-east-2.amazonaws.com/DICOMImage3DBuilder_demo.mp4)

## Requirements

- VTK Version: 8.2.0
- Qt Version: 5.9.0

## Overview

DICOMImage3DBuilder is a specialized tool for converting a sequence of DICOM images into a 3D visualization using the VTK library. This tool allows for an enhanced analysis of DICOM image data, providing a more detailed and spatial understanding of the images.

## How Does It Work?

Reading following functions to understand how the tool works:

### `findHistogramPeaks` Function

This function is designed to identify histogram peaks within a sequence of DICOM images. It works by:

- Defining the total number of bins for the histogram.
- Calculating the width of each bin based on the value range of the image data.
- Assigning each pixel value to the corresponding bin.
- Identifying peaks by comparing the frequency of each bin with its neighbors.
  The function ultimately returns a vector of values representing these peaks, which are key to understanding the data distribution in the DICOM images.

### `processDICOM` Function

The `processDICOM` function processes DICOM images for 3D rendering. Its steps include:

- Reading a directory of DICOM images.
- Using `findHistogramPeaks` to find histogram peaks in the image data.
- Applying the Marching Cubes algorithm for each peak to create a 3D surface representation.
- Rendering each 3D model separately using a vtkRenderer, allowing detailed visual representation of the DICOM data in 3D space.

## Building VTK Library

For setting up the VTK library, please refer to the following tutorial:
[Tutorial on YouTube](https://www.youtube.com/watch?v=u5-Df1YlxCI&t=775s)

## Contributing

If you want to contribute to this project and make it better with new ideas, your pull request is very welcomed.

Eg. You can improve the existing UI or add new features to the tool.

If you find any issue just put it in the repository issue section.

## License

MIT License

## Other Information

The project currently is using a seperated OpenGL library because of the potential future plans.

But it is not necessary for the core functions of the project.

You may see a colorful cube after launch the app, which is a place holder, click the upload to select the folder with dicom images. 
