#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "player.h"

#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonObject>

namespace Ui {
class MainWindow;
}

enum GameOutcome {
    SUCCESSFUL = 42,
    FAILURE = -1
};

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
    void onHitButtonClicked();
    void onOpponentCellClicked(int y, int x);

    void onQuitClicked();

    void recieveServerMsg();

private:
    Ui::MainWindow *ui;
    Player m_player;

    bool m_selectedCell = false;
    bool m_opponentSelectedCell = false;

    int m_boatSize=0;

    // player's coordinates
    int m_x1 = -2;
    int m_y1 = -2;

    // opponent's coordinates
    int m_ox = -1;
    int m_oy = -1;

    int m_oldX = -1;
    int m_oldY = -1;

    // opponent's hit coordinates
    int m_oppHitX = -1;
    int m_oppHitY = -1;

    int m_availableShipsSize2 = 4;
    int m_availableShipsSize3 = 3;
    int m_availableShipsSize4 = 2;
    int m_availableShipsSize5 = 1;

    // player turn variable false = player, true = opponent
    bool m_turn = false;


    void deleteGray(int y, int x);
    void reduceBoatCount();
    void resetUi();

    // server handle response methods
    void handlePlayResponse(QJsonObject & response);
    void handleChatResponse(QJsonObject & response);

    void handleOpponentDisconnectedResponse(QJsonObject & response);

    void handleWaitOpponentResponse(QJsonObject & response);
    void handleReadyOpponentResponse(QJsonObject & response);
    void handleAttackResponse(QJsonObject & response);
    void handleIfHitResponse(QJsonObject & response);

    void handleGameStartResponse(QJsonObject & response);

    void setUiFonts();
    void setCellSize();
    void disablePlayerButtons();
};

#endif // MAINWINDOW_H
