#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtMath>
#include <QMessageBox>
#include <QString>
#include <QJsonArray>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QFontDatabase>

#define CELL_SIZE 40

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setUiFonts();

    setCellSize();

    // set up table items
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            ui->playerShips->setItem(i, j, new QTableWidgetItem);
            ui->opponentShips->setItem(i, j, new QTableWidgetItem);
        }
    }

    disablePlayerButtons();

    // connecting button's signals and corresponding slots
    connect(ui->playButton, SIGNAL(clicked(bool)), this, SLOT(onPlayClicked()));
    connect(ui->sendButton, SIGNAL(clicked(bool)), this, SLOT(onSendClicked()));

    connect(ui->boatSize2, SIGNAL(clicked(bool)), this, SLOT(setBoatSize2()));
    connect(ui->boatSize3, SIGNAL(clicked(bool)), this, SLOT(setBoatSize3()));
    connect(ui->boatSize4, SIGNAL(clicked(bool)), this, SLOT(setBoatSize4()));
    connect(ui->boatSize5, SIGNAL(clicked(bool)), this, SLOT(setBoatSize5()));

    connect(ui->playerShips, SIGNAL(cellClicked(int,int)), this, SLOT(onCellClick(int,int)));

    connect(ui->ReadyButton, SIGNAL(clicked(bool)), this, SLOT(onReadyToPlayButtonClicked()));
    connect(ui->hitButton, SIGNAL(clicked(bool)), this, SLOT(onHitButtonClicked()));
    connect(ui->opponentShips, SIGNAL(cellClicked(int, int)), this, SLOT(onOpponentCellClicked(int, int)));

    connect(ui->quitButton, SIGNAL(clicked(bool)), this, SLOT(onQuitClicked()));

    // set application background
    QPixmap background(":/images/water.png");

    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onPlayClicked()
{
    // set player name
    m_player.name(ui->lePlayerName->text());

    if (m_player.connectToHost(ui->leServerIP->text())) {
        connect(m_player.m_socket.get(), SIGNAL(readyRead()), this, SLOT(recieveServerMsg()));

        ui->displayManager->setCurrentWidget(ui->gameScreen);
        ui->playerBox->setTitle(m_player.name());

        ui->teNotifications->append("Connected");
        ui->teNotifications->append("Waiting for other player to join ...");

        // send play request
        QJsonObject request;
        request.insert("iw2p", 1);
        request.insert("name", m_player.name());

        QJsonDocument document(request);

        m_player.m_socket->write(document.toJson());
    }
    else {
        QMessageBox msgBox;
        msgBox.setText("Server could not be found!");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }
}


void MainWindow::onSendClicked()
{
    // send chat request
    if (!ui->leTextMsg->text().isEmpty()) {
        // print message to your chat box
        ui->teChat->append(QString("[" + m_player.name() + "]: " + ui->leTextMsg->text()));

        // send message to other player
        // message format [player_name]: msg_content
        QJsonObject request;
        request.insert("chat_msg", "[" + m_player.name() + "]: " + ui->leTextMsg->text());
        request.insert("player_type", m_player.m_playerType);
        request.insert("game_id", m_player.m_gameId);

        QJsonDocument doc(request);
        m_player.m_socket->write(doc.toJson());

        ui->leTextMsg->clear();
    }
}


void MainWindow::setBoatSize2()
{
    if(m_availableShipsSize2 > 0)
        m_boatSize=2;
    qDebug() << m_boatSize;
}


void MainWindow::setBoatSize3()
{
    if(m_availableShipsSize3 > 0)
        m_boatSize=3;
    qDebug() << m_boatSize;
}


void MainWindow::setBoatSize4()
{
    if(m_availableShipsSize4 > 0)
        m_boatSize=4;
    qDebug() << m_boatSize;
}


void MainWindow::setBoatSize5()
{
    if(m_availableShipsSize5 > 0)
        m_boatSize=5;
    qDebug() << m_boatSize;
}


