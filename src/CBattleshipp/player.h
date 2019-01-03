#ifndef PLAYER_H
#define PLAYER_H

#include <memory>

#include <QObject>
#include <QTcpSocket>

class Player : public QObject
{
    Q_OBJECT

public:
    explicit Player(QObject *parent = nullptr);

    bool connectToHost(const QString & ipAddress);

    QTcpSocket *socket() const;

    QString name() const;
    void name(const QString & name);

private:
    std::unique_ptr<QTcpSocket> m_socket = nullptr;
    QString m_name;

    uint8_t m_playerType;
    qint32 m_gameId;
    qint64 m_greatAttack = 0;
    qint64 m_shipsLeft = 30;
    qint64 m_opponentShipsLeft = 30;

    friend class MainWindow;
};

#endif // PLAYER_H
