#include "playerthread.h"

PlayerThread::PlayerThread(qintptr socketDescriptor, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor)
{
}

void PlayerThread::run()
{
    QTcpSocket tcpSocket;
    if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
        emit error(tcpSocket.error());
        return;
    }

    qDebug() << "$ Hello from client thread!";

    tcpSocket.disconnectFromHost();
}
