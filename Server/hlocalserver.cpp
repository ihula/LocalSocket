#include <QLocalServer>
#include <QLocalSocket>
#include <QProcess>

#include "hlocalserver.h"

HLocalServer::HLocalServer(QObject *parent) : QObject(parent)
{
    server = NULL;
    for (int i = 0; i < MAX_CONNECT_NUM; i++)
        clients[i] = NULL;
}

HLocalServer::~HLocalServer()
{
    if (server != NULL)
        delete server;
}

int HLocalServer::init(const QString &servername)
{
    if (isServerRun(servername))
        return 1;

    for (int i = 0; i < MAX_CONNECT_NUM; i++)
        clients[i] = NULL;

    // 先移除原来存在的,servername已经存在就会listen失败
    QLocalServer::removeServer(servername);

    server = new QLocalServer;
    server->listen(servername);
    connect(server, &QLocalServer::newConnection,
            this, &HLocalServer::newConnection);

    return 0;
}

void HLocalServer::newConnection()
{
    for(int i = 0; i < MAX_CONNECT_NUM; i++)
    {
        if (clients[i] == NULL)
        {
            clients[i] = server->nextPendingConnection();
            connect(clients[i], &QLocalSocket::readyRead,
                    this, &HLocalServer::readyRead);
            connect(clients[i], &QLocalSocket::disconnected,
                    this, &HLocalServer::disconnected);
            break;
        }
    }
}

void HLocalServer::readyRead()
{
    QLocalSocket *client = static_cast<QLocalSocket *>(sender());
    if (!client)
        return;

    int i;
    for (i = 0; i < MAX_CONNECT_NUM; i++)
    {
        if (clients[i] == client)
            break;
    }

    QTextStream txtStream(client);
    QString message = txtStream.readAll();
    parseMessage(message);
    emit readMessage(i, cmd, args);
}

void HLocalServer::sendMessage(int client, int cmd, QString arg)
{
    if ((client < 0) || (client >= MAX_CONNECT_NUM))
        return;
    if (clients[client] == NULL)
        return;

    QString message;
    if (arg.isEmpty() || arg.isNull())
        message = QString::number(cmd);
    else
        message = QString::number(cmd) + "::" + arg;
    QTextStream txtStream(clients[client]);
    txtStream << message;
    txtStream.flush();
    clients[client]->waitForBytesWritten();
}

void HLocalServer::startProcess(QString filename)
{
    QProcess *process = new QProcess(this);
    process->start(filename);
}

void HLocalServer::disconnected()
{
    QLocalSocket *client = static_cast<QLocalSocket *>(sender());
    for (int i = 0; i < MAX_CONNECT_NUM; i++)
    {
        if (clients[i] == client)
            clients[i] = NULL;
    }
}

int HLocalServer::isServerRun(const QString &servername)
{
    // 用一个localsocket去连一下,如果能连上就说明有一个在运行了
    QLocalSocket ls;
    ls.connectToServer(servername);
    if (ls.waitForConnected(1000))
    {
        ls.disconnectFromServer();
        ls.close();
        return 1;
    }
    return 0;
}

void HLocalServer::parseMessage(QString message)
{
    int index = message.indexOf("::");
    if (index < 0)
    {
        cmd = -1;
        args = "";
    }
    else
    {
        cmd = message.left(index).toInt();
        args = message.right(message.length() - index - 2);
    }
}

