#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QTcpSocket>

class Player : public QObject
{
    Q_OBJECT

public:
    explicit Player(QObject *parent = nullptr);

    QTcpSocket *socket() const;
    void socket(QTcpSocket *socket);

    QString name() const;
    void name(const QString &name);

protected:
    QTcpSocket *m_socket;
    QString m_name;
};

#endif // PLAYER_H
