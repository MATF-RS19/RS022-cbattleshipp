#include "gamemanager.h"

GameManager::GameManager(QObject *parent) : QObject(parent)
{
}

QVector<Player *> GameManager::players() const
{
    return m_players;
}

void GameManager::addToPlayersList(Player *player)
{
    m_players.push_back(player);
    ++m_numOfPlayers;

    if (!(m_numOfPlayers % 2)) {
        createGame(m_players.at(0), m_players.at(1));
        m_players.pop_front();
        m_players.pop_front();
    }
}

void GameManager::setPlayerName(qintptr socketDescriptor, QString &playerName)
{
    for (int i = 0, n = m_players.size(); i < n; ++i) {
        qDebug() << m_players.at(i)->socket()->socketDescriptor();
        if (m_players.at(i)->socket()->socketDescriptor() == socketDescriptor) {
            m_players.at(i)->name(playerName);
            break;
        }
    }
}

Player *GameManager::getPlayer1() const
{
    return m_activeGameList[0].first;
}

Player *GameManager::getPlayer2() const
{
    return m_activeGameList[0].second;
}

void GameManager::createGame(Player *player1, Player *player2)
{
    m_activeGameList.push_back(qMakePair(player1, player2));
    emit startGame();
}
