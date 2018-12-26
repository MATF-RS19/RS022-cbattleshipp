#ifndef GAMESERVER_H
#define GAMESERVER_H

#include "gamemanager.h"

#include <QObject>
#include <QTcpServer>
#include <QJsonDocument>
#include <QJsonObject>

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
    void clientDisconnected();

private:
    GameManager m_gm;

    void handlePlayRequest(QJsonObject & request);
    void handleChatRequest(QJsonObject & request);

    QTcpSocket *opponentSocket(int playerType, int gameId);
    QTcpSocket *opponentSocket(qintptr socketDescriptor);
};

#endif // GAMESERVER_H
