#include "image_processor.h"
#include <QDebug>
#include <vtkSmartPointer.h>

ImageProcessor::ImageProcessor() {
}

void ImageProcessor::processDicomFiles(const QStringList& fileNames) {
    for (const QString& fileName : fileNames) {
        processSingleDicomFile(fileName);
    }
}

void ImageProcessor::processSingleDicomFile(const QString& fileName) {
    qDebug() << "Processing DICOM file:" << fileName;

   
}
