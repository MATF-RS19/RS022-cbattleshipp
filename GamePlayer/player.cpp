#include "player.h"

#include <QDebug>

Player::Player(QObject *parent)
    : QObject(parent)
{
}

void Player::connect(QString ipAddress, quint16 port)
{
    tcpSocket = new QTcpSocket(this);

    tcpSocket->connectToHost(ipAddress, port);

    if (tcpSocket->waitForConnected(3000)) {
        qDebug() << "Connected!";

        tcpSocket->close();
    }
    else {
        qDebug() << "Failed to connect!";
    }

}
