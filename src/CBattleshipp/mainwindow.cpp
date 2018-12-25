#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <qmath.h>

#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for(int i = 0; i < 10; i++){
        ui->tableWidget->setColumnWidth(i,32);
        ui->tableWidget->setRowHeight(i,32);
        ui->tableWidget_2->setColumnWidth(i,32);
        ui->tableWidget_2->setRowHeight(i,32);
        }

    connect(ui->playButton, SIGNAL(clicked(bool)), this, SLOT(onPlayClicked()));
    connect(ui->sendButton, SIGNAL(clicked(bool)), this, SLOT(onSendClicked()));
    connect(ui->boatSize2, SIGNAL(clicked(bool)), this, SLOT(setBoatSize2()));
    connect(ui->boatSize3, SIGNAL(clicked(bool)), this, SLOT(setBoatSize3()));
    connect(ui->boatSize4, SIGNAL(clicked(bool)), this, SLOT(setBoatSize4()));
    connect(ui->boatSize5, SIGNAL(clicked(bool)), this, SLOT(setBoatSize5()));
    connect(ui->tableWidget, SIGNAL(cellClicked(int,int)), this, SLOT(setBoat(int,int)));
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onPlayClicked()
{

    m_player.name(ui->lePlayerName->text());

    if (m_player.connectToHost(ui->leServerIP->text())) {
        connect(m_player.m_socket.get(), SIGNAL(readyRead()), this, SLOT(recieveServerMsg()));

        ui->displayManager->setCurrentWidget(ui->gameScreen);
        ui->playerBox->setTitle(m_player.name());

        ui->teNotifications->append("Connected");
        ui->teNotifications->append("Waiting for other player to join ...");

        m_player.m_socket->write(QString("iw2p: " + m_player.name() + "\n").toUtf8());
    }
    else {
        QMessageBox msgBox;
        msgBox.setText("Server could not be found!");
        msgBox.exec();
    }

}



void MainWindow::onSendClicked()
{
    if (!ui->leTextMsg->text().isEmpty()) {
        // print message to you chat
        ui->teChat->append(QString("[" + m_player.name() + "]: " + ui->leTextMsg->text()));

        // send message to other player
        m_player.m_socket->write(QString(QString(m_player.m_playerType) + " " +
                                         QString::number(m_player.m_gameId) +
                                         " chat_msg: " +
                                         ui->leTextMsg->text() + "\n").toUtf8());

        ui->leTextMsg->clear();
    }
}

void MainWindow::setBoatSize2()
{
    m_boatSize=2;
    qDebug() << m_boatSize;
}

void MainWindow::setBoatSize3()
{
    m_boatSize=3;
    qDebug() << m_boatSize;
}

void MainWindow::setBoatSize4()
{
    m_boatSize=4;
    qDebug() << m_boatSize;
}

void MainWindow::setBoatSize5()
{
    m_boatSize=5;
    qDebug() << m_boatSize;
}

void MainWindow::setBoat(int y, int x)
{
    if(m_selectedCell){
        if((qFabs(x - m_x1) == 1 && y - m_y1 == 0) || (qFabs(y - m_y1) == 1 && x - m_x1 == 0)){
            ui->tableWidget->setItem(y, x, new QTableWidgetItem);
            ui->tableWidget->item(y, x)->setBackground(Qt::green);

            // reset marker variable
            m_selectedCell = false;
        }
        else {
        m_x1 = -2;
        m_y1 = -2;
        m_selectedCell = false;
        }
    }
    else{
        if(x != 0){
            ui->tableWidget->setItem(y, x - 1, new QTableWidgetItem);
            ui->tableWidget->item(y, x - 1)->setBackground(Qt::gray);
        }
        if(x != 9){
            ui->tableWidget->setItem(y, x + 1, new QTableWidgetItem);
            ui->tableWidget->item(y, x + 1)->setBackground(Qt::gray);
        }
        if(y != 0){
            ui->tableWidget->setItem(y - 1, x, new QTableWidgetItem);
            ui->tableWidget->item(y - 1, x)->setBackground(Qt::gray);
        }
        if(y != 9){
            ui->tableWidget->setItem(y + 1, x, new QTableWidgetItem);
            ui->tableWidget->item(y + 1, x)->setBackground(Qt::gray);
        }
        m_selectedCell = true;
        m_x1 = x;
        m_y1 = y;
    }
}

void MainWindow::recieveServerMsg()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());

    while (socket->canReadLine()) {
         QString msg = QString::fromUtf8(socket->readLine()).trimmed();
         qDebug() << msg;

         // inform that other player has joined and that game has started
         if (msg.contains("opp_name:")) {
            QStringList request = msg.split(" ");

            qDebug() << msg;

            m_player.m_playerType = request[2].at(0);
            m_player.m_gameId = request[3].toInt();

            ui->opponentBox->setTitle(request[1]);
            ui->teNotifications->append("Player " + request[1] + " joined!");
            ui->teNotifications->append("Game will start soon ...");

            return;
         }

         // print opponent message
         if (msg.contains("chat_msg:")) {
            QStringList request = msg.split(" ");
            QString chatMsg;

            qDebug() << msg;

            for (int i = 1; i < request.size(); i++)
                chatMsg.append(request[i]).append(" ");

            ui->teChat->append(chatMsg);

            return;
         }
    }
}
