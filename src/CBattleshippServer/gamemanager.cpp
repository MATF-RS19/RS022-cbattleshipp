#include "gamemanager.h"

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

    player1->m_playerType = 'a';
    player2->m_playerType = 'b';

    // send opponent info
    player1->m_socket->write(QString("opp_name: " +
                                     player2->m_name + " " +
                                     player1->m_playerType + " " + QString::number(m_gameCounter) + "\n").toUtf8());

    player2->m_socket->write(QString("opp_name: " +
                                     player1->m_name + " " +
                                     player2->m_playerType + " " + QString::number(m_gameCounter) + "\n").toUtf8());

    Game game(nullptr, std::move(player1), std::move(player2), m_gameCounter);

    m_activeGames.push_back(std::move(game));
}
