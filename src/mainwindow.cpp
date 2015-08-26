#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    inputBrowseButton = new DropDownButton(this);
    // Add the drop down widget here
    ui->horizontalLayout->removeWidget(ui->inputPushButton);
    ui->inputPushButton->close();
    ui->horizontalLayout->addWidget(inputBrowseButton);
    ui->horizontalLayout->update();

    connect(ui->outputPushButton,SIGNAL(clicked()),this,SLOT(onOutputBrowseButtonClick()));
    connect(ui->encryptPushButton,SIGNAL(clicked()),this,SLOT(onEncryptButtonClick()));
    connect(this,SIGNAL(logTextChanged(QString)),this,SLOT(onLogTextChanged(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOutputBrowseButtonClick() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save file"), "/");
    ui->outputLineEdit->setText(fileName);
}

void MainWindow::onEncryptButtonClick() {
    QString input = ui->inputLineEdit->text();
    QString output = ui->outputLineEdit->text();

    emit onLogTextChanged(QString("Compressing files..."));

    // Start the thread to compress the files
    Compress *compressRunner = new Compress(this, input, output);
    compressRunner->setAutoDelete(false);
    QThreadPool::globalInstance()->start(compressRunner);
}

void MainWindow::onLogTextChanged(QString log) {
    qDebug() << "Caught LogTextChanged signal";
    // Add the new log line to logText edit field
    ui->logText->moveCursor(QTextCursor::End);
    ui->logText->insertPlainText(log + "\n");
}

void MainWindow::onFileBrowseButtonClick() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/" );
    ui->inputLineEdit->setText(fileName);
}

void MainWindow::onFolderBrowseButtonClick() {
    QString folderName = QFileDialog::getExistingDirectory(this, tr("Open Folder"), "/" );
    ui->inputLineEdit->setText(folderName);
}

