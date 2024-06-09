#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qpushbutton.h"
#include <QLabel>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->setStyleSheet("background-color: #001315;");
    layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);

    searchMusicYT = new SearchMusicYT(this);
    layout->addWidget(searchMusicYT->searchTerm);
    layout->addWidget(searchMusicYT->songList);


    ui->setupUi(this);
    ui->centralwidget->setLayout(layout);


    //desing
    //logo
    QLabel *logoLabel = new QLabel(this);
    QPixmap Logopixmap("resources/assets/logo.png");
    QPixmap scaledLogoPixmap = Logopixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    logoLabel->setPixmap(scaledLogoPixmap);
    logoLabel->setAlignment(Qt::AlignCenter);
    ui->toolBar->addWidget(logoLabel);

    //playlisty

    QPushButton *openPlaylistSubMenuButton = new QPushButton("Playlisty",this);

    openPlaylistSubMenuButton->setStyleSheet(
        "QPushButton {"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 #011517, stop:1 #011519);" // Gradient od zielonego do ciemnozielonego
        "    color: white;"                        // Biały kolor tekstu
        "    border: 2px solid #4CAF50;"           // Zielona ramka
        //"    border-radius: 10px;"                 // Zaokrąglone rogi
        "    padding: 10px 20px;"                  // Wewnętrzne odstępy
        "}"
        "QPushButton:hover {"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 #42a658);" // Jaśniejszy zielony na hover
        "}"
        "QPushButton:pressed {"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 #289042);" // Ciemniejszy zielony na kliknięcie
        "}"
        );
    layout->addWidget(openPlaylistSubMenuButton);
    ui->toolBar->addWidget(openPlaylistSubMenuButton);

    //main layout



    //end of desing



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
}


MainWindow::~MainWindow()
{
    delete ui;
    delete layout;
    delete searchMusicYT;
}
