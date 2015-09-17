#ifndef COMPRESS_H
#define COMPRESS_H

#include <QString>
#include <QStringList>
#include <JlCompress.h>
#include <QRunnable>
#include <QDebug>
#include <QMainWindow>
#include <mainwindow.h>
#include <QThread>
#include <QObject>
#include <QMetaObject>

class Zip:public QObject {
    Q_OBJECT
private:
    QObject *parent;
    void printLog(QString);
    bool compressFile(QString inputFile, QString output);
    bool compressDir(QString inputDir, QString output);
    bool compressFiles(QStringList inputFiles, QString output);

public:
    Zip();
    ~Zip();

public slots:
    void compress(QString input, QString output);
    QStringList deCompress(QString input, QString output);

signals:
    void compressionFinished();
    void deCompressionFinished();
    void logTextChanged(QString);
};

#endif // COMPRESS_H
