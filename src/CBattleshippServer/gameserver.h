#ifndef GAMESERVER_H
#define GAMESERVER_H

#include "gamemanager.h"

#include <QObject>
#include <QTcpServer>

class GameServer : public QTcpServer
{
    Q_OBJECT

public:
    GameServer(QObject *parent = nullptr);

    void startServer();

public Q_SLOTS:
    void handleRequest();
    void sendStartMsg();

protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    GameManager m_gm;
};

#endif // GAMESERVER_H
