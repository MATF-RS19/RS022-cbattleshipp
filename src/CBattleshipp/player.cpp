#include "player.h"

#define GAME_PORT 5050

Player::Player(QObject *parent) : QObject(parent)
{}

bool Player::connectToHost(const QString &ipAddress)
{
    m_socket = std::make_unique<QTcpSocket>();
    m_socket->connectToHost(ipAddress, GAME_PORT);

    // wait for connection
    return m_socket->waitForConnected(30000);
}

QString Player::name() const
{
    return m_name;
}

void Player::name(const QString & name)
{
    if (name.isEmpty()) {
        m_name = QString("Guest");
        return;
    }

    m_name = QString(name);
}
