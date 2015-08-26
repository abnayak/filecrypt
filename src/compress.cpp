#include "compress.h"

Compress::Compress(QObject *parent, QString input, QString output) {
    this->parent = parent;
    this->input = input;
    this->output = output;
}

bool Compress::compressFile(QString inputFile, QString output) {
    return JlCompress::compressFile(output,inputFile);
}

bool Compress::compressDir(QString inputDir, QString output) {
    return JlCompress::compressDir(output, inputDir);
}

bool Compress::compressFiles(QStringList inputFiles, QString output) {
    return JlCompress::compressFiles(output, inputFiles);
}

void Compress::run() {
    QFileInfo fileInfo(input);

    if(fileInfo.exists()) {
        qDebug() << "File: " << input << " exists.";
        printLog(input + " exists.");

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
    printLog("Finished compression.");
}

void Compress::printLog(QString log) {
    QMetaObject::invokeMethod(parent, "logTextChanged", Qt::DirectConnection, Q_ARG(QString, log));
}
