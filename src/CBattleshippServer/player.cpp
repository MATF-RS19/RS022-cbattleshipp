#include "player.h"

Player::Player(QObject *parent, std::unique_ptr<QTcpSocket> && socket)
    : QObject(parent),
      m_socket(std::move(socket)),
      m_name("Guest")
{}

Player::Player(Player &&other)
    : m_socket(std::move(other.m_socket)),
      m_name(std::move(other.m_name))
{}

void Player::name(const QString & playerName)
{
    m_name = QString(playerName);
}

QString Player::name() const
{
   return m_name;
}
