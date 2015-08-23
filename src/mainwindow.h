#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QListView>
#include <QTreeView>

#include <compress.h>

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
public slots:
    void onInputBrowseButtonClick();
    void onOutputBrowseButtonClick();
    void onEncryptButtonClieck();
};

#endif // MAINWINDOW_H
