#include "gameserver.h"
#include "playerthread.h"

#include <QDebug>
#include <QNetworkInterface>

GameServer::GameServer(QObject *parent)
    : QTcpServer (parent)
{
    openSession();
}

void GameServer::incomingConnection(qintptr socketDescriptor)
{
    PlayerThread *thread = new PlayerThread(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}


void GameServer::openSession()
{

    if (!this->listen()) {
        qDebug() << "$ Server could not start";
        return;
    }

    QHostAddress ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

    // get the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i);
            break;
        }
    }

    qDebug() << "$ Server IP adress " << ipAddress.toString();
    qDebug() << "$ The server is running on port " << this->serverPort();
}
