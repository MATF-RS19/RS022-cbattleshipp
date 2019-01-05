#include "gamemanager.h"

#include <QJsonDocument>
#include <QJsonObject>


GameManager::GameManager(QObject *parent)
    : QObject(parent)
{}

GameManager::~GameManager()
{
    // delete waiting players
    while (!m_waitingPlayers.empty()) {
        if (m_waitingPlayers.back() != nullptr) {
            m_waitingPlayers.back().release();
            m_waitingPlayers.pop_back();
        }
    }

    // delete games
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

    qDebug() << "$ players waiting : " << m_playerCounter;

    //	start a new game for players who want to play a new game
    if (m_playerCounter % 2 == 0 &&
            m_waitingPlayers.back()->m_playerType == PlayerType::PLAY_AGAIN) {
        startGame();
    }
}


// methods for finding players
// NOTE: always check if returned nullptr
Player *GameManager::findIngamePlayer(int playerType, int gameId) const
{
    for (auto & game : m_activeGames) {
        if (game.m_gameId == gameId) {
            if (game.m_player1 != nullptr) {
                if (game.m_player1->m_playerType == playerType)
                    return game.m_player1.get();
            }
            if (game.m_player2 != nullptr) {
                if (game.m_player2->m_playerType == playerType)
                    return game.m_player2.get();
            }
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
        if (game.m_gameId != -1) {
            if (game.m_player1 != nullptr) {
                if (game.m_player1->m_socket->socketDescriptor() == sd)
                    return game.m_player1.get();
            }
            else if (game.m_player2 != nullptr) {
                if (game.m_player2->m_socket->socketDescriptor() == sd)
                    return game.m_player2.get();
            }
        }
    }

    return nullptr;
}


// methods for finding opponents
// NOTE: always check if returned nullptr
Player *GameManager::opponent(int playerType, int gameId) const
{
    for (auto & game : m_activeGames) {
        if (game.m_gameId == gameId && game.m_gameId != -1) {
            if (playerType == PLAYER1) {
                if (game.m_player2 == nullptr)
                    return nullptr;
                else if (game.m_player2->m_playerType != DELETED)
                    return game.m_player2.get();
            }

            if (playerType == PLAYER2) {
                if (game.m_player1 == nullptr)
                    return nullptr;
                else if (game.m_player1->m_playerType != DELETED)
                    return game.m_player1.get();
            }
        }
    }

    return nullptr;
}


Player *GameManager::opponent(qintptr sd) const
{
    auto player = findPlayer(sd);

    if (player == nullptr)
        return nullptr;

    for (auto & game : m_activeGames) {
        if (player->m_gameId == game.m_gameId && game.m_gameId != -1) {
            if (player->m_playerType == PLAYER1) {
                if (game.m_player2 == nullptr)
                    return nullptr;
                else if (game.m_player2->m_playerType != DELETED) {
                    return game.m_player2.get();
                }
            }
            if (player->m_playerType == PLAYER2) {
                if (game.m_player1 == nullptr)
                    return nullptr;
                else if (game.m_player1->m_playerType != DELETED) {
                    return game.m_player1.get();
                }
            }
        }
    }

    return nullptr;
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
    // player is in a game, mark it for deletion
    else {
        for (auto & game : m_activeGames) {
            if (game.m_gameId == player->m_gameId) {
                if (player->m_playerType == PLAYER1)
                    game.m_player1->m_playerType = PlayerType::DELETED;
                else if (player->m_playerType == PLAYER2)
                    game.m_player2->m_playerType = PlayerType::DELETED;
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

    // set player's game id
    player1->m_gameId = m_gameCounter;
    player2->m_gameId = m_gameCounter;

    // send opponent info
    QJsonObject msg1;
    msg1.insert("ucp", 1);
    msg1.insert("opp_name", player2->name());
    msg1.insert("player_type", player1->m_playerType);
    msg1.insert("game_id", m_gameCounter);

    QJsonDocument doc1(msg1);

    qDebug() << "$ sending : " << doc1;
    player1->m_socket->write(doc1.toJson());

    QJsonObject msg2;
    msg2.insert("ucp", 1);
    msg2.insert("opp_name", player1->name());
    msg2.insert("player_type", player2->m_playerType);
    msg2.insert("game_id", m_gameCounter);

    QJsonDocument doc2(msg2);
    qDebug() << "$ sending : " << doc2;
    player2->m_socket->write(doc2.toJson());

    // create a game
    Game game(nullptr, std::move(player1), std::move(player2), m_gameCounter);
    m_activeGames.push_back(std::move(game));
}

