#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "player.h"
#include "game.h"

#include <vector>
#include <memory>

#include <QObject>

class GameManager : public QObject
{
    Q_OBJECT

public:
    explicit GameManager(QObject *parent = nullptr);

    void addToWaitingList(std::unique_ptr<Player> && player);

private:
    std::vector<std::unique_ptr<Player>> m_waitingPlayers;
    std::vector<Game> m_activeGames;

    uint16_t m_playerCounter = 0;
    uint16_t m_gameCounter = 0;

    void startGame();

    friend class GameServer;
};

#endif // GAMEMANAGER_H
