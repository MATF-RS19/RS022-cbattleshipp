#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->playButton, SIGNAL(clicked(bool)), this, SLOT(onPlayClicked()));
    connect(ui->sendButton, SIGNAL(clicked(bool)), this, SLOT(onSendClicked()));
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
    else { // TODO: handle error with an error window popup
        qDebug() << "$ Connection failed";
    }

}

void MainWindow::onSendClicked()
{
    if (!ui->leTextMsg->text().isEmpty()) {
        // print message to you chat
        ui->teChat->append(ui->leTextMsg->text());

        // send message to other player
        m_player.m_socket->write(QString(QString(m_player.m_playerType) +
                                         QString(m_player.m_gameId) +
                                         " chat_msg: " +
                                         ui->leTextMsg->text() + "\n").toUtf8());

        ui->leTextMsg->clear();
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

            m_player.m_playerType = request[2].at(0);
            m_player.m_gameId = request[2].at(1).unicode();

            ui->opponentBox->setTitle(request[1]);
            ui->teNotifications->append("Player " + request[1] + " joined!");
            ui->teNotifications->append("Game will start soon ...");

            return;
         }

         // NOTE: chat is not working on server side
         if (msg.contains("chat_msg:")) {
            // FIXME: change sending message format
            ui->teChat->append(msg);

            return;
         }
    }
}
