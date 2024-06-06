#include "PlaylistSubmenu.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

playlistloader::playlistloader(QWidget *parent)
    : QWidget(parent)
{
    initUI();
    loadPlaylists();
}

void playlistloader::initUI()
{
    fileList = new QListWidget();
    fileContent = new QTextEdit();
    fileContent->setReadOnly(true);

    connect(fileList, &QListWidget::itemClicked, this, &playlistloader::displayFileContent);

    QVBoxLayout *leftLayout = new QVBoxLayout();
    leftLayout->addWidget(fileContent);

    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->addWidget(fileList);

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    setLayout(mainLayout);
}

void playlistloader::loadPlaylists()
{
    QFile file("resources/music/playlisty.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (!line.isEmpty()) {
                fileList->addItem(line);
            }
        }
        file.close();
    } else {
        QMessageBox::warning(this, "Błąd", "Nie znaleziono pliku 'playlisty.txt'.");
    }
}

void playlistloader::displayFileContent(QListWidgetItem *item)
{
    QString filename = item->text();
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        fileContent->setPlainText(in.readAll());
        file.close();
    } else {
        fileContent->setPlainText(QString("Nie znaleziono pliku '%1'.").arg(filename));
    }
}
