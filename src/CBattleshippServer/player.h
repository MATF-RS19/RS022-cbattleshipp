#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>
#include <QTcpSocket>

#include <memory>

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

    // playerType values are 1 and 2 for ingame players and 0 for new players
    uint8_t m_playerType = 0;

    friend class GameServer;
    friend class GameManager;
};

#endif // PLAYER_H
