#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qpushbutton.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);

    searchMusicYT = new SearchMusicYT(this);
    layout->addWidget(searchMusicYT->searchTerm);
    layout->addWidget(searchMusicYT->songList);


    ui->setupUi(this);
    ui->centralwidget->setLayout(layout);

    QPushButton *openPlaylistSubMenuButton = new QPushButton("Playlisty", this);
    ui->toolBar->addWidget(openPlaylistSubMenuButton);

    connect(openPlaylistSubMenuButton, &QPushButton::clicked, this, &MainWindow::OpenPlaylistSubMenu);
}
void MainWindow::OpenPlaylistSubMenu()
{
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    playlistloader = new class playlistloader(this);
    layout->addWidget(playlistloader);
    ui->centralwidget->setLayout(layout);

    //&playlistloader::loadPlaylists();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete layout;
    delete searchMusicYT;
}
