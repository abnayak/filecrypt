#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QListView>
#include <QTreeView>
#include <QThreadPool>

#include <compress.h>
#include <dropdownbutton.h>
#include <botanwrapper.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    // Dropdown file/dir browse button
    DropDownButton *inputBrowseButton;
    // Botan objec to encrypt the file
    BotanWrapper *botan;
    int validateFields();
    void beginCompress();
    void beginEncryption();
    void decrypt();
    void deleteFile(QString file);

public slots:
    void onOutputBrowseButtonClick();
    void onEncryptButtonClick();
    void onLogTextChanged(QString);
    void onDecryptCheckBoxSelect();
    void onCompressionFinished();
    void onEncryptionFinished();

    // Following two slots are being called by DropDownButton
    void onFileBrowseButtonClick();
    void onFolderBrowseButtonClick();

signals:
    void logTextChanged(QString);
};

#endif // MAINWINDOW_H
