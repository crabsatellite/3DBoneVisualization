#include "image_processor.h"
#include "itkGDCMImageIO.h"
#include "itkImageFileReader.h"
#include "itkBinaryMask3DMeshSource.h"
#include "itkImage.h"
#include <QDebug>

ImageProcessor::ImageProcessor() {
}

void ImageProcessor::processDicomFiles(const QStringList& fileNames) {
    for (const QString& fileName : fileNames) {
        processSingleDicomFile(fileName);
    }
}

void ImageProcessor::processSingleDicomFile(const QString& fileName) {
    qDebug() << "Processing DICOM file:" << fileName;

    const unsigned int Dimension = 3;
    typedef unsigned char  PixelType;
    typedef itk::Image< PixelType, Dimension >   ImageType;

    typedef itk::ImageFileReader< ImageType >    ReaderType;
    typedef itk::GDCMImageIO                     ImageIOType;
    ImageIOType::Pointer dicomIO = ImageIOType::New();

    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName( fileName.toStdString() );
    reader->SetImageIO( dicomIO );

    try {
        reader->Update();
    }
    catch( itk::ExceptionObject & exp ) {
        qCritical() << "Exception thrown while reading the DICOM file" << fileName;
        qCritical() << exp.GetDescription();
        return;
    }

    typedef itk::Mesh<double>                         MeshType;
    typedef itk::BinaryMask3DMeshSource< ImageType, MeshType >   MeshSourceType;
    MeshSourceType::Pointer meshSource = MeshSourceType::New();

    // Set the object value to a default or let it be configurable.
    // For example, assuming the object value represents a threshold.
    const PixelType objectValue = 1; // This value would typically come from the UI or config.
    meshSource->SetObjectValue( objectValue );

    meshSource->SetInput( reader->GetOutput() );

    try {
        meshSource->Update();
    }
    catch( itk::ExceptionObject & exp ) {
        qCritical() << "Exception thrown during mesh generation for the file" << fileName;
        qCritical() << exp.GetDescription();
        return;
    }

    qDebug() << "Nodes =" << meshSource->GetNumberOfNodes();
    qDebug() << "Cells =" << meshSource->GetNumberOfCells();

    // Here you would typically continue to work with the mesh,
    // such as displaying it or saving it to a file.
}

