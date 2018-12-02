#include "gameserver.h"
#include "playerthread.h"

#include <QDebug>
#include <QList>
#include <QNetworkInterface>

GameServer::GameServer(QObject *parent)
    : QTcpServer(parent)
{
    if (!this->listen(QHostAddress::AnyIPv4, GAME_PORT)) {
        qDebug() << "$ Server could not start";
        exit(EXIT_FAILURE);
    }

    QString ipAddress;
    QList<QHostAddress> ipList = QNetworkInterface::allAddresses();

    for (int i = 0, n = ipList.size(); i < n; i++) {
        if (ipList.at(i) != QHostAddress::LocalHost && ipList.at(i).toIPv4Address()) {
            ipAddress = ipList.at(i).toString();
            break;
        }
    }

   qDebug() << "$ Server IP address" << ipAddress;
}

void GameServer::incomingConnection(qintptr socketDescriptor)
{
    PlayerThread *player = new PlayerThread(this, socketDescriptor);

    connect(player, SIGNAL(finished()), player, SLOT(deleteLater()));

    player->start();
}
