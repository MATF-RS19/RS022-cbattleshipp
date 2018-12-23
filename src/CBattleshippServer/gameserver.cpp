#include "gameserver.h"
#include "player.h"

#include <QNetworkInterface>
#include <QTcpSocket>
#include <QList>

#include <memory>

GameServer::GameServer(QObject * parent)
    : QTcpServer(parent)
{}

void GameServer::startServer()
{
    if (!this->listen(QHostAddress::AnyIPv4, 5050)) {
        emit log("Server could not start!");
        return;
    }

    QList<QHostAddress> ipList = QNetworkInterface::allAddresses();
    for (auto & address : ipList) {
        if (address != QHostAddress::LocalHost && address.toIPv4Address()) {
            emit setIp(address.toString());
            break;
        }
    }

    emit log("Server started successfully.");
}

void GameServer::incomingConnection(qintptr handle)
{
    // create new player
    std::unique_ptr<Player> player = std::make_unique<Player>();
    std::unique_ptr<QTcpSocket> playerSocket = std::make_unique<QTcpSocket>(this);

    // set up player socket
    player->m_socket = std::move(playerSocket);
    player->m_socket->setSocketDescriptor(handle);

    QObject::connect(player->m_socket.get(), SIGNAL(readyRead()), this, SLOT(handleRequest()));

    m_gm.addToWaitingList(std::move(player));

    emit log("Player connected to server.");
}

void GameServer::handleRequest()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());

    while (socket->canReadLine()) {
         QString msg = QString::fromUtf8(socket->readLine()).trimmed();

         if (msg.contains("iw2p:")) {
            QStringList request = msg.split(" ");

            // set player name
            m_gm.m_waitingPlayers.at(m_gm.m_playerCounter - 1)->name(request[1]);

            // if even number of players are on network, start a game
            if (m_gm.m_playerCounter % 2 == 0)
                m_gm.startGame();

            return;
         }

        /* FIXME: index out of range !!! = wrong message format
        if (msg.contains("chat_msg:")) {
            QStringList request = msg.split(" ");

            if (request[0][0] == 'a') {
                m_gm.m_activeGames.at(request[0][1].unicode()).m_player2->m_socket->write(msg.toUtf8());
            }
            else {
                m_gm.m_activeGames.at(request[0][1].unicode()).m_player1->m_socket->write(msg.toUtf8());
            }

            return;
         }
       */
    }
}
