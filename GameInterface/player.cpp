#include "player.h"

Player::Player(QObject *parent)
    : QObject(parent)
{
}

bool Player::connectToHost(QString ipAddress)
{
    m_socket = new QTcpSocket(this);
    m_socket->connectToHost(ipAddress, GAME_PORT);

    // wait for connection
    return m_socket->waitForConnected(30000);
}
