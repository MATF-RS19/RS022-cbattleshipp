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
    if (!this->listen(QHostAddress::AnyIPv4, GAME_PORT)) {
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
    ++m_playerIdGenerator;

    // create new player
    std::unique_ptr<Player> player = std::make_unique<Player>();
    std::unique_ptr<QTcpSocket> playerSocket = std::make_unique<QTcpSocket>(this);

    // set up player socket
    player->m_socket = std::move(playerSocket);
    player->m_socket->setSocketDescriptor(handle);

    player->m_playerId = m_playerIdGenerator;

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

    // player will send one request at a time = return from method
    if (request.contains("iw2p")) {
        handlePlayRequest(request);
        return;
    }

    if (request.contains("chat_msg")) {
        handleChatRequest(request);
        return;
    }

    if (request.contains("play_again")) {
        handlePlayAgainRequest(request);
        return;
    }

    if (request.contains("ready")) {
        handleReadyRequest(request);
        return;
    }

    if (request.contains("hit")) {
        handleHitRequest(request);
        return;
    }
}


void GameServer::playerDisconnected()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());

    auto opp = m_gm.opponent(socket->socketDescriptor());
    auto player = m_gm.findPlayer(socket->socketDescriptor());

    // remove player from game
    m_gm.removePlayer(player);

    // if player was in a game, send opponent disconnected response
    if (opp != nullptr) {
        QJsonObject msg;
        msg.insert("od", 1);
        QJsonDocument doc(msg);

        opp->m_socket->write(doc.toJson());
    }

    emit log("Player disconnected");
}


void GameServer::handlePlayRequest(QJsonObject & request)
{
    // set player name
    m_gm.m_waitingPlayers.at(m_gm.m_playerCounter - 1)->name(request.value("name").toString());

    // if even number of players are connected to server, start a game
    if (m_gm.m_playerCounter % 2 == 0)
        m_gm.startGame();
}


void GameServer::handleChatRequest(QJsonObject & request)
{
    QJsonObject msg;
    msg.insert("chat_msg", request.value("chat_msg").toString());
    QJsonDocument doc(msg);

    qDebug() << "$ sending : " << doc.toJson();

    if (request.value("player_type").toInt() == PLAYER1) {
        auto opp = m_gm.opponent(PLAYER1, request.value("game_id").toInt());
        if (opp != nullptr)
            opp->m_socket->write(doc.toJson());
    }
    else {
        auto opp = m_gm.opponent(PLAYER2, request.value("game_id").toInt());
        if (opp != nullptr)
            opp->m_socket->write(doc.toJson());
    }
}


void GameServer::handlePlayAgainRequest(QJsonObject &request)
{
    for (auto & game : m_gm.m_activeGames) {
        if (game.m_gameId == request.value("game_id").toInt() && game.m_gameId != -1) {

            if (request.value("player_type").toInt() == PlayerType::PLAYER1) {
                // game ended with one player quiting
                if (request.value("game_outcome").toInt() == -1)
                    game.m_gameId = request.value("game_outcome").toInt();

                if (request.value("game_outcome").toInt() == 42 &&
                    m_gm.opponent(PLAYER1, game.m_gameId) == nullptr)
                    game.m_gameId = -1;

                game.m_player1->m_playerType = PlayerType::PLAY_AGAIN;
                m_gm.addToWaitingList(std::move(game.m_player1));

                return;
            }
            else {
                if (request.value("game_outcome").toInt() == -1)
                    game.m_gameId = request.value("game_outcome").toInt();

                if (request.value("game_outcome").toInt() == 42 &&
                    m_gm.opponent(PLAYER2, game.m_gameId) == nullptr)
                    game.m_gameId = -1;

                game.m_player2->m_playerType = PlayerType::PLAY_AGAIN;
                m_gm.addToWaitingList(std::move(game.m_player2));

                return;
            }
        }
    }
}


void GameServer::handleReadyRequest(QJsonObject &request)
{
    auto player = m_gm.findIngamePlayer(request.value("playerType").toInt(), request.value("gameId").toInt());
    auto gameId = request.value("gameId").toInt();

    // remove player info
    request.remove("ready");
    request.remove("playerType");
    request.remove("gameId");

    // set player's ships
    player->m_ships = request;

    auto opp = m_gm.opponent(player->m_playerType, gameId);
    QJsonObject response;

    // check if opponent ships are all set up, so game can start
    if (opp != nullptr) {
        if (!opp->m_ships.empty()) {
            response.insert("start_game", 1);

            // set first player turn
            if (player->m_playerType == PlayerType::PLAYER1){
                response.insert("turn", player->m_name);
                response.insert("player_type" , player->m_playerType);
            }else {
                response.insert("turn", opp->m_name);
                response.insert("player_type" , player->m_playerType);
            }

            QJsonDocument msg(response);
            player->m_socket->write(msg.toJson());
            opp->m_socket->write(msg.toJson());
        }
        else {
            // send message to player that opponent is not ready
            response.insert("wait_opp", 1);
            response.insert("opp_name", opp->m_name);
            QJsonDocument msg(response);

            player->m_socket->write(msg.toJson());

            // send message to opponent that his opponent is ready
            QJsonObject readyMsg;
            readyMsg.insert("opp_ready", 1);
            readyMsg.insert("opp_name", player->m_name);
            QJsonDocument info(readyMsg);

            opp->m_socket->write(info.toJson());
        }
    }
}


void GameServer::handleHitRequest(QJsonObject & request)
{
    auto player = m_gm.findIngamePlayer(request.value("playerType").toInt(), request.value("gameId").toInt());
    auto gameId = request.value("gameId").toInt();

    // remove player info
    request.remove("hit");
    request.remove("playerType");
    request.remove("gameId");

    auto opp = m_gm.opponent(player->m_playerType, gameId);

    QJsonObject responseToOpponent;
    QJsonObject responseToPlayer;

    //send message to opponent that he/she is hit or not
    responseToOpponent.insert("attack", 1);
    //send message to player that he/she is hit opponent or not
    responseToPlayer.insert("if_hit", 1);

    // send hit coordinates
    responseToOpponent.insert("x", request.value("x"));
    responseToOpponent.insert("y", request.value("y"));

    if(opp->m_ships.value(QString::number(request.value("y").toInt()))[request.value("x").toInt()] == 1) {
        //yah = you are hit
        responseToOpponent.insert("yah", 1);

        responseToPlayer.insert("great_attack", 1);
    }

    QJsonDocument msgTO(responseToOpponent);
    QJsonDocument msgTP(responseToPlayer);
    opp->m_socket->write(msgTO.toJson());
    player->m_socket->write(msgTP.toJson());

}
