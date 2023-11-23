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
#include <vector>
#include <algorithm>

class ImageProcessor
{
public:
    ImageProcessor();
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> processDICOM(const QString& directory);
    std::vector<double> findHistogramPeaks(vtkSmartPointer<vtkDICOMImageReader> reader);

private:
    double determineThreshold(vtkSmartPointer<vtkDICOMImageReader> reader);
};

#endif // IMAGE_PROCESSOR_H
