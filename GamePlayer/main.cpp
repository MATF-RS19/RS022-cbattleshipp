#include "player.h"

#include <QCoreApplication>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QTextStream in(stdin);

    qDebug() << "$ Server IP address: ";
    QString ipAddress;
    in >> ipAddress;

    qDebug() << "$ Server port: ";
    quint16 port;
    in >> port;

    Player player;
    player.connect(ipAddress, port);

    return app.exec();
}
