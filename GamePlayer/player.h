#ifndef PLAYER_H_
#define PLAYER_H_

#include <QTcpSocket>

class Player : public QObject {
    Q_OBJECT

public:
    Player(QObject *parent = nullptr);

public slots:
    void connect(QString ipAddress, quint16 port);

private:
    QTcpSocket *tcpSocket = nullptr;
    QString ipAddress;
    quint16 port;
};

#endif // PLAYER_H_
