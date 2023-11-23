#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include <vtkSmartPointer.h>
#include <vtkDICOMImageReader.h>
#include <vtkMarchingCubes.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <QString>
#include <vtkImageData.h>

class ImageProcessor
{
public:
    ImageProcessor();
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> processDICOM(const QString& directory);
    std::vector<double> findHistogramPeaks(vtkSmartPointer<vtkDICOMImageReader> reader);

private:
};

#endif // IMAGE_PROCESSOR_H
