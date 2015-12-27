#ifndef HMANAGER_H
#define HMANAGER_H

#include <QObject>
#include <QStringList>

class HCamera;
class HLocalSocket;

/*
 * message format: command(int) + :: + arguments(string)
 * arguments separator: ``
 * return success: command + :: + 0
 * return fail: command + :: + 1
 * unknown command return: 404
 */
class HManager : public QObject
{
    Q_OBJECT
public:
    explicit HManager(QObject *parent = 0);
    ~HManager();

    void connectServer(QString servername);
    void parseMessage(QString message);
    void sendMessage(int cmd, QString arg);
    void openCamera(QString cameraname);
    void cameraCapture(QString &filename);
    void closeCamera();

signals:

public slots:
    void readMessage(QString message);
    void cameraCaptured();

private:
    HCamera *camera;
    HLocalSocket *localSocket;

    int cmd;
    QStringList args;
};

#endif // HMANAGER_H
