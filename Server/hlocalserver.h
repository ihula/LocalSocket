#ifndef HLOCALSERVER_H
#define HLOCALSERVER_H

#include <QObject>

#define MAX_CONNECT_NUM 30

class QProcess;
class QLocalServer;
class QLocalSocket;

class HLocalServer : public QObject
{
    Q_OBJECT
public:
    explicit HLocalServer(QObject *parent = 0);
    ~HLocalServer();

    int init(const QString &servername);
    void sendMessage(int client, int cmd, QString arg);
    void startProcess(QString filename);

signals:
    void readMessage(int client, int cmd, QString arg);

public slots:
    void newConnection();
    void readyRead();
    void disconnected();

private:
    QLocalServer *server;
    QLocalSocket *clients[MAX_CONNECT_NUM];
    int cmd;
    QString args;

    // 判断是否有一个同名的服务器在运行
    int isServerRun(const QString & servername);
    void parseMessage(QString message);
};

#endif // HLOCALSOCKETSERVER_H
