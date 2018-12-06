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
    void recieveServerMsg();

private:
    Ui::MainWindow *ui;
    Player m_player;
};

#endif // MAINWINDOW_H
