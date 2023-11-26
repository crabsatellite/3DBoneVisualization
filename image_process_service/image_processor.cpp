#include "image_processor.h"

ImageProcessor::ImageProcessor() {}

std::vector<double> ImageProcessor::findHistogramPeaks(vtkSmartPointer<vtkDICOMImageReader> reader) {
    int numBins = 256;
    double range[2];
    reader->GetOutput()->GetScalarRange(range);
    double binWidth = (range[1] - range[0]) / numBins;

    std::vector<int> histogram(numBins, 0);

    vtkImageData* imageData = reader->GetOutput();
    for (int z = 0; z < imageData->GetDimensions()[2]; ++z) {
        for (int y = 0; y < imageData->GetDimensions()[1]; ++y) {
            for (int x = 0; x < imageData->GetDimensions()[0]; ++x) {
                double pixelValue = imageData->GetScalarComponentAsDouble(x, y, z, 0);
                int bin = static_cast<int>((pixelValue - range[0]) / binWidth);
                if (bin >= 0 && bin < numBins) {
                    histogram[bin]++;
                }
            }
        }
    }

    std::vector<double> peaks;
    for (int i = 1; i < numBins - 1; ++i) {
        if (histogram[i] > histogram[i - 1] && histogram[i] > histogram[i + 1]) {
            peaks.push_back(range[0] + i * binWidth);
        }
    }

    return peaks;
}

vtkSmartPointer<vtkGenericOpenGLRenderWindow> ImageProcessor::processDICOM(const QString& directory) {
    vtkSmartPointer<vtkDICOMImageReader> reader = vtkSmartPointer<vtkDICOMImageReader>::New();
    reader->SetDirectoryName(directory.toStdString().c_str());
    reader->Update();

    std::vector<double> peaks = findHistogramPeaks(reader);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

    for (double peak : peaks) {
        vtkSmartPointer<vtkMarchingCubes> mc = vtkSmartPointer<vtkMarchingCubes>::New();
        mc->SetInputConnection(reader->GetOutputPort());
        mc->SetValue(0, peak);

        vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputConnection(mc->GetOutputPort());

        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        actor->SetMapper(mapper);

        renderer->AddActor(actor);
    }

    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    return renderWindow;
}
