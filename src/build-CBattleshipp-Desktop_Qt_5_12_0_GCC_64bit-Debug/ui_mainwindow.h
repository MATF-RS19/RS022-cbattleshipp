/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QStackedWidget *displayManager;
    QWidget *welcomeScreen;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout_6;
    QLineEdit *leServerIP;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_3;
    QLineEdit *lePlayerName;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *playButton;
    QSpacerItem *horizontalSpacer_4;
    QWidget *gameScreen;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QGridLayout *gridLayout_2;
    QPushButton *boatSize3;
    QLabel *countSize5;
    QPushButton *hitButton;
    QPushButton *boatSize4;
    QLabel *countSize4;
    QLabel *countSize2;
    QPushButton *boatSize5;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *boatSize2;
    QLabel *countSize3;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *leTextMsg;
    QPushButton *sendButton;
    QLabel *label_4;
    QTextEdit *teChat;
    QVBoxLayout *verticalLayout_4;
    QTextEdit *teNotifications;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *playerBox;
    QGridLayout *gridLayout_5;
    QTableWidget *tableWidget;
    QGroupBox *opponentBox;
    QGridLayout *gridLayout_4;
    QTableWidget *tableWidget_2;
    QPushButton *ReadyButton;
    QLabel *shipsLeft;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1024, 768);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        displayManager = new QStackedWidget(centralWidget);
        displayManager->setObjectName(QString::fromUtf8("displayManager"));
        welcomeScreen = new QWidget();
        welcomeScreen->setObjectName(QString::fromUtf8("welcomeScreen"));
        verticalLayout_2 = new QVBoxLayout(welcomeScreen);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setSpacing(6);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        leServerIP = new QLineEdit(welcomeScreen);
        leServerIP->setObjectName(QString::fromUtf8("leServerIP"));

        gridLayout_6->addWidget(leServerIP, 0, 2, 1, 1);

        label_2 = new QLabel(welcomeScreen);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_2, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_2, 0, 3, 1, 1);


        verticalLayout_2->addLayout(gridLayout_6);

        label = new QLabel(welcomeScreen);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 500));
        QFont font;
        font.setFamily(QString::fromUtf8("Monospace"));
        font.setPointSize(36);
        font.setBold(false);
        font.setWeight(50);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        label_3 = new QLabel(welcomeScreen);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_3);

        lePlayerName = new QLineEdit(welcomeScreen);
        lePlayerName->setObjectName(QString::fromUtf8("lePlayerName"));

        horizontalLayout->addWidget(lePlayerName);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);


        verticalLayout->addLayout(horizontalLayout);

        playButton = new QPushButton(welcomeScreen);
        playButton->setObjectName(QString::fromUtf8("playButton"));
        playButton->setMinimumSize(QSize(50, 40));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        playButton->setFont(font1);
        playButton->setAutoFillBackground(true);
        playButton->setFlat(false);

        verticalLayout->addWidget(playButton);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_2);

        displayManager->addWidget(welcomeScreen);
        gameScreen = new QWidget();
        gameScreen->setObjectName(QString::fromUtf8("gameScreen"));
        gridLayout = new QGridLayout(gameScreen);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_5 = new QLabel(gameScreen);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        boatSize3 = new QPushButton(gameScreen);
        boatSize3->setObjectName(QString::fromUtf8("boatSize3"));

        gridLayout_2->addWidget(boatSize3, 0, 3, 1, 1);

        countSize5 = new QLabel(gameScreen);
        countSize5->setObjectName(QString::fromUtf8("countSize5"));

        gridLayout_2->addWidget(countSize5, 1, 1, 1, 1);

        hitButton = new QPushButton(gameScreen);
        hitButton->setObjectName(QString::fromUtf8("hitButton"));

        gridLayout_2->addWidget(hitButton, 0, 5, 1, 1);

        boatSize4 = new QPushButton(gameScreen);
        boatSize4->setObjectName(QString::fromUtf8("boatSize4"));

        gridLayout_2->addWidget(boatSize4, 0, 2, 1, 1);

        countSize4 = new QLabel(gameScreen);
        countSize4->setObjectName(QString::fromUtf8("countSize4"));

        gridLayout_2->addWidget(countSize4, 1, 2, 1, 1);

        countSize2 = new QLabel(gameScreen);
        countSize2->setObjectName(QString::fromUtf8("countSize2"));

        gridLayout_2->addWidget(countSize2, 1, 4, 1, 1);

        boatSize5 = new QPushButton(gameScreen);
        boatSize5->setObjectName(QString::fromUtf8("boatSize5"));

        gridLayout_2->addWidget(boatSize5, 0, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 0, 0, 1, 1);

        boatSize2 = new QPushButton(gameScreen);
        boatSize2->setObjectName(QString::fromUtf8("boatSize2"));

        gridLayout_2->addWidget(boatSize2, 0, 4, 1, 1);

        countSize3 = new QLabel(gameScreen);
        countSize3->setObjectName(QString::fromUtf8("countSize3"));

        gridLayout_2->addWidget(countSize3, 1, 3, 1, 1);


        gridLayout->addLayout(gridLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        leTextMsg = new QLineEdit(gameScreen);
        leTextMsg->setObjectName(QString::fromUtf8("leTextMsg"));

        horizontalLayout_3->addWidget(leTextMsg);

        sendButton = new QPushButton(gameScreen);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));

        horizontalLayout_3->addWidget(sendButton);


        gridLayout->addLayout(horizontalLayout_3, 4, 0, 1, 1);

        label_4 = new QLabel(gameScreen);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 1, 1, 1);

        teChat = new QTextEdit(gameScreen);
        teChat->setObjectName(QString::fromUtf8("teChat"));
        teChat->setReadOnly(true);

        gridLayout->addWidget(teChat, 3, 0, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        teNotifications = new QTextEdit(gameScreen);
        teNotifications->setObjectName(QString::fromUtf8("teNotifications"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(teNotifications->sizePolicy().hasHeightForWidth());
        teNotifications->setSizePolicy(sizePolicy);
        teNotifications->setUndoRedoEnabled(false);
        teNotifications->setReadOnly(true);
        teNotifications->setTextInteractionFlags(Qt::NoTextInteraction);

        verticalLayout_4->addWidget(teNotifications);


        gridLayout->addLayout(verticalLayout_4, 3, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        playerBox = new QGroupBox(gameScreen);
        playerBox->setObjectName(QString::fromUtf8("playerBox"));
        playerBox->setMinimumSize(QSize(0, 400));
        gridLayout_5 = new QGridLayout(playerBox);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        tableWidget = new QTableWidget(playerBox);
        if (tableWidget->columnCount() < 10)
            tableWidget->setColumnCount(10);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        if (tableWidget->rowCount() < 10)
            tableWidget->setRowCount(10);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(8, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(9, __qtablewidgetitem19);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidget->setTextElideMode(Qt::ElideLeft);

        gridLayout_5->addWidget(tableWidget, 0, 0, 1, 1);


        horizontalLayout_4->addWidget(playerBox);

        opponentBox = new QGroupBox(gameScreen);
        opponentBox->setObjectName(QString::fromUtf8("opponentBox"));
        opponentBox->setMinimumSize(QSize(0, 400));
        gridLayout_4 = new QGridLayout(opponentBox);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        tableWidget_2 = new QTableWidget(opponentBox);
        if (tableWidget_2->columnCount() < 10)
            tableWidget_2->setColumnCount(10);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(4, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(5, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(6, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(7, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(8, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(9, __qtablewidgetitem29);
        if (tableWidget_2->rowCount() < 10)
            tableWidget_2->setRowCount(10);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(0, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(1, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(2, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(3, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(4, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(5, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(6, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(7, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(8, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(9, __qtablewidgetitem39);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));
        tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_2->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidget_2->setTextElideMode(Qt::ElideLeft);

        gridLayout_4->addWidget(tableWidget_2, 0, 0, 1, 1);


        horizontalLayout_4->addWidget(opponentBox);


        gridLayout->addLayout(horizontalLayout_4, 0, 0, 1, 2);

        ReadyButton = new QPushButton(gameScreen);
        ReadyButton->setObjectName(QString::fromUtf8("ReadyButton"));

        gridLayout->addWidget(ReadyButton, 4, 1, 1, 1);

        shipsLeft = new QLabel(gameScreen);
        shipsLeft->setObjectName(QString::fromUtf8("shipsLeft"));

        gridLayout->addWidget(shipsLeft, 1, 1, 1, 1);

        displayManager->addWidget(gameScreen);

        gridLayout_3->addWidget(displayManager, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "cbattleshipp", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Server IP", nullptr));
        label->setText(QApplication::translate("MainWindow", "cbattleshipp", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Player name", nullptr));
        playButton->setText(QApplication::translate("MainWindow", "Play", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Chat", nullptr));
        boatSize3->setText(QApplication::translate("MainWindow", "3", nullptr));
        countSize5->setText(QApplication::translate("MainWindow", "1", nullptr));
        hitButton->setText(QApplication::translate("MainWindow", "Hit", nullptr));
        boatSize4->setText(QApplication::translate("MainWindow", "4", nullptr));
        countSize4->setText(QApplication::translate("MainWindow", "2", nullptr));
        countSize2->setText(QApplication::translate("MainWindow", "4", nullptr));
        boatSize5->setText(QApplication::translate("MainWindow", "5", nullptr));
        boatSize2->setText(QApplication::translate("MainWindow", "2", nullptr));
        countSize3->setText(QApplication::translate("MainWindow", "3", nullptr));
        sendButton->setText(QApplication::translate("MainWindow", "Send", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Notifications", nullptr));
        playerBox->setTitle(QApplication::translate("MainWindow", "PlayerName", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "3", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "4", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "5", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "6", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "7", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "8", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "9", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "10", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem12->setText(QApplication::translate("MainWindow", "3", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem13->setText(QApplication::translate("MainWindow", "4", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem14->setText(QApplication::translate("MainWindow", "5", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem15->setText(QApplication::translate("MainWindow", "6", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem16->setText(QApplication::translate("MainWindow", "7", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem17->setText(QApplication::translate("MainWindow", "8", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget->verticalHeaderItem(8);
        ___qtablewidgetitem18->setText(QApplication::translate("MainWindow", "9", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget->verticalHeaderItem(9);
        ___qtablewidgetitem19->setText(QApplication::translate("MainWindow", "10", nullptr));
        opponentBox->setTitle(QApplication::translate("MainWindow", "Opponent Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem20->setText(QApplication::translate("MainWindow", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem21->setText(QApplication::translate("MainWindow", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem22->setText(QApplication::translate("MainWindow", "3", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget_2->horizontalHeaderItem(3);
        ___qtablewidgetitem23->setText(QApplication::translate("MainWindow", "4", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget_2->horizontalHeaderItem(4);
        ___qtablewidgetitem24->setText(QApplication::translate("MainWindow", "5", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget_2->horizontalHeaderItem(5);
        ___qtablewidgetitem25->setText(QApplication::translate("MainWindow", "6", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget_2->horizontalHeaderItem(6);
        ___qtablewidgetitem26->setText(QApplication::translate("MainWindow", "7", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget_2->horizontalHeaderItem(7);
        ___qtablewidgetitem27->setText(QApplication::translate("MainWindow", "8", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget_2->horizontalHeaderItem(8);
        ___qtablewidgetitem28->setText(QApplication::translate("MainWindow", "9", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidget_2->horizontalHeaderItem(9);
        ___qtablewidgetitem29->setText(QApplication::translate("MainWindow", "10", nullptr));
        QTableWidgetItem *___qtablewidgetitem30 = tableWidget_2->verticalHeaderItem(0);
        ___qtablewidgetitem30->setText(QApplication::translate("MainWindow", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem31 = tableWidget_2->verticalHeaderItem(1);
        ___qtablewidgetitem31->setText(QApplication::translate("MainWindow", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidget_2->verticalHeaderItem(2);
        ___qtablewidgetitem32->setText(QApplication::translate("MainWindow", "3", nullptr));
        QTableWidgetItem *___qtablewidgetitem33 = tableWidget_2->verticalHeaderItem(3);
        ___qtablewidgetitem33->setText(QApplication::translate("MainWindow", "4", nullptr));
        QTableWidgetItem *___qtablewidgetitem34 = tableWidget_2->verticalHeaderItem(4);
        ___qtablewidgetitem34->setText(QApplication::translate("MainWindow", "5", nullptr));
        QTableWidgetItem *___qtablewidgetitem35 = tableWidget_2->verticalHeaderItem(5);
        ___qtablewidgetitem35->setText(QApplication::translate("MainWindow", "6", nullptr));
        QTableWidgetItem *___qtablewidgetitem36 = tableWidget_2->verticalHeaderItem(6);
        ___qtablewidgetitem36->setText(QApplication::translate("MainWindow", "7", nullptr));
        QTableWidgetItem *___qtablewidgetitem37 = tableWidget_2->verticalHeaderItem(7);
        ___qtablewidgetitem37->setText(QApplication::translate("MainWindow", "8", nullptr));
        QTableWidgetItem *___qtablewidgetitem38 = tableWidget_2->verticalHeaderItem(8);
        ___qtablewidgetitem38->setText(QApplication::translate("MainWindow", "9", nullptr));
        QTableWidgetItem *___qtablewidgetitem39 = tableWidget_2->verticalHeaderItem(9);
        ___qtablewidgetitem39->setText(QApplication::translate("MainWindow", "10", nullptr));
        ReadyButton->setText(QApplication::translate("MainWindow", "Ready to play!", nullptr));
        shipsLeft->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
