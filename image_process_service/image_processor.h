#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include <QStringList>

class ImageProcessor {
public:
    ImageProcessor();
    void processDicomFiles(const QStringList& fileNames);

private:
    void processSingleDicomFile(const QString& fileName);
};

#endif // IMAGE_PROCESSOR_H
