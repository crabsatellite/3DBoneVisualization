#include "image_processor.h"

ImageProcessor::ImageProcessor() {}

vtkSmartPointer<vtkGenericOpenGLRenderWindow> ImageProcessor::processDICOM(const QString& directory)
{
    vtkSmartPointer<vtkDICOMImageReader> reader = vtkSmartPointer<vtkDICOMImageReader>::New();
    reader->SetDirectoryName(directory.toStdString().c_str());
    reader->Update();

    double threshold = determineThreshold(reader);

    vtkSmartPointer<vtkMarchingCubes> mc = vtkSmartPointer<vtkMarchingCubes>::New();
    mc->SetInputConnection(reader->GetOutputPort());
    mc->SetValue(0, threshold);

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(mc->GetOutputPort());
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    return renderWindow;
}

double ImageProcessor::determineThreshold(vtkSmartPointer<vtkDICOMImageReader> reader)
{
    double range[2];
    reader->GetOutput()->GetScalarRange(range);
    return (range[0] + range[1]) / 2;
}
