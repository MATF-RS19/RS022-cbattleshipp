#include "gamemanager.h"

#include <QJsonDocument>
#include <QJsonObject>


GameManager::GameManager(QObject *parent)
    : QObject(parent)
{}

GameManager::~GameManager()
{
    // delete active games
    while (!m_activeGames.empty()) {

        if (m_activeGames.front().m_player1 != nullptr ) {
            m_activeGames.front().m_player1->m_socket.release();
            m_activeGames.front().m_player1.release();
        }

        if (m_activeGames.front().m_player2 != nullptr) {
            m_activeGames.front().m_player2->m_socket.release();
            m_activeGames.front().m_player2.release();
        }

        m_activeGames.pop_front();
    }
}

void GameManager::addToWaitingList(std::unique_ptr<Player> && player)
{
    ++m_playerCounter;

    m_waitingPlayers.push_back(std::move(player));

    qDebug() << m_playerCounter;

    //	start a new game for players who want to play a new game
    if (m_playerCounter % 2 == 0 &&
            m_waitingPlayers.back()->m_playerType == PlayerType::PLAY_AGAIN) {
        qDebug() << "IT SHOULD START!!!";
        startGame();
    }
}


// methods for finding players
// NOTE: always check if methods returned nullptr
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

Player *GameManager::findPlayer(qintptr sd) const
{
    for (auto & player : m_waitingPlayers) {
        if (sd ==player->m_socket->socketDescriptor())
            return player.get();
    }

    for (auto & game : m_activeGames) {
        if (sd == game.m_player1->m_socket.get()->socketDescriptor())
            return game.m_player1.get();
        else if (sd == game.m_player2->m_socket.get()->socketDescriptor())
            return game.m_player2.get();
    }

    return nullptr;
}

Player *GameManager::opponent(int playerType, int gameId) const
{
    for (auto & game : m_activeGames) {
        if (game.m_gameId == gameId && game.m_gameId != -1) {
            if (game.m_player1->m_playerType == playerType &&
                game.m_player2->m_playerType != PlayerType::DELETED)
                return  game.m_player2.get();
            else if (game.m_player2->m_playerType == playerType &&
                     game.m_player1->m_playerType != PlayerType::DELETED)
                return game.m_player1.get();
        }
    }

    return nullptr;
}


Player *GameManager::opponent(qintptr sd) const
{
    for (auto & game : m_activeGames) {
        if (game.m_gameId != -1) {
            if (sd == game.m_player1->m_socket.get()->socketDescriptor() &&
                    game.m_player2->m_playerType != PlayerType::DELETED) {
                return game.m_player2.get();
            }
            else if (sd == game.m_player2->m_socket.get()->socketDescriptor() &&
                     game.m_player1->m_playerType != PlayerType::DELETED) {
                return game.m_player1.get();
            }
        }
    }

    return nullptr;
}


void GameManager::removeWaitingPlayer()
{
    --m_playerCounter;
    auto deletedPlayer = std::move(m_waitingPlayers.back());
    deletedPlayer.release();

    // if player is waiting, he must be at the back of the vector
    m_waitingPlayers.pop_back();
}

void GameManager::removePlayer(Player *player)
{
    // player is in waiting list
    if (player->m_playerType == PlayerType::NEW) {
        --m_playerCounter;

        m_waitingPlayers.back()->m_socket.release();
        m_waitingPlayers.back().release();

        m_waitingPlayers.pop_back();

        return;
    }
    // player is in a game
    else {
        for (auto & game : m_activeGames) {
            if (game.m_player1->m_playerId == player->m_playerId) {
                // mark player for deletion
                game.m_player1->m_playerType = PlayerType::DELETED;

                return;
            }
            else if (game.m_player2->m_playerId == player->m_playerId) {
                // mark player for deletion
                game.m_player2->m_playerType = PlayerType::DELETED;
                return;
            }
        }
    }
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

    player1->m_playerType = PlayerType::PLAYER1;
    player2->m_playerType = PlayerType::PLAYER2;

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
        if (gameId == game.m_gameId && game.m_gameId != -1) {
            if (game.m_player1->m_playerType == playerType && game.m_player2->m_playerType != DELETED)
                return  game.m_player2->m_socket.get();
            else if (game.m_player2->m_playerType == playerType && game.m_player1->m_playerType != DELETED)
                return  game.m_player1->m_socket.get();
        }
    }

    return nullptr;
}


QTcpSocket *GameManager::opponentSocket(qintptr socketDescriptor)
{
    for (auto & game : m_activeGames) {
        if (game.m_gameId != -1) {
            if (socketDescriptor == game.m_player1->m_socket.get()->socketDescriptor() && game.m_player2->m_playerType != DELETED)
                return game.m_player2->m_socket.get();
            else if (socketDescriptor == game.m_player2->m_socket.get()->socketDescriptor() && game.m_player1->m_playerType != DELETED)
                return game.m_player1->m_socket.get();
        }
    }

    return nullptr;
}
