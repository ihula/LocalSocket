#include <QApplication>
#include <QLocalSocket>

#include "hmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HManager manager;
    manager.connectServer("localserver-Hula-Camera");

    return a.exec();
}
