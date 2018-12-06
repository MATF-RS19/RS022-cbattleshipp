#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QTcpSocket>

class Player : public QObject
{
    Q_OBJECT

public:
    explicit Player(QObject *parent = nullptr);

    bool connectToHost(const QString & ipAddress);

    QTcpSocket *socket() const;

    QString name() const;
    void name(const QString & name);

public Q_SLOTS:

private:
    QTcpSocket *m_socket = nullptr;
    QString m_name;
};

#endif // PLAYER_H
