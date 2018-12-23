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

Q_SIGNALS:
    void log(const QString & msg);
    void setIp(const QString & ip);

protected:
    void incomingConnection(qintptr handle);

private Q_SLOTS:
    void handleRequest();

private:
    GameManager m_gm;
};

#endif // GAMESERVER_H
