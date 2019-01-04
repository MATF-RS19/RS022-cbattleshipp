#ifndef GAMESERVER_H
#define GAMESERVER_H

#include "gamemanager.h"

#include <QObject>
#include <QTcpServer>
#include <QJsonDocument>
#include <QJsonObject>

#define GAME_PORT 5050

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
    void playerDisconnected();

private:
    GameManager m_gm;

    int m_playerIdGenerator = 0;

    void handlePlayRequest(QJsonObject & request);
    void handleChatRequest(QJsonObject & request);
    void handlePlayAgainRequest(QJsonObject & request);
    void handleQuitRequest(QJsonObject & request);
    void handleReadyRequest(QJsonObject & request);
    void handleHitRequest(QJsonObject & request);
};

#endif // GAMESERVER_H
