#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QJsonObject>

#include <memory>

enum PlayerType {
    NEW = 0,
    PLAYER1 = 1,
    PLAYER2 = 2,
    DELETED = 3,
    PLAY_AGAIN = 4
};

class Player : public QObject
{
    Q_OBJECT

public:
    explicit Player(QObject *parent = nullptr,
                    std::unique_ptr<QTcpSocket> && socket = nullptr);

    Player(Player && other);

    void name(const QString & playerName);
    QString name() const;

private:
    std::unique_ptr<QTcpSocket> m_socket;
    QString m_name;

    QJsonObject m_ships;

    uint8_t m_playerType = PlayerType::NEW;

    int m_playerId = 0;

    friend class GameServer;
    friend class GameManager;
};


#endif // PLAYER_H
