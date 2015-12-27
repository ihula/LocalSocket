#include "hmanager.h"

#include "hcamera.h"
#include "hlocalsocket.h"

HManager::HManager(QObject *parent) : QObject(parent)
{
    camera = new HCamera(this);

    localSocket = new HLocalSocket(this);
    connect(localSocket, &HLocalSocket::newMessage,
            this, &HManager::readMessage);
    connect(camera, &HCamera::cameraCaptured, this, &HManager::cameraCaptured);
}

HManager::~HManager()
{
    if (camera->isOpenCamera())
        camera->closeCamera();
    delete camera;
    delete localSocket;
}

void HManager::connectServer(QString servername)
{
    localSocket->init(servername);
}

void HManager::parseMessage(QString message)
{
    QString arg;
    int index = message.indexOf("::");
    if (index < 0)
    {
        cmd = message.toInt();
        arg = "";
    }
    else
    {
        cmd = message.left(index).toInt();
        arg = message.right(message.length() - index - 2);
    }
    args.clear();
    args = arg.split("``");
    if (args.size() == 0)
        args.append("");
}

void HManager::sendMessage(int cmd, QString arg)
{
    QString message;
    if (arg.isEmpty() || arg.isNull())
        message = QString::number(cmd);
    else
        message = QString::number(cmd) + "::" + arg;
    localSocket->sendMessage(message);
}

void HManager::openCamera(QString cameraname)
{
    if (cameraname.isEmpty() || cameraname.isNull())
    {
        sendMessage(2, "2``Camera name cannot be empty.");
        return;
    }
    camera->openCamera(cameraname);
    if (camera->isOpenCamera())
        sendMessage(cmd, "0");
    else
        sendMessage(cmd, "1");
}

void HManager::cameraCapture(QString &filename)
{
    if (filename.isEmpty() || filename.isNull())
    {
        sendMessage(2, "2``File name cannot be empty.");
        return;
    }
    if (camera->isOpenCamera())
        camera->captureImage(filename);
    else
        sendMessage(2, "1``Camera not open.");
}

void HManager::closeCamera()
{
    camera->closeCamera();
    if (camera->isOpenCamera())
        sendMessage(3, "1");
    else
        sendMessage(3, "0");
}

void HManager::readMessage(QString message)
{
    parseMessage(message);
    switch (cmd)
    {
        case -1:
            sendMessage(-1, "");
            break;
        case 1:
            openCamera(args[0]);
            break;
        case 2:
            cameraCapture(args[0]);
            break;
        case 3:
            closeCamera();
            break;
        default:
            break;
    }
}

void HManager::cameraCaptured()
{
    sendMessage(2, "0");
}

