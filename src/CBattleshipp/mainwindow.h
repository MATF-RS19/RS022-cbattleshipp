#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "player.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private Q_SLOTS:
    void onPlayClicked();
    void onSendClicked();
    void setBoatSize2();
    void setBoatSize3();
    void setBoatSize4();
    void setBoatSize5();
    void recieveServerMsg();

private:
    Ui::MainWindow *ui;
    Player m_player;
    int m_boatSize=0;
};

#endif // MAINWINDOW_H
