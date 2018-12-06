#include "gameserver.h"
#include "player.h"

#include <QDebug>
#include <QNetworkInterface>

#define GAME_PORT 5050

GameServer::GameServer(QObject *parent)
    : QTcpServer(parent)
{
}

void GameServer::startServer()
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

   qDebug() << "$ Server IP address " << ipAddress;

   connect(&m_gm, SIGNAL(startGame()), this, SLOT(sendStartMsg()));
}

void GameServer::incomingConnection(qintptr socketDescriptor)
{
    Player *player = new Player();
    player->socket(new QTcpSocket(this));

    player->socket()->setSocketDescriptor(socketDescriptor);
    m_gm.addToPlayersList(player);

    qDebug() << "$ Player connected";

    connect(player->socket(), SIGNAL(readyRead()), this, SLOT(handleRequest()));
}

void GameServer::handleRequest()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());

    while (socket->canReadLine()) {
         QString msg = QString::fromUtf8(socket->readLine()).trimmed();

         if (msg.contains("iw2p:")) {
            QStringList request = msg.split(" ");
            qDebug() << request[2];
            m_gm.setPlayerName(socket->socketDescriptor(), request[2]);
         }
    }
}

void GameServer::sendStartMsg()
{
    QTcpSocket *socket1 = m_gm.getPlayer1()->socket();
    QTcpSocket *socket2 = m_gm.getPlayer2()->socket();

    qDebug() << m_gm.getPlayer1()->name();
    qDebug() << m_gm.getPlayer2()->name();

    socket1->write(QString("yycp: opponent: " + m_gm.getPlayer2()->name() + " \n").toUtf8());
    socket2->write(QString("yycp: opponent: " + m_gm.getPlayer1()->name() + " \n").toUtf8());
}
