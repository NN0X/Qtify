#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->setStyleSheet(" color: white;background-color: #001315;");
    layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);

    searchMusicYT = new SearchMusicYT(this);
    layout->addWidget(searchMusicYT->searchTerm);
    layout->addWidget(searchMusicYT->songList);

    player = new Player(this);

    ui->setupUi(this);
    ui->centralwidget->setLayout(layout);
    QLabel *logoLabel = new QLabel(this);
    QPixmap Logopixmap("resources/assets/logo.png");
    QPixmap scaledLogoPixmap = Logopixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    logoLabel->setPixmap(scaledLogoPixmap);
    logoLabel->setAlignment(Qt::AlignCenter);
    ui->toolBar->addWidget(logoLabel);


   // QToolBar *PlayerToolBar = new QToolBar(this);
    ui->PlayerToolBar->addWidget(player->playButton);
    ui->PlayerToolBar->addWidget(player->nextButton);
    ui->PlayerToolBar->addWidget(player->prevButton);
    ui->PlayerToolBar->addWidget(player->volumeBar);
    ui->PlayerToolBar->addWidget(player->progressBar);
    ui->PlayerToolBar->addWidget(player->songTitle);
    ui->PlayerToolBar->addWidget(player->songTime);
    ui->PlayerToolBar->addWidget(player->songDuration);

    // Main button
    QPushButton *openMenuButton = new QPushButton("Main", this);
    openMenuButton->setStyleSheet(
        "QPushButton {"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 #011517, stop:1 #011519);"
        "    color: white;"
        "    border: 2px solid #4CAF50;"
        "    padding: 10px 20px;"
        "}"
        "QPushButton:hover {"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 #42a658);"
        "}"
        "QPushButton:pressed {"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 #289042);"
        "}"
        );
    ui->toolBar->addWidget(openMenuButton);

    // Player button
    QPushButton *openPlayerButton = new QPushButton("Player", this);
    openPlayerButton->setStyleSheet(
        "QPushButton {"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 #011517, stop:1 #011519);"
        "    color: white;"
        "    border: 2px solid #4CAF50;"
        "    padding: 10px 20px;"
        "}"
        "QPushButton:hover {"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 #42a658);"
        "}"
        "QPushButton:pressed {"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 #289042);"
        "}"
        );
    ui->toolBar->addWidget(openPlayerButton);

    // Playlist button
    QPushButton *openPlaylistSubMenuButton = new QPushButton("Playlisty", this);
    openPlaylistSubMenuButton->setStyleSheet(
        "QPushButton {"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 #011517, stop:1 #011519);"
        "    color: white;"
        "    border: 2px solid #4CAF50;"
        "    padding: 10px 20px;"
        "}"
        "QPushButton:hover {"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 #42a658);"
        "}"
        "QPushButton:pressed {"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 #289042);"
        "}"
        );
    ui->toolBar->addWidget(openPlaylistSubMenuButton);

    connect(openMenuButton, &QPushButton::clicked, this, &MainWindow::OpenMenu);
    connect(openPlayerButton, &QPushButton::clicked, this, &MainWindow::OpenPlayerMenu);
    connect(openPlaylistSubMenuButton, &QPushButton::clicked, this, &MainWindow::OpenPlaylistSubMenu);
}

void MainWindow::OpenMenu()
{
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }

    searchMusicYT = new SearchMusicYT(this);
    layout->addWidget(searchMusicYT->searchTerm);
    layout->addWidget(searchMusicYT->songList);
    ui->centralwidget->setLayout(layout);
}

void MainWindow::OpenPlaylistSubMenu()
{
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }

    playlistloader = new class playlistloader(this);
    layout->addWidget(playlistloader);
    ui->centralwidget->setLayout(layout);
}

void MainWindow::OpenPlayerMenu()
{

    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }

    player = new class Player(this);
    layout->addWidget(player);
    ui->centralwidget->setLayout(layout);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete layout;
    delete searchMusicYT;
    delete player;
}
