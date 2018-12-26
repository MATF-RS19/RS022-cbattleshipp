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
