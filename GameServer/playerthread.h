#ifndef PLAYERTHREAD_H
#define PLAYERTHREAD_H

#include <QObject>
#include <QThread>

class PlayerThread : public QThread
{
    Q_OBJECT

public:
    PlayerThread(QObject *parent = nullptr, qintptr socketDescriptor = 0);

protected:
    void run();

private:
    qintptr m_socketDescriptor;
};

#endif // PLAYERTHREAD_H
