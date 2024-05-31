#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);

    searchMusicYT = new SearchMusicYT(this);
    layout->addWidget(searchMusicYT->textInput);
    layout->addWidget(searchMusicYT->songList);

    ui->setupUi(this);
    ui->centralwidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete layout;
    delete searchMusicYT;
}
