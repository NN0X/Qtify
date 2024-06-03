#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);

    searchMusicYT = new SearchMusicYT(this);
    layout->addWidget(searchMusicYT->searchTerm);
    layout->addWidget(searchMusicYT->songList);

    player = new Player(this);
    layout->addWidget(player->playButton);
    layout->addWidget(player->nextButton);
    layout->addWidget(player->prevButton);
    layout->addWidget(player->volume);
    layout->addWidget(player->progress);
    layout->addWidget(player->songTitle);
    layout->addWidget(player->songTime);
    layout->addWidget(player->songDuration);

    ui->setupUi(this);
    ui->centralwidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete layout;
    delete searchMusicYT;
    delete player;
}
