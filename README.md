# 3DBoneVisualization

### QT Configuration

Add `QTDIR` to your environment variable settings as:

Step1. Add new variable: 
`QTDIR` -> `{YOUR_QT_DIRECTORY_TO_MSVC2017}`

for example: `C:\Qt\Qt5.9.1\5.9.1\msvc2017_64`

Step2. Add this variable to the path as:

`%QTDIR%\bin`


### Build ITK Library

Step1. Clone the ITK libary to local host:

`git clone -b v5.3.0 https://github.com/InsightSoftwareConsortium/ITK ITK-5.3.0`

Step2. Create `itk/src` and `itk/build` directory in your project:

2.1 Create a `itk/src` folder under your project directory:

e.g. You should have directory such as this: `${YOUR_PROJECT_DIRECTORY}/itk/src` available, and then move all the files from Step1 to here

2.2 Create a `itk/build` folder under your project directory:

e.g. You should have directory such as this: `${YOUR_PROJECT_DIRECTORY}/itk/build` available

Step3. Build the ITK with CMake GUI

Enter the source code and binaries directory accordingly as below:

Where is the source code: `${YOUR_PROJECT_DIRECTORY}/itk/src`

Where to build the binaries: `${YOUR_PROJECT_DIRECTORY}/itk/build`

Click `Configure`, after it is done, click `Generate`, this step should take a while to complete

Step4. Open the ITK project in visual studio and build

Step5. Add ITK_DIR to your environment variable settings as:

`ITK_DIR` -> `{YOUR_PROJECT_DIRECTORY}/itk/build`

Datasets:
https://github.com/datalad/example-dicom-structural

### Build VTK Library

Tutorial: https://www.youtube.com/watch?v=u5-Df1YlxCI&t=775s

Vtk Version: 8.2.0

