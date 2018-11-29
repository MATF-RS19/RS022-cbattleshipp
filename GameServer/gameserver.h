#ifndef GAMESERVER_H_
#define GAMESERVER_H_

#include <QTcpServer>

class GameServer : public QTcpServer {
    Q_OBJECT

public:
    GameServer(QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void openSession();
};

#endif // GAMESERVER_H_
