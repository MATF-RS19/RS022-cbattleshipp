#include <QCoreApplication>

#include "gameserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    GameServer server;

    return app.exec();
}
