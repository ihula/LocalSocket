#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class HLocalServer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void openCamera(int client, QString cameraname);
    void cameraCapture(int client, QString filename);
    void closeCamera(int client);

private slots:
    void readMessage(int client, int cmd, QString arg);
    void on_btnSend1_clicked();
    void on_btnSend2_clicked();

    void on_btnCapture1_clicked();

    void on_btnCapture2_clicked();

    void on_btnClose1_clicked();

    void on_btnClose2_clicked();

private:
    HLocalServer *server;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