void MainWindow::onCellClick(int y, int x)
{
    //user must first click on ship size before placing it
    if(m_boatSize!=0){
        bool cellUsed = false;
        //second click
        if(m_selectedCell){
            //set boat
            if((qFabs(x - m_x1) == 1 && y - m_y1 == 0) || (qFabs(y - m_y1) == 1 && x - m_x1 == 0)){
                //right
                if(x > m_x1 && m_x1 + m_boatSize - 1 <= 9){
                    for(int i = 0; i < m_boatSize; i++){
                        cellUsed = cellUsed || ui->playerShips->item(m_y1, m_x1 + i)->isSelected();
                    }
                    if(!cellUsed){
                        for(int i = 0; i < m_boatSize; i++){
                            ui->playerShips->item(m_y1, m_x1 + i)->setSelected(true);
                        }
                        reduceBoatCount();
                    }
                }
                //left
                if(x < m_x1 && m_x1 - m_boatSize + 1 >= 0){
                    for(int i = 0; i < m_boatSize; i++){
                        cellUsed = cellUsed || ui->playerShips->item(m_y1, m_x1 - i)->isSelected();
                    }
                    if(!cellUsed){
                        for(int i = 0; i < m_boatSize; i++){
                            ui->playerShips->item(m_y1, m_x1 - i)->setSelected(true);
                        }
                        reduceBoatCount();
                    }
                }
                //down
                if(y > m_y1 && m_y1 + m_boatSize - 1 <= 9){
                    for(int i = 0; i < m_boatSize; i++){
                        cellUsed = cellUsed || ui->playerShips->item(m_y1 + i, m_x1)->isSelected();
                    }
                    if(!cellUsed){
                        for(int i = 0; i < m_boatSize; i++){
                            ui->playerShips->item(m_y1 + i, m_x1)->setSelected(true);
                        }
                        reduceBoatCount();
                    }
                }
                //up
                if(y < m_y1 && m_y1 - m_boatSize + 1 >= 0){
                    for(int i = 0; i < m_boatSize; i++){
                        cellUsed = cellUsed || ui->playerShips->item(m_y1 - i, m_x1)->isSelected();
                    }
                    if(!cellUsed){
                        for(int i = 0; i < m_boatSize; i++){
                            ui->playerShips->item(m_y1 - i, m_x1)->setSelected(true);
                        }
                        reduceBoatCount();
                    }
                }

                // reset marker variable
                deleteGray(m_y1,m_x1);
                m_selectedCell = false;
                m_boatSize = 0;
            }
            else {
                deleteGray(m_y1,m_x1);
                m_x1 = -2;
                m_y1 = -2;
                m_selectedCell = false;
            }

        }
        //first click
        else if(!ui->playerShips->item(y, x)->isSelected()){
            if(x != 0){
                ui->playerShips->item(y, x - 1)->setBackground(Qt::gray);
            }
            if(x != 9){
                ui->playerShips->item(y, x + 1)->setBackground(Qt::gray);
            }
            if(y != 0){
                ui->playerShips->item(y - 1, x)->setBackground(Qt::gray);
            }
            if(y != 9){
                ui->playerShips->item(y + 1, x)->setBackground(Qt::gray);
            }
            m_selectedCell = true;
            m_x1 = x;
            m_y1 = y;
        }
    }
}

void MainWindow::reduceBoatCount()
{
    if(m_boatSize == 2){
        m_availableShipsSize2--;
        ui->countSize2->setText(QString::number(m_availableShipsSize2));
        qDebug() << m_availableShipsSize2 << "brodova2";
    }
    if(m_boatSize == 3){
        m_availableShipsSize3--;
        ui->countSize3->setText(QString::number(m_availableShipsSize3));
        qDebug() << m_availableShipsSize3 << "brodova3";
    }
    if(m_boatSize == 4){
        m_availableShipsSize4--;
        ui->countSize4->setText(QString::number(m_availableShipsSize4));
        qDebug() << m_availableShipsSize4 << "brodova4";
    }
    if(m_boatSize == 5){
        m_availableShipsSize5--;
        ui->countSize5->setText(QString::number(m_availableShipsSize5));
        qDebug() << m_availableShipsSize5 << "brodova5";
    }
}

