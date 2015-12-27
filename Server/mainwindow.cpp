#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QProcess>
#include "hlocalserver.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new HLocalServer(this);
    server->init("localserver-Hula-Camera");
    connect(server, &HLocalServer::readMessage, this, &MainWindow::readMessage);

    server->startProcess("./ClientCamera");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openCamera(int client, QString cameraname)
{
    server->sendMessage(client, 1, cameraname);
}

void MainWindow::cameraCapture(int client, QString filename)
{
    server->sendMessage(client, 2, filename);
}

void MainWindow::closeCamera(int client)
{
    server->sendMessage(client, 3, "");
}

void MainWindow::readMessage(int client, int cmd, QString arg)
{
    ui->label->setText(QString::number(client) + "\n" +
                       QString::number(cmd) + "\n" + arg);
}

void MainWindow::on_btnSend1_clicked()
{
    openCamera(0, ui->edtCamera->text());
}

void MainWindow::on_btnSend2_clicked()
{
    openCamera(1, ui->edtCamera->text());
}

void MainWindow::on_btnCapture1_clicked()
{
    cameraCapture(0, ui->edtFile->text());
}

void MainWindow::on_btnCapture2_clicked()
{
    cameraCapture(1, ui->edtFile->text());
}

void MainWindow::on_btnClose1_clicked()
{
    closeCamera(0);
}

void MainWindow::on_btnClose2_clicked()
{
    closeCamera(1);
}
