#include "image_processor.h"
#include <QDebug>
#include <vtkSmartPointer.h>
#include <vtkDICOMImageReader.h>
#include <vtkMarchingCubes.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkNamedColors.h>

ImageProcessor::ImageProcessor() {
    // 初始化代码
}

void ImageProcessor::processDicomFiles(const QStringList& fileNames) {
    for (const QString& fileName : fileNames) {
        processSingleDicomFile(fileName);
    }
}

void ImageProcessor::processSingleDicomFile(const QString& fileName) {
    qDebug() << "Processing DICOM file:" << fileName;

   
}
