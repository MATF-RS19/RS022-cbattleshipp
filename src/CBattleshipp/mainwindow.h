#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "player.h"

#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonObject>

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

    void onCellClick(int y, int x);
    void onReadyToPlayButtonClicked();

    void recieveServerMsg();

private:
    Ui::MainWindow *ui;
    Player m_player;

    bool m_selectedCell = false;

    int m_boatSize=0;

    int m_x1 = -2;
    int m_y1 = -2;

    int m_availableShipsSize2 = 4;
    int m_availableShipsSize3 = 3;
    int m_availableShipsSize4 = 2;
    int m_availableShipsSize5 = 1;

    // player turn variable false = player, true = opponent
    bool m_turn = false;


    void deleteGray(int y, int x);
    void reduceBoatCount();

    // server handle response methods
    void handlePlayResponse(QJsonObject & response);
    void handleChatResponse(QJsonObject & response);

    void handleOpponentDisconnectedResponse(QJsonObject & response);

    void handleWaitOpponentResponse(QJsonObject & response);
    void handleReadyOpponentResponse(QJsonObject & response);

    void handleGameStartResponse(QJsonObject & response);
};

#endif // MAINWINDOW_H