void MainWindow::deleteGray(int y, int x){
    //right
    if(x != 9)
        ui->playerShips->item(y, x + 1)->setBackground(Qt::white);
    //left
    if(x != 0)
        ui->playerShips->item(y, x - 1)->setBackground(Qt::white);
    //down
    if(y != 9)
        ui->playerShips->item(y + 1, x)->setBackground(Qt::white);
    //up
    if(y != 0)
        ui->playerShips->item(y - 1, x)->setBackground(Qt::white);
}


void MainWindow::recieveServerMsg()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());

    QJsonDocument msg = QJsonDocument::fromJson(socket->readAll());
    QJsonObject response = msg.object();

    qDebug() << response;

    if (response.isEmpty())
        return;

    // server will send one response at a time = return statements
    if (response.contains("ucp")) {
        handlePlayResponse(response);
        return;
    }

    if (response.contains("chat_msg")) {
        handleChatResponse(response);
        return;
    }

    if (response.contains("od")) {
        handleOpponentDisconnectedResponse(response);
        return;
    }

    if (response.contains("wait_opp")) {
        handleWaitOpponentResponse(response);
        return;
    }

    if (response.contains("opp_ready")) {
        handleReadyOpponentResponse(response);
        return;
    }

    if (response.contains("start_game")) {
        handleGameStartResponse(response);
        return;
    }

    if (response.contains("attack"))
        handleAttackResponse(response);

    if (response.contains("if_hit"))
        handleIfHitResponse(response);
}

void MainWindow::handlePlayResponse(QJsonObject & response)
{
    // set player type and game id
    m_player.m_playerType = response.value("player_type").toInt();
    m_player.m_gameId = response.value("game_id").toInt();

    // inform that other player has joined and that game has started
    ui->teNotifications->append("Player " + response.value("opp_name").toString() + " joined!");
    ui->opponentBox->setTitle(response.value("opp_name").toString());

    ui->teNotifications->append("Place your boats and then click on Ready.");

    // enable disabled buttons
    ui->playerBox->setEnabled(true);
    ui->ReadyButton->setEnabled(true);
    ui->boatSize2->setEnabled(true);
    ui->boatSize3->setEnabled(true);
    ui->boatSize4->setEnabled(true);
    ui->boatSize5->setEnabled(true);
}

void MainWindow::handleChatResponse(QJsonObject & response)
{
    ui->teChat->append(response.value("chat_msg").toString());
}

void MainWindow::handleOpponentDisconnectedResponse(QJsonObject & response)
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText("Opponent has left the game. Play again?");

    QAbstractButton* buttonYes = msgBox.addButton(tr("Yes"), QMessageBox::YesRole);
    QAbstractButton* buttonNo = msgBox.addButton(tr("Quit"), QMessageBox::NoRole);

    ui->teNotifications->clear();
    ui->teChat->clear();

    msgBox.exec();

    QJsonObject msg;

    if (msgBox.clickedButton() == buttonYes) {
        ui->opponentBox->setTitle("Opponent name");
        ui->teNotifications->append("Wait for other player to joint the game.");

        msg.insert("play_again", 1);
        msg.insert("player_type", m_player.m_playerType);
        msg.insert("game_id", m_player.m_gameId);

        QJsonDocument doc(msg);
        m_player.m_socket->write(doc.toJson());

        // remove player's ships
        for(int i = 0; i < ui->playerShips->rowCount(); ++i) {
            for (int j = 0; j < ui->playerShips->columnCount(); ++j)
                if (ui->playerShips->item(i,j)->isSelected())
                    ui->playerShips->item(i, j)->setSelected(false);
        }

    }
    if (msgBox.clickedButton() == buttonNo) {
        msg.insert("quit", 1);
        QJsonDocument doc(msg);
        m_player.m_socket->write(doc.toJson());

        exit(EXIT_SUCCESS);
    }
}

void MainWindow::handleWaitOpponentResponse(QJsonObject &response)
{
    ui->teNotifications->append("Wait for " + response.value("opp_name").toString() + " to get ready.");
}

void MainWindow::handleReadyOpponentResponse(QJsonObject &response)
{
    ui->teNotifications->append(response.value("opp_name").toString() + " is ready.");
}

