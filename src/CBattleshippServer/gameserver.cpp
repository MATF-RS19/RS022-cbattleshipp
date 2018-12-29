#include "gameserver.h"
#include "player.h"

#include <QNetworkInterface>
#include <QTcpSocket>
#include <QList>
#include <QJsonDocument>
#include <QJsonObject>

#include <memory>
#include <iterator>


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

    connect(player->m_socket.get(), SIGNAL(readyRead()), this, SLOT(handleRequest()));
    connect(player->m_socket.get(), SIGNAL(disconnected()), this, SLOT(playerDisconnected()));

    m_gm.addToWaitingList(std::move(player));

    emit log("Player connected to server.");
}


void GameServer::handleRequest()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());

    QJsonDocument msg = QJsonDocument::fromJson(socket->readAll());
    QJsonObject request = msg.object();

    qDebug() << request;

    if (request.isEmpty())
        return;

    if (request.contains("iw2p"))
        handlePlayRequest(request);

    if (request.contains("chat_msg"))
        handleChatRequest(request);

    if (request.contains("play_again"))
        handlePlayAgainRequest(request);

    if (request.contains("quit"))
        handlePlayAgainRequest(request);
}


void GameServer::playerDisconnected()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());

    auto oppSocket = m_gm.opponentSocket(socket->socketDescriptor());

    // if player was in a game, send opponent disconnected response
    if (oppSocket != nullptr) {
        QJsonObject msg;
        msg.insert("od", 1);
        QJsonDocument doc(msg);
        oppSocket->write(doc.toJson());

    } // player left before playing a game
    else {
        m_gm.removeWaitingPlayer();
    }

    socket->disconnectFromHost();
    emit log("Player disconnected");
}


void GameServer::handlePlayRequest(QJsonObject & request)
{
    // set player name
    m_gm.m_waitingPlayers.at(m_gm.m_playerCounter - 1)->name(request.value("name").toString());

    // if even number of players are on network, start a game
    if (m_gm.m_playerCounter % 2 == 0)
        m_gm.startGame();
}


void GameServer::handleChatRequest(QJsonObject & request)
{
    QJsonObject msg;
    msg.insert("chat_msg", request.value("chat_msg").toString());
    QJsonDocument doc(msg);

    qDebug() << "Sending: " << doc.toJson();

    if (request.value("player_type").toInt() == 1) {
        auto socket = m_gm.opponentSocket(1, request.value("game_id").toInt());
        if (socket != nullptr)
            socket->write(doc.toJson());
    }
    else {
        auto socket = m_gm.opponentSocket(2, request.value("game_id").toInt());
        if (socket != nullptr)
            socket->write(doc.toJson());
    }
}


void GameServer::handlePlayAgainRequest(QJsonObject &request)
{
    for (auto i = std::begin(m_gm.m_activeGames); i != std::end(m_gm.m_activeGames); ++i) {
        if (i->m_player1->m_playerType == request.value("player_type").toInt()) {
                m_gm.addToWaitingList(std::move(i->m_player1));
                i->m_player2.release();
                m_gm.m_activeGames.erase(i);
                break;
        }
        else if (i->m_player2->m_playerType == request.value("player_type").toInt()) {
                m_gm.addToWaitingList(std::move(i->m_player2));
                i->m_player1.release();
                m_gm.m_activeGames.erase(i);
                break;
        }
    }
}


// delete players who left the game
void GameServer::handleQuitRequest(QJsonObject &request)
{
    for (auto i = std::begin(m_gm.m_activeGames); i != std::end(m_gm.m_activeGames); ++i) {
        if (i->m_player1->m_playerType == request.value("player_type").toInt() ||
            i->m_player2->m_playerType == request.value("player_type").toInt()) {
                i->m_player1.release();
                i->m_player2.release();
                m_gm.m_activeGames.erase(i);
                break;
        }
    }
}
