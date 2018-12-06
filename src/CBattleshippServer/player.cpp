#include "player.h"

Player::Player(QObject *parent) : QObject(parent)
{
}

QTcpSocket *Player::socket() const
{
    return m_socket;
}

void Player::socket(QTcpSocket *socket)
{
    m_socket = socket;
}

QString Player::name() const
{
    return m_name;
}

void Player::name(const QString &name)
{
    m_name = name;
}
