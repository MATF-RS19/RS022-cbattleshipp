#ifndef GAME_H
#define GAME_H

#include <player.h>

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>

#include <memory>

class Game : public QObject
{
    Q_OBJECT

public:
    explicit Game(QObject *parent = nullptr,
                  std::unique_ptr<Player> && player1 = nullptr,
                  std::unique_ptr<Player> && player2 = nullptr,
                  qint32 gameId = 0);

    Game(Game && other);

private:
    std::unique_ptr<Player> m_player1;
    std::unique_ptr<Player> m_player2;

    // if gameId is -1, game is ended
    qint32 m_gameId = 0;

    friend class GameManager;
    friend class GameServer;
};

#endif // GAME_H
