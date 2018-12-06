#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <player.h>

#include <QObject>
#include <QTcpSocket>

class GameManager : public QObject
{
    Q_OBJECT

public:
    explicit GameManager(QObject *parent = nullptr);

    QVector<Player *> players() const;

    void addToPlayersList(Player *player);
    void setPlayerName(qintptr socketDescriptor, QString & playerName);

    Player *getPlayer1() const;
    Player *getPlayer2() const;

Q_SIGNALS:
    void startGame();

private:
    QVector<Player *> m_players;
    QVector<QPair<Player *, Player *> > m_activeGameList;
    qint32 m_numOfPlayers = 0;

    void createGame(Player* player1, Player* player2);
};

#endif // GAMEMANAGER_H
