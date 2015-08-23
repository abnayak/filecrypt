#include "compress.h"

Compress::Compress() {}

bool Compress::compressFile(QString inputFile, QString output) {
    return JlCompress::compressFile(output,inputFile);
}

bool Compress::compressDir(QString inputDir, QString output) {
    return JlCompress::compressDir(output, inputDir);
}

bool Compress::compressFiles(QStringList inputFiles, QString output) {
    return JlCompress::compressFiles(output, inputFiles);
}
