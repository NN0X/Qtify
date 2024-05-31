#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{

    layout = new QVBoxLayout();

    searchMusic = new SearchMusic(this);
    layout->addWidget(searchMusic->textInput);

    ui->setupUi(this);
    ui->centralwidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete layout;
    delete searchMusic;
}
