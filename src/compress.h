#ifndef COMPRESS_H
#define COMPRESS_H

#include <QString>
#include <JlCompress.h>
#include <QRunnable>
#include <QDebug>
#include <QMainWindow>
#include <mainwindow.h>
#include <QThread>

class Compress:public QObject {
private:
    QObject *parent;
    QString input;
    QString output;
    void printLog(QString);
    QThread thread;
public:
    Compress(QObject *parent, QString input, QString output);
    ~Compress();
    void run();
    bool compressFile(QString inputFile, QString output);
    bool compressDir(QString inputDir, QString output);
    bool compressFiles(QStringList inputFiles, QString output);
};

#endif // COMPRESS_H
