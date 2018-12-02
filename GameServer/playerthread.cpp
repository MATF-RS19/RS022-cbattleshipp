#include "playerthread.h"

#include <QTcpSocket>

PlayerThread::PlayerThread(QObject *parent, qintptr socketDescriptor)
    : QThread(parent),
      m_socketDescriptor(socketDescriptor)
{
}

void PlayerThread::run()
{
    QTcpSocket socket;
    if (!socket.setSocketDescriptor(m_socketDescriptor)) {
        return;
    }

    qDebug() << "$ What shall I do now?";

    QThread::exec();

}
