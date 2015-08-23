#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QFileDialog>

class FileDialog : public QFileDialog
{
public:
    FileDialog(QObject *parent);
};

#endif // FILEDIALOG_H