void MainWindow::handleGameStartResponse(QJsonObject &response)
{
   ui->opponentBox->setEnabled(true);

   ui->teNotifications->append("Game starts!");
   ui->teNotifications->append(response.value("turn").toString() + " turn.");

   // set player turn
   if (!response.value("turn").toString().compare(m_player.m_name)) {
       m_turn = true;

   }
   else {
       m_turn = false;
       ui->hitButton->setEnabled(true);
   }
}

void MainWindow::setUiFonts()
{
    // include fonts
    QFontDatabase::addApplicationFont(":/fonts/ArcadeClassic.ttf");

    QFont Arcade("Arcade Classic", 16, QFont::Normal);

    // main screen
    ui->laServerIP->setFont(Arcade);
    ui->laPlayerName->setFont(Arcade);

    Arcade.setPixelSize(34);
    ui->playButton->setFont(Arcade);

    Arcade.setPixelSize(120);
    ui->laGameTitle->setFont(Arcade);

    // player's boxes
    Arcade.setPixelSize(24);
    ui->playerBox->setFont(Arcade);
    ui->opponentBox->setFont(Arcade);

    // available ships counters and corresponding buttons
    Arcade.setPixelSize(18);
    ui->laAvailableShips->setFont(Arcade);
    ui->countSize2->setFont(Arcade);
    ui->countSize3->setFont(Arcade);
    ui->countSize4->setFont(Arcade);
    ui->countSize5->setFont(Arcade);

    ui->boatSize2->setFont(Arcade);
    ui->boatSize3->setFont(Arcade);
    ui->boatSize4->setFont(Arcade);
    ui->boatSize5->setFont(Arcade);

    // ship counters
    Arcade.setPixelSize(24);
    ui->laPlayersShips->setFont(Arcade);
    ui->laPlayerShipsLeft->setFont(Arcade);

    ui->laOpponentShips->setFont(Arcade);
    ui->laOpponentShipsLeft->setFont(Arcade);

    // buttons
    ui->hitButton->setFont(Arcade);
    ui->ReadyButton->setFont(Arcade);
    ui->quitButton->setFont(Arcade);
    ui->sendButton->setFont(Arcade);

    // chat and notification labels
    ui->laChat->setFont(Arcade);
    ui->laNotifications->setFont(Arcade);
}

void MainWindow::setCellSize()
{
    // set player's cells width and height
    ui->playerShips->horizontalHeader()->setMinimumSectionSize(CELL_SIZE);
    ui->playerShips->verticalHeader()->setMinimumSectionSize(CELL_SIZE);
    ui->playerShips->horizontalHeader()->setDefaultSectionSize(CELL_SIZE);
    ui->playerShips->verticalHeader()->setDefaultSectionSize(CELL_SIZE);

    // set opponent's cells width and height
    ui->opponentShips->horizontalHeader()->setMinimumSectionSize(CELL_SIZE);
    ui->opponentShips->verticalHeader()->setMinimumSectionSize(CELL_SIZE);
    ui->opponentShips->horizontalHeader()->setDefaultSectionSize(CELL_SIZE);
    ui->opponentShips->verticalHeader()->setDefaultSectionSize(CELL_SIZE);
}


void MainWindow::disablePlayerButtons()
{
    // disable game buttons before game starts
    ui->playerBox->setDisabled(true);
    ui->opponentBox->setDisabled(true);
    ui->hitButton->setDisabled(true);
    ui->ReadyButton->setDisabled(true);
    ui->boatSize2->setDisabled(true);
    ui->boatSize3->setDisabled(true);
    ui->boatSize4->setDisabled(true);
    ui->boatSize5->setDisabled(true);
}


void MainWindow::onReadyToPlayButtonClicked()
{
    //Check if all ships are set up
    if(m_availableShipsSize2 != 0 || m_availableShipsSize3 !=0 || m_availableShipsSize4 != 0 || m_availableShipsSize5 != 0 ){

        QMessageBox msgBox;
        msgBox.setText("Ships are not set up!");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();

    }else{
        //Send to server map of ships
        QJsonObject mapOfShips;

        mapOfShips.insert("ready", 1);
        mapOfShips.insert("gameId", m_player.m_gameId);
        mapOfShips.insert("playerType", m_player.m_playerType);

        for(int i=0 ; i<ui->playerShips->rowCount(); ++i){

            QJsonArray niz;

            for (int j = 0; j < ui->playerShips->columnCount(); ++j) {

                if(ui->playerShips->item(i,j)->isSelected()){
                    niz.append(1);
                }else{
                    niz.append(0);
                }

            }
            mapOfShips.insert(QString::number(i), niz);
        }

        QJsonDocument doc(mapOfShips);
        m_player.m_socket->write(doc.toJson());

        qDebug() << doc;

        // disable ReadyButton so player cannot send multiple ready requests
        ui->ReadyButton->setDisabled(true);
    }
}

