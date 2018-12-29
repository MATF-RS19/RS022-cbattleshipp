#include "gamemanager.h"

#include <QJsonDocument>
#include <QJsonObject>


GameManager::GameManager(QObject *parent)
    : QObject(parent)
{}


void GameManager::addToWaitingList(std::unique_ptr<Player> && player)
{
    ++m_playerCounter;
    m_waitingPlayers.push_back(std::move(player));

    //	start a new game for players who already played a game
    if (m_playerCounter % 2 == 0 && m_waitingPlayers.back()->m_playerType != 0)
        startGame();
}


Player *GameManager::findIngamePlayer(int playerType, int gameId) const
{
    for (auto & game : m_activeGames) {
        if (game.m_gameId == gameId) {
            if (game.m_player1->m_playerType == playerType)
                return  game.m_player1.get();
            else
                return game.m_player2.get();
        }
    }

    return nullptr;
}


Player *GameManager::opponent(int playerType, int gameId) const
{
    for (auto & game : m_activeGames) {
        if (game.m_gameId == gameId) {
            if (game.m_player1->m_playerType == playerType)
                return  game.m_player2.get();
            else
                return game.m_player1.get();
        }
    }

    return nullptr;
}


void GameManager::removeWaitingPlayer()
{
    --m_playerCounter;
    auto deletedPlayer = std::move(m_waitingPlayers.back());
    deletedPlayer.release();
    m_waitingPlayers.pop_back();
}


void GameManager::startGame()
{
    ++m_gameCounter;

    // get the first player
    auto player1 = std::move(m_waitingPlayers.back());
    m_waitingPlayers.pop_back();

    // get the second player
    auto player2 = std::move(m_waitingPlayers.back());
    m_waitingPlayers.pop_back();

    // remove last two joined players
    m_playerCounter -= 2;

    player1->m_playerType = 1;
    player2->m_playerType = 2;

    // send opponent info
    QJsonObject msg1;
    msg1.insert("ucp", 1);
    msg1.insert("opp_name", player2->name());
    msg1.insert("player_type", player1->m_playerType);
    msg1.insert("game_id", m_gameCounter);

    QJsonDocument doc1(msg1);
    qDebug() << "Sending : " << doc1;
    player1->m_socket->write(doc1.toJson());

    QJsonObject msg2;
    msg2.insert("ucp", 1);
    msg2.insert("opp_name", player1->name());
    msg2.insert("player_type", player2->m_playerType);
    msg2.insert("game_id", m_gameCounter);

    QJsonDocument doc2(msg2);
    qDebug() << "Sending : " << doc2;
    player2->m_socket->write(doc2.toJson());

    // create a game
    Game game(nullptr, std::move(player1), std::move(player2), m_gameCounter);
    m_activeGames.push_back(std::move(game));
}


// methods for finding opponent's socket
// NOTE: always check if socket is nullptr
QTcpSocket *GameManager::opponentSocket(int playerType, int gameId)
{
    // find opponent socket
    for (auto & game : m_activeGames) {
        if (gameId == game.m_gameId)
            return playerType == game.m_player1->m_playerType ? game.m_player2->m_socket.get() : game.m_player1->m_socket.get();
    }

    return nullptr;
}


QTcpSocket *GameManager::opponentSocket(qintptr socketDescriptor)
{
    for (auto & game : m_activeGames) {
        if (socketDescriptor == game.m_player1->m_socket.get()->socketDescriptor())
            return game.m_player2->m_socket.get();
        else if (socketDescriptor == game.m_player2->m_socket.get()->socketDescriptor())
            return game.m_player1->m_socket.get();
    }

    return nullptr;
}
