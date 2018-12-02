#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QTcpSocket>

#define GAME_PORT 5050

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);

    bool connectToHost(QString ipAddress);

private:
   QTcpSocket *m_socket;
};

#endif // PLAYER_H
