#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->playButton, SIGNAL(clicked(bool)), this, SLOT(onPlayClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onPlayClicked()
{
    m_player.name(ui->lePlayerName->text());

    if (m_player.connectToHost(ui->leServerIP->text())) {

        connect(m_player.socket(), SIGNAL(readyRead()), this, SLOT(recieveServerMsg()));
        ui->displayManager->setCurrentWidget(ui->gameScreen);
        ui->playerBox->setTitle(m_player.name());

        ui->teNotifications->append("Connected");
        ui->teNotifications->append("Waiting for other player to join ...");

        m_player.socket()->write(QString("iw2p: name: " + m_player.name() + " \n").toUtf8());
    }
    else { // TODO: handle error with an error window popup
        qDebug() << "$ Connection failed";
    }

}

void MainWindow::recieveServerMsg()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());

    while (socket->canReadLine()) {
         QString msg = QString::fromUtf8(socket->readLine()).trimmed();
         qDebug() << msg;

         // FIXME: opponent name is not sent correctly
         if (msg.contains("yycp:")) {
            QStringList request = msg.split(" ");
            for (int i = 0; i < request.size(); i++) {
                qDebug() << request.at(i);
            }

            //ui->opponentBox->setTitle(request[2]);
            //ui->teNotifications->append("Player " + request[2] + " joined!");
            //ui->teNotifications->append("Game will start soon ...");

            ui->teNotifications->append("Player joined!");
            ui->teNotifications->append("Game will start soon ...");
         }
    }
}
