#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <memory>
#include <player.h>

class Game : public QObject
{
    Q_OBJECT

public:
    explicit Game(QObject *parent = nullptr,
                  std::unique_ptr<Player> && player1 = nullptr,
                  std::unique_ptr<Player> && player2 = nullptr);

    Game(Game && other);

private:
    std::unique_ptr<Player> m_player1;
    std::unique_ptr<Player> m_player2;

    uint16_t m_gameId = 0;

    friend class GameManager;
    friend class GameServer;
};

#endif // GAME_H
