#include "gameinterface.h"
#include "ui_gameinterface.h"

GameInterface::GameInterface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameInterface)
{
    ui->setupUi(this);

    connect(ui->playButton, SIGNAL(clicked(bool)), this, SLOT(onPlayClicked()));

    Player player;
}

GameInterface::~GameInterface()
{
    delete ui;
}

void GameInterface::onPlayClicked()
{
    if (player.connectToHost(ui->serverIp->text())) {
        ui->gameControler->setCurrentWidget(ui->game_screen);
        ui->connectionStatus->setText("Connection secure!");
    }
    else // TODO: handle errors with a error window
        qDebug() << "$ Handle error here!";
}
