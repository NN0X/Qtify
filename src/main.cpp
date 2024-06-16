#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.setWindowTitle("Qtify");
    QIcon windowicon("resources/assets/logo.png");
    mainWindow.setWindowIcon(windowicon);
    mainWindow.show();
    return app.exec();
}
