#ifndef COMPRESS_H
#define COMPRESS_H

#include <QString>
#include <JlCompress.h>

class Compress
{
public:
    Compress();
    bool compressFile(QString inputFile, QString output);
    bool compressDir(QString inputDir, QString output);
    bool compressFiles(QStringList inputFiles, QString output);
};

#endif // COMPRESS_H
