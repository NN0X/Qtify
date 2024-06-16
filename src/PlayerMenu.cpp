#include "PlayerMenu.h"
#include "mainwindow.h"
PlayerMenu::PlayerMenu(QWidget *parent, Player *player)
  : QWidget(parent),player(player)
{

    setupUI();
    loadPlaylists();
}
PlayerMenu::~PlayerMenu()
{
    delete playlistList;
    delete songList;
}
void PlayerMenu::setupUI() {
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    playlistList = new QListWidget();
    playlistList->setStyleSheet(
        "QListWidget {"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 #011517, stop:1 #011519);"
        "    color: white;"
        "    border: 2px solid #4CAF50;"
        "    padding: 10px 20px;"
        "}"
        );
    QVBoxLayout *leftLayout = new QVBoxLayout();
    leftLayout->addWidget(playlistList);

    songList = new QListWidget();
    songList->setStyleSheet(
        "QListWidget {"
        "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
        "        stop:0 #011517, stop:1 #011519);"
        "    color: white;"
        "    border: 2px solid #4CAF50;"
        "    padding: 10px 20px;"
        "}"
        );
    QVBoxLayout *centerLayout = new QVBoxLayout();
    leftLayout->addWidget(songList);

    connect(songList, &QListWidget::itemDoubleClicked, this, &PlayerMenu::onsongselected);
    connect(playlistList, &QListWidget::itemDoubleClicked, this, &PlayerMenu::displaySongsInPlaylist);

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(centerLayout);
    setLayout(mainLayout);
}
void PlayerMenu::loadPlaylists() {
    QString filename = "resources/music/playlisty.txt";
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //QMessageBox::warning(this, tr("Błąd odczytu"), tr("Nie można otworzyć pliku playlisty.txt"));
        return;
    }
    playlistList->addItem("list");
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QListWidgetItem *item = new QListWidgetItem(line);
        playlistList->addItem(item);
    }
    file.close();
}

void PlayerMenu::displaySongsInPlaylist(QListWidgetItem *item) {
    QString filename = "resources/music/" + item->text() + ".txt";
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //QMessageBox::warning(this, tr("Błąd odczytu"), tr("Nie można otworzyć pliku ") + filename);
        return;
    }

    songList->clear();
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (!line.isEmpty()) {
            QStringList parts = line.split("\t");
            if (parts.size() == 2) {
                QListWidgetItem *item = new QListWidgetItem(parts[1]);
                item->setData(Qt::UserRole, parts[0]);
                songList->addItem(item);
            }
        }
    }
    file.close();
}

void PlayerMenu::onsongselected(QListWidgetItem *item)
{
    if (item)
    {
        QListWidgetItem *playlistItem = playlistList->currentItem();
        if (playlistItem)
        {
          player->loadplaylist(item,playlistItem->text());
        }
    }
}
