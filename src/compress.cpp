#include "compress.h"

Zip::Zip() {
}

Zip::~Zip() {
}

bool Zip::compressFile(QString inputFile, QString output) {
    return JlCompress::compressFile(output,inputFile);
}

bool Zip::compressDir(QString inputDir, QString output) {
    return JlCompress::compressDir(output, inputDir);
}

bool Zip::compressFiles(QStringList inputFiles, QString output) {
    return JlCompress::compressFiles(output, inputFiles);
}

void Zip::compress(QString input, QString output) {
    QFileInfo fileInfo(input);

    if(fileInfo.exists()) {
        qDebug() << "File: " << input << " exists.";

        // If the file is a directory
        if(fileInfo.isDir()) {
            if(compressDir(input,output)) {
                printLog("Successfully compressed the directory.");
            } else {
                printLog("Failed to compress the directory. Exiting...");
            }
        } else {
            if(compressFile(input,output)) {
                printLog("Successfully compressed the file.");
            } else {
                printLog("Failed to compresse the file. Exiting...");
            }
        }
    } else {
        qDebug() << "File: " << input << " does not exists.";
        printLog("File: " + input + " does not exist. Choose another file");
    }

    // Send signal to parent about compression finish
    //QMetaObject::invokeMethod(parent, "onCompressionFinished", Qt::QueuedConnection);
    emit compressionFinished();
}

// Extract the file
void Zip::deCompress(QString input, QString output) {
    JlCompress::extractDir(input, output);
    emit inflationFinished();
}

void Zip::printLog(QString log) {
    //QMetaObject::invokeMethod(parent, fun, Qt::QueuedConnection, Q_ARG(QString, log));
    emit logTextChanged(log);
}