void MainWindow::onOpponentCellClicked(int y, int x)
{
    m_opponentSelectedCell = true;

    if (m_ox == x && m_oy == y) {
        QMessageBox msgBox;
        msgBox.setText("You can't hit the same spot twice!");
        msgBox.setIcon(QMessageBox::Icon::Critical);

        msgBox.exec();

        m_ox = -1;
        m_oy = -1;
    }
    else {
        m_ox = x;
        m_oy = y;
    }
}

void MainWindow::onQuitClicked()
{
    QMessageBox msgBox;
    msgBox.setText("Are you sure?");
    msgBox.setIcon(QMessageBox::Warning);

    QAbstractButton* buttonYes = msgBox.addButton(tr("Yes"), QMessageBox::YesRole);
    QAbstractButton* buttonNo = msgBox.addButton(tr("No"), QMessageBox::NoRole);

    msgBox.exec();

    if (msgBox.clickedButton() == buttonYes) {
        exit(EXIT_SUCCESS);
    }

    if (msgBox.clickedButton() == buttonNo) {
        return;
    }

}

void MainWindow::onHitButtonClicked()
{
    if(m_opponentSelectedCell){
           QJsonObject playerHit;
           playerHit.insert("hit", 1);
           playerHit.insert("x", m_ox);
           playerHit.insert("y", m_oy);

           playerHit.insert("gameId", m_player.m_gameId);
           playerHit.insert("playerType", m_player.m_playerType);

           m_turn = false;
           ui->hitButton->setEnabled(false);

           QJsonDocument doc(playerHit);
           m_player.m_socket->write(doc.toJson());

    }else{

        QMessageBox msgBox;
        msgBox.setText("Choose a cell!");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }
}

void MainWindow::handleAttackResponse(QJsonObject & response)
{
    // read hit info
    m_oppHitX = response.value("x").toInt();
    m_oppHitY = response.value("y").toInt();

    if(response.contains("yah")){

        ui->teNotifications->append("You are hit!");
        m_player.m_shipsLeft--;
        ui->laPlayerShipsLeft->setText(QString::number(m_player.m_shipsLeft));

        // unselect ship, and color it
        ui->playerShips->item(m_oppHitY, m_oppHitX)->setSelected(false);
        ui->playerShips->item(m_oppHitY, m_oppHitX)->setBackgroundColor(Qt::red);

        if(m_player.m_shipsLeft == 0){
            QMessageBox msgBox;
            msgBox.setText(m_player.name() + " you lost the game!");
            msgBox.setIcon(QMessageBox::Information);
            msgBox.exec();
        }

    }else{

        ui->teNotifications->append("You are not hit!");
        m_turn = true;
        ui->hitButton->setEnabled(true);

        ui->playerShips->item(m_oppHitY, m_oppHitX)->setBackgroundColor(Qt::gray);
    }
}

void MainWindow::handleIfHitResponse(QJsonObject & response)
{
    if(response.contains("great_attack")){

        ui->hitButton->setEnabled(true);
        m_turn = true;
        ui->teNotifications->append("You hit your opponent!");
        ui->opponentShips->item(m_oy, m_ox)->setBackgroundColor(Qt::red);
        m_player.m_greatAttack++;

        if(m_player.m_greatAttack == 30){
            QMessageBox msgBox;
            msgBox.setText(m_player.name() + " you are winner!");
            msgBox.setIcon(QMessageBox::Information);
            msgBox.exec();
        }
    }else{
        ui->teNotifications->append("You did't hit your opponent!");
        ui->opponentShips->item(m_oy, m_ox)->setBackgroundColor(Qt::gray);
    }
}
