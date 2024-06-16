#include "mainwindow.h"
#include "../ui/ui_mainwindow.h"

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
    //player->initPlayerToolbox();
    ui->setupUi(this);
    ui->centralwidget->setLayout(layout);
    QLabel *logoLabel = new QLabel(this);
    QPixmap Logopixmap("resources/assets/logo.png");
    QPixmap scaledLogoPixmap = Logopixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    logoLabel->setPixmap(scaledLogoPixmap);
    logoLabel->setAlignment(Qt::AlignCenter);
    ui->toolBar->addWidget(logoLabel);

    ui->PlayerToolBar->addWidget(player->prevButton);
    ui->PlayerToolBar->addWidget(player->playButton);
    ui->PlayerToolBar->addWidget(player->nextButton);
    ui->PlayerToolBar->addWidget(player->songTime);
    ui->PlayerToolBar->addWidget(player->songDuration);
    ui->PlayerToolBar->addWidget(player->progressBar);
    ui->PlayerToolBar->addWidget(player->volumeBar);
    ui->PlayerToolBar->addWidget(player->songTitle);

    QString defaultbuttonlayout=
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
        "}";

    QPushButton *openMenuButton = new QPushButton("Main", this);
    openMenuButton->setStyleSheet(defaultbuttonlayout);
    ui->toolBar->addWidget(openMenuButton);
    QPushButton *openPlayerButton = new QPushButton("Player", this);
    openPlayerButton->setStyleSheet(defaultbuttonlayout);
    ui->toolBar->addWidget(openPlayerButton);
    QPushButton *openPlaylistSubMenuButton = new QPushButton("Playlisty", this);
    openPlaylistSubMenuButton->setStyleSheet(defaultbuttonlayout);
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

    playerMenu = new PlayerMenu(this, player);
    layout->addWidget(playerMenu);
    ui->centralwidget->setLayout(layout);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete layout;
    //delete searchMusicYT;
    if (player->playerProcess != nullptr)
    {
        QByteArray data("EXIT\n");
        player->playerProcess->write(data);
        player->playerProcess->waitForFinished();
        delete player->playerProcess;
    }

    for (Song *song : player->songs)
    {
        delete song;
    }
    delete player->playButton;
    delete player->nextButton;
    delete player->prevButton;
    delete player->volumeBar;
    delete player->progressBar;
    delete player->songTitle;
    delete player->songTime;
    delete player->songDuration;
    delete player;
}
