#include "gamemanager.h"

GameManager::GameManager(QObject *parent)
    : QObject(parent)
{}

void GameManager::addToWaitingList(std::unique_ptr<Player> && player)
{
    m_playerCounter += 1;
    m_waitingPlayers.push_back(std::move(player));
}

void GameManager::startGame()
{
    m_gameCounter += 1;

    // create new game
    auto player1 = std::move(std::move(m_waitingPlayers[0]));
    auto player2 = std::move(std::move(m_waitingPlayers[1]));

    player1->m_playerId = 'a';
    player2->m_playerId = 'b';

    // send opponent name
    player1->m_socket->write(QString("opp_name: " +
                                     player2->m_name + " " +
                                     player1->m_playerId +
                                     m_gameCounter + "\n").toUtf8());

    player2->m_socket->write(QString("opp_name: " +
                                     player1->m_name + " " +
                                     player2->m_playerId +
                                     m_gameCounter + "\n").toUtf8());

    Game game(nullptr, std::move(player1), std::move(player2));

    // remove first two joined players
    m_playerCounter -= 2;
    m_waitingPlayers.pop_back();
    m_waitingPlayers.pop_back();

    m_activeGames.push_back(std::move(game));
}
