#include "player.h"

#define GAME_PORT 5050

Player::Player(QObject *parent) : QObject(parent)
{
}

bool Player::connectToHost(const QString &ipAddress)
{
    m_socket = new QTcpSocket();
    m_socket->connectToHost(ipAddress, GAME_PORT);

    // wait for connection
    return m_socket->waitForConnected(30000);
}

QTcpSocket *Player::socket() const
{
    return m_socket;
}

QString Player::name() const
{
    return m_name;
}

void Player::name(const QString & name)
{
    if (name.isEmpty()) {
        m_name = "Guest";
    }
    else
        m_name = name;
}
