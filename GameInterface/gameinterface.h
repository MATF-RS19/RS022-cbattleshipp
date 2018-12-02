#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include "player.h"

#include <QMainWindow>

namespace Ui {
class GameInterface;
}

class GameInterface : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameInterface(QWidget *parent = nullptr);
    ~GameInterface();

private slots:
    void onPlayClicked();

private:
    Ui::GameInterface *ui;
    Player player;

};

#endif // GAMEINTERFACE_H
