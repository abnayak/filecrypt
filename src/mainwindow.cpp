#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->inputPushButton,SIGNAL(clicked()),this,SLOT(onInputBrowseButtonClick()));
    connect(ui->outputPushButton,SIGNAL(clicked()),this,SLOT(onOutputBrowseButtonClick()));
    connect(ui->encryptPushButton,SIGNAL(clicked()),this,SLOT(onEncryptButtonClieck()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onInputBrowseButtonClick() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "/" );
    ui->inputLineEdit->setText(fileName);

//    QListView *l = w.findChild<QListView*>("listView");
//    if (l) {
//        l->setSelectionMode(QAbstractItemView::MultiSelection);
//    }
//    QTreeView *t = w.findChild<QTreeView*>();
//    if (t) {
//        t->setSelectionMode(QAbstractItemView::MultiSelection);
//    }
//    w.exec();
}

void MainWindow::onOutputBrowseButtonClick() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save file"), "/");
    ui->outputLineEdit->setText(fileName);
}

void MainWindow::onEncryptButtonClieck() {
    Compress compress;
    QFile qfile;
}
