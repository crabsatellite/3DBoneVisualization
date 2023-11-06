# 3DBoneVisualization

### Build ITK Library

Step1. Clone the ITK libary to local host:

`git clone -b v5.3.0 https://github.com/InsightSoftwareConsortium/ITK ITK-5.3.0`

Step2. Create `itk/src` and `itk/bin` directory in your project:

2.1 Create a `itk/src` folder under your project directory:

e.g. You should have directory such as this: `${YOUR_PROJECT_DIRECTORY}/itk/src` available, and then move all the files from Step1 to here

2.2 Create a `itk/bin` folder under your project directory:

e.g. You should have directory such as this: `${YOUR_PROJECT_DIRECTORY}/itk/bin` available

Step3. Build the ITK with CMake GUI

Enter the source code and binaries directory accordingly as below:

Where is the source code: `${YOUR_PROJECT_DIRECTORY}/itk/src`

Where to build the binaries: `${YOUR_PROJECT_DIRECTORY}/itk/bin`

Click `Configure`, after it is done, click `Generate`, this step should take a while to complete

Step4. Open the project with Qt creator, compile the project and run !

Datasets:
https://github.com/datalad/example-dicom-structural
