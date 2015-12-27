#ifndef CLIENTHOST_H
#define CLIENTHOST_H

#include <QObject>
#include <QLocalSocket>

class QTimer;
class HCamera;

class HLocalSocket : public QObject
{
    Q_OBJECT
public:
    explicit HLocalSocket(QObject *parent = 0);
    ~HLocalSocket();

    void init(QString server);


signals:
     void newMessage(QString message);

public slots:
    void timeoutConnect();
    void sendMessage(QString msg);
    void readMessage();
    void socketErroring(QLocalSocket::LocalSocketError socketError);
    void connected();
    void disconnected();

private:
    QTimer *timer;
    QLocalSocket *socket;
    HCamera *imgCamera;
    QString serverName;
    int cmd;
    QString arg;

    void connectServer();
};

#endif // CLIENTHOST_H
