#include "hlocalsocket.h"

#include <QDebug>
#include <QLocalSocket>
#include <QTimer>


HLocalSocket::HLocalSocket(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    timer->setInterval(300);
    connect(timer, &QTimer::timeout, this, &HLocalSocket::timeoutConnect);

    socket = new QLocalSocket(this);
    connect(socket, &QLocalSocket::readyRead, this, &HLocalSocket::readMessage);
    connect(socket, &QLocalSocket::connected, this, &HLocalSocket::connected);
    connect(socket, &QLocalSocket::disconnected, this, &HLocalSocket::disconnected);
    connect(socket,
            static_cast<void (QLocalSocket::*)(QLocalSocket::LocalSocketError)>
            (&QLocalSocket::error),
            this, &HLocalSocket::socketErroring);
}

HLocalSocket::~HLocalSocket()
{
    delete socket;
}

void HLocalSocket::init(QString server)
{
    serverName = server;
    connectServer();
}

void HLocalSocket::timeoutConnect()
{
    connectServer();
}

void HLocalSocket::sendMessage(QString msg)
{
    QTextStream txtStream(socket);
    txtStream << msg;
    txtStream.flush();
    socket->waitForBytesWritten();
    qDebug() << "send:" + msg;
}

void HLocalSocket::readMessage()
{
    QTextStream txtStream(socket);
    QString message = txtStream.readAll();
    emit newMessage(message);
    qDebug() << "read:" + message;
}

// mac OS 下服务器断开后会触发此事件，不会触发 disconnected 事件
void HLocalSocket::socketErroring(QLocalSocket::LocalSocketError socketError)
{
    Q_UNUSED(socketError);
    if (!timer->isActive())
        timer->start();
}

void HLocalSocket::connected()
{
    sendMessage("0");
    qDebug() << "Connected.";
}

// windows 下服务器断开后会触发此事件，不会触发 socketError事件
void HLocalSocket::disconnected()
{
    if (!timer->isActive())
        timer->start();
}

void HLocalSocket::connectServer()
{
    timer->stop();
    socket->abort();
    qDebug() << "Connecting...";
    socket->connectToServer(serverName);
}

