#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "player.h"
#include "game.h"

#include <vector>
#include <list>
#include <memory>

#include <QObject>

class GameManager : public QObject
{
    Q_OBJECT

public:
    explicit GameManager(QObject *parent = nullptr);
    ~GameManager();

    void addToWaitingList(std::unique_ptr<Player> && player);

    Player *findIngamePlayer(int playerType, int gameId) const;
    Player *findPlayer(qintptr sd) const;

    Player *opponent(int playerType, int gameId) const;
    Player *opponent(qintptr sd) const;

private:
    std::vector<std::unique_ptr<Player>> m_waitingPlayers;
    std::list<Game> m_activeGames;

    uint16_t m_playerCounter = 0;
    uint16_t m_gameCounter = 0;

    void startGame();

    void removePlayer(Player *player);

    GameManager(const GameManager& other);
    GameManager& operator=(const GameManager &other);

    friend class GameServer;
};

#endif // GAMEMANAGER_H
