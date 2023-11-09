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

Vtk Version:
8.2.0

#include "itkImageFileReader.h"
#include "itkBinaryMask3DMeshSource.h"
#include "itkImage.h"

int main(int argc, char \* argv[] )
{
if( argc < 3 )
{
std::cerr << "Usage: IsoSurfaceExtraction inputImageFile objectValue " << std::endl;
return EXIT_FAILURE;
}

const unsigned int Dimension = 3;
typedef unsigned char PixelType;
typedef itk::Image< PixelType, Dimension > ImageType;

typedef itk::ImageFileReader< ImageType > ReaderType;
ReaderType::Pointer reader = ReaderType::New();
reader->SetFileName( argv[1] );

try
{
reader->Update();
}
catch( itk::ExceptionObject & exp )
{
std::cerr << "Exception thrown while reading the input file " << std::endl;
std::cerr << exp << std::endl;
return EXIT_FAILURE;
}

typedef itk::Mesh<double> MeshType;

typedef itk::BinaryMask3DMeshSource< ImageType, MeshType > MeshSourceType;
MeshSourceType::Pointer meshSource = MeshSourceType::New();

const PixelType objectValue = static_cast<PixelType>( atof( argv[2] ) );
meshSource->SetObjectValue( objectValue );

meshSource->SetInput( reader->GetOutput() );

try
{
meshSource->Update();
}
catch( itk::ExceptionObject & exp )
{
std::cerr << "Exception thrown during Update() " << std::endl;
std::cerr << exp << std::endl;
return EXIT_FAILURE;
}

std::cout << "Nodes = " << meshSource->GetNumberOfNodes() << std::endl;
std::cout << "Cells = " << meshSource->GetNumberOfCells() << std::endl;

return EXIT_SUCCESS;
}
