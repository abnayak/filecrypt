#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow) {
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
    connect(ui->decryptCheckBox,SIGNAL(clicked()),this,SLOT(onDecryptCheckBoxSelect()));

    // setup the threads
    zip = new Zip();
    zip->moveToThread(&thread);

    connect(this,SIGNAL(startCompression(QString,QString)),zip, SLOT(compress(QString,QString)));
    connect(this,SIGNAL(startUncompression(QString,QString)),zip,SLOT(deCompress(QString,QString)));
    connect(zip,SIGNAL(compressionFinished()),this,SLOT(onCompressionFinished()));
    connect(zip,SIGNAL(inflationFinished()),this, SLOT(onDecompressionFinished()));
    connect(zip,SIGNAL(logTextChanged(QString)),this,SLOT(onLogTextChanged(QString)));

    // Setup the encryption objects
    botan = new BotanWrapper();
    botan->moveToThread(&thread);

    connect(this,SIGNAL(startEncryption(QString,QString)),botan,SLOT(EncryptFile(QString,QString)));
    connect(this,SIGNAL(startDeCryption(QString,QString)),botan,SLOT(DecryptFile(QString,QString)));
    connect(botan,SIGNAL(EncryptionFinished()),this,SLOT(onEncryptionFinished()));
    connect(botan,SIGNAL(DecryptionFinished()),this,SLOT(onDecryptionFinished()));
    connect(botan,SIGNAL(logTextChanged(QString)),this,SLOT(onLogTextChanged(QString)));

    // Start the thread
    thread.start();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onOutputBrowseButtonClick() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save file"), "/");
    ui->outputLineEdit->setText(fileName);
}

void MainWindow::onEncryptButtonClick() {
    // validate the input fields
    if (validateFields()) {
        return;
    }

    if (ui->decryptCheckBox->checkState() == Qt::Checked ) {
        decrypt();
    } else {
        encrypt();
    }
}

void MainWindow::encrypt() {
    QString source = ui->inputLineEdit->text();
    QString destination = ui->outputLineEdit->text();
    QString zippedFile = destination + ".zip";

    // Start the thread to compress the files
    emit onLogTextChanged(QString("Compressing files..."));

    // Start the compression
    emit startCompression(source,zippedFile);
}

void MainWindow::onCompressionFinished() {
    // Invoke encryption after the compression
    beginEncryption();
}

void MainWindow::beginEncryption() {
    qDebug() << "Enter MainWindow::beginEncryption";
    QString destination = ui->outputLineEdit->text();
    QString password = ui->password->text();
    QString zippedFile = destination + ".zip";

    // Start the encryption
    emit onLogTextChanged(QString("Encrypting the file..."));


    qDebug() << "Password: " << password;

    botan->setPassword(password);
    botan->setSalt(password+password);

    //botan->EncryptFile(zippedFile,destination);
    emit startEncryption(zippedFile,destination);

    qDebug() << "Exiting MainWindow::beginEncryption";
}

void MainWindow::onEncryptionFinished() {
    QString destination = ui->outputLineEdit->text();
    QString password = ui->password->text();
    QString zippedFile = destination + ".zip";

    //delete(botan);
    emit onLogTextChanged(QString("Encryption finished..."));

    // Delete the encrypted file
    deleteFile(zippedFile);
}

void MainWindow::decrypt() {
    QString source = ui->inputLineEdit->text();
    QString destination = ui->outputLineEdit->text();
    QString password = ui->password->text();

    // Start the decryption
    emit onLogTextChanged(QString("Decrypting the file..."));

    botan->setPassword(password);
    botan->setSalt(password+password);

    emit startDeCryption(source, destination+".temp");
}

void MainWindow::onDecryptionFinished() {
    emit onLogTextChanged(QString("Decryption finished..."));
    QString destination = ui->outputLineEdit->text();
    // Start the inflation
    emit startUncompression(destination+".temp", destination);
}

void MainWindow::onDecompressionFinished() {
    QString const destination = ui->outputLineEdit->text();
    deleteFile(destination+".temp");
    emit onLogTextChanged(QString("Restored the file..."));
}

void MainWindow::deleteFile(QString fileName) {
    QDir dir;
    if (!dir.remove(fileName)) {
        emit onLogTextChanged(QString("Unable to remove the file " +fileName));
    }
}

void MainWindow::onLogTextChanged(QString log) {
    qDebug() << "Caught LogTextChanged signal";
    // Add the new log line to logText edit field
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

void MainWindow::onDecryptCheckBoxSelect() {
    if (ui->decryptCheckBox->checkState() != Qt::Unchecked) {
        ui->confirmPassword->setEnabled(false);
        ui->encryptPushButton->setText(tr("Decrypt"));
        ui->passwordLabel->setText(tr("Password to decrypt:"));
    } else {
        ui->confirmPassword->setEnabled(true);
        ui->encryptPushButton->setText(tr("Encrypt"));
        ui->passwordLabel->setText(tr("Password"));
    }
}


/*
 * returns 1 for failure and 0 if passed
 */
int MainWindow::validateFields() {
    QString input = ui->inputLineEdit->text();
    QString output = ui->outputLineEdit->text();
    QString password = ui->password->text();
    QString confirmPassword = ui->confirmPassword->text();
    QFileInfo inputFileInfo(input);
    QFileInfo outputFileInfo(output);

    if (!ui->decryptCheckBox->isChecked()) {
        // Validate the input and output file locations
        if (!inputFileInfo.exists() || !inputFileInfo.isReadable()) {
            emit onLogTextChanged(QString("Invalid input file, Please check again."));
            return 1;
        }

//        if (!outputFileInfo.isWritable()) {
//            emit onLogTextChanged(QString("Can't write at the destination location, Please choose another destination file"));
//            return 1;
//        }

        if (password.isNull() || confirmPassword.isNull()) {
            emit onLogTextChanged(QString("Password field is empty"));
            return 1;
        }

        if (password != confirmPassword) {
            emit onLogTextChanged(QString("Passwords don't match, Please reenter."));
            return 1;
        }
        return 0;
    } else {
        if (!inputFileInfo.exists() || !inputFileInfo.isReadable()) {
            emit onLogTextChanged(QString("Invalid input file, Please check again."));
            return 1;
        }

//        if (!outputFileInfo.isWritable()) {
//            emit onLogTextChanged(QString("Can't write at the destination location, Please choose another destination file"));
//            return 1;
//        }

        if (password.isNull() || confirmPassword.isNull()) {
            emit onLogTextChanged(QString("Password field is empty"));
            return 1;
        }

        return 0;
    }
}
