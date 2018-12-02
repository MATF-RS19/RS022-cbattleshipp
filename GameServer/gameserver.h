#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QObject>
#include <QTcpServer>

#define GAME_PORT 5050

class GameServer : public QTcpServer
{
    Q_OBJECT

public:
    GameServer(QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor);

};

#endif // GAMESERVER_H
