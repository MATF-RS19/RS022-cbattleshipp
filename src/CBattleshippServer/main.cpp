#include "mainwindow.h"
#include "gameserver.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    GameServer server;

    QObject::connect(&server, SIGNAL(log(QString)), &w, SLOT(writeLog(QString)));
    QObject::connect(&server, SIGNAL(setIp(QString)), &w, SLOT(writeIp(QString)));

    server.startServer();

    w.show();

    return a.exec();
}
