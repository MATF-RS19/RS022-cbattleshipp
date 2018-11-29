#ifndef PLAYERTHREAD_H_
#define PLAYERTHREAD_H_

#include <QThread>
#include <QTcpSocket>
#include <QDebug>

class PlayerThread : public QThread {
    Q_OBJECT

public:
    PlayerThread(qintptr socketDescriptor, QObject *parent);

    void run() override;

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    qintptr socketDescriptor;
};

#endif // PLAYERTHREAD_H_
